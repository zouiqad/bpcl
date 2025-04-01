#include "CameraControlSystem.h"

#include <iostream>

#include "Components/Transform.h"
#include "Core/Mediator.h"


extern Mediator gMediator;


void CameraControlSystem::Init()
{
    gMediator.AddEventListener(METHOD_LISTENER(Events::Window::KEYDOWN, CameraControlSystem::KeyboardInputListener));
    gMediator.AddEventListener(METHOD_LISTENER(Events::Window::MOUSEMOVE, CameraControlSystem::MouseInputListener));
}

void CameraControlSystem::Update(float dt)
{
    for (auto& entity : mEntities)
    {
        auto& transform = gMediator.GetComponent<Transform>(entity);
        // Precompute cameras right vector
        glm::vec3 right = glm::normalize(glm::cross(transform.forward, transform.up));


        // MOUSE EVENTS
        if(mPitch > 89.0)
            mPitch = 89.0;
        if(mPitch < -89.0)
            mPitch = -89.0;

        glm::vec3 direction;
        direction.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
        direction.y = sin(glm::radians(mPitch));
        direction.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
        transform.forward = glm::normalize(direction);

        // KEYBOARD EVENTS
        if (mButtons.test(static_cast<std::size_t>(InputButtons::W)))
        {
            transform.position += (dt * cameraSpeed) * transform.forward;
        }

        if (mButtons.test(static_cast<std::size_t>(InputButtons::S)))
        {
            transform.position -= (dt * cameraSpeed) * transform.forward;
        }

        if (mButtons.test(static_cast<std::size_t>(InputButtons::Q)))
        {
            transform.position += (dt * cameraSpeed) * transform.up;
        }

        if (mButtons.test(static_cast<std::size_t>(InputButtons::E)))
        {
            transform.position -= (dt * cameraSpeed) * transform.up;
        }

        if (mButtons.test(static_cast<std::size_t>(InputButtons::A)))
        {
            transform.position -= (dt * cameraSpeed) * right;
        }

        if (mButtons.test(static_cast<std::size_t>(InputButtons::D)))
        {
            transform.position += (dt * cameraSpeed) * right;
        }
    }

}

void CameraControlSystem::KeyboardInputListener(Event& event)
{
    mButtons = event.GetParam<std::bitset<8>>(Events::Window::Input::KEYS_DOWN);
}

void CameraControlSystem::MouseInputListener(Event& event)
{
    mPitch += event.GetParam<double>(Events::Window::Input::MOUSE_YOFFSET) * mouseSensitivity;
    mYaw += event.GetParam<double>(Events::Window::Input::MOUSE_XOFFSET) * mouseSensitivity;
}
