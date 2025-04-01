#include "SkyboxRenderSystem.h"
#include "core/Mediator.h"
#include "components/Camera.h"
#include "components/Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

extern Mediator gMediator;

SkyboxRenderSystem::SkyboxRenderSystem()
{
}

SkyboxRenderSystem::~SkyboxRenderSystem() {
}

void SkyboxRenderSystem::Init()
{
    std::string rootPath = "resources/textures/skybox/";
    std::vector texPaths = {
        rootPath + "right.jpg",
        rootPath + "left.jpg",
        rootPath + "top.jpg",
        rootPath + "bottom.jpg",
        rootPath + "front.jpg",
        rootPath + "back.jpg"
    };

    mSkybox = std::make_unique<Skybox>(texPaths);

    mSkyboxShader = std::make_unique<Shader>("resources/shaders/skybox.vert", "resources/shaders/skybox.frag");
}

void SkyboxRenderSystem::Update(float dt)
{
    Entity camera = gMediator.GetMainCamera();
    auto& camTransform = gMediator.GetComponent<Transform>(camera);
    auto& cam = gMediator.GetComponent<Camera>(camera);


    glm::mat4 viewMatrix = glm::lookAt(camTransform.position,
                                       camTransform.position + glm::vec3(0.0f, 0.0f, -1.0f),
                                       glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 viewNoTranslation = glm::mat4(glm::mat3(viewMatrix));

    glm::mat4 projection = cam.projectionMatrix;


    mSkyboxShader->use();

    mSkyboxShader->setUniform("uView", viewNoTranslation);
    mSkyboxShader->setUniform("uProj", projection);
    mSkyboxShader->setUniform("skybox", 0);

    mSkybox->draw(*mSkyboxShader, viewNoTranslation, projection);
}
