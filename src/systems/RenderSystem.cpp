#include "RenderSystem.h"

#include "components/Camera.h"
#include "components/Renderable.h"
#include "components/Transform.h"
#include "core/Mediator.h"
#include "graphics/Shader.h"
#include <cmath>
#include <iostream>
#include <ostream>


extern Mediator gMediator;


void RenderSystem::Init()
{
	gMediator.AddEventListener(METHOD_LISTENER(Events::Window::RESIZED, RenderSystem::WindowSizeListener));

	mShader = std::make_unique<Shader>("resources/shaders/simple.vert", "resources/shaders/simple.frag");

	mCamera = gMediator.CreateEntity();


	gMediator.AddComponent(
		mCamera,
		Transform{
			.position = glm::vec3(5.0f, 10.0f, 15.0f),
		});

	gMediator.AddComponent(
		mCamera,
		Camera{
			.projectionMatrix = Camera::BuildProjectionMatrix(45.0f, 0.1f, 1000.0f, 1920, 1080)
		});

	gMediator.SetMainCamera(mCamera);
}


void RenderSystem::Update(float dt)
{
	mShader->use();
	glBindVertexArray(mVAO);

	auto& cameraTransform = gMediator.GetComponent<Transform>(mCamera);
	auto& camera = gMediator.GetComponent<Camera>(mCamera);

	for (auto const& entity : mEntities)
	{
		auto const& transform = gMediator.GetComponent<Transform>(entity);
		auto const& renderable = gMediator.GetComponent<Renderable>(entity);

		glm::mat4 view = glm::mat4(1.0f);
		view[0][3] = -cameraTransform.position.x;
		view[1][3] = -cameraTransform.position.y;
		view[2][3] = -cameraTransform.position.z;

		glm::mat4 rotY = glm::mat4(1.0f);

		float cos_theta_y = cosf(transform.rotation.y);
		float sin_theta_y = sinf(transform.rotation.y);

		rotY[0][0] = cos_theta_y;
		rotY[2][0] = -sin_theta_y;
		rotY[0][2] = sin_theta_y;
		rotY[2][2] = cos_theta_y;


		glm::mat4 rotX = glm::mat4(1.0f);

		float cosThetaX = cosf(transform.rotation.x);
		float sinThetaX = sinf(transform.rotation.x);

		rotX[1][1] = cosThetaX;
		rotX[2][1] = sinThetaX;
		rotX[1][2] = -sinThetaX;
		rotX[2][2] = cosThetaX;


		glm::mat4 rotZ = glm::mat4(1.0f);

		float cosThetaZ = cosf(transform.rotation.z);
		float sinThetaZ = sinf(transform.rotation.z);

		rotZ[0][0] = cosThetaZ;
		rotZ[1][0] = sinThetaZ;
		rotZ[0][1] = -sinThetaZ;
		rotZ[1][1] = cosThetaZ;


		glm::mat4 translate = glm::translate(glm::mat4(1.0f), transform.position);

		glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), transform.scale);

		glm::mat4 model = translate * scaleMat * rotY;

		glm::mat4 projection = camera.projectionMatrix;

		view = glm::lookAt(cameraTransform.position, cameraTransform.position + cameraTransform.forward, cameraTransform.up);

		mShader->setUniform<glm::mat4>("uModel", model);
		mShader->setUniform<glm::mat4>("uView", view);
		mShader->setUniform<glm::mat4>("uProj", projection);
		mShader->setUniform<glm::vec3>("uColor", renderable.color);

		// Lightning uniform
		mShader->setUniform("uViewPos", cameraTransform.position);
		mShader->setUniform("uSpecularStrength", 10.0f);
		mShader->setUniform("uSpecularPower", 512.0f);
		mShader->setUniform("uSunDirection", glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))); // Sun from above
		mShader->setUniform("uSunColor", glm::vec3(1.0f));  // Full white sun
		mShader->setUniform("uAmbientColor", glm::vec3(0.3f, 0.3f, 0.3f));  // Increase as needed for global illumination

		if (renderable.visible)
			renderable.drawable->draw(*mShader);
	}

	glBindVertexArray(0);
}

void RenderSystem::WindowSizeListener(Event& event)
{
	auto windowWidth = event.GetParam<unsigned int>(Events::Window::Resized::WIDTH);
	auto windowHeight = event.GetParam<unsigned int>(Events::Window::Resized::HEIGHT);

	auto& camera = gMediator.GetComponent<Camera>(mCamera);
	camera.projectionMatrix = Camera::BuildProjectionMatrix(45.0f, 0.1f, 1000.0f, windowWidth, windowHeight);
}

