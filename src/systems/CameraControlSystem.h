#pragma once

#include "core/System.h"


class Event;


class CameraControlSystem : public System
{
public:
    void Init();

    void Update(float dt);

private:
    std::bitset<8> mButtons;
    double mPitch = -45.0f, mYaw = -90.0f, mRoll = 0.0f;

    // Controls params
    float mouseSensitivity = 0.1f;
    float cameraSpeed = 40.0f;

    // Listeners
    void KeyboardInputListener(Event& event);
    void MouseInputListener(Event& event);
};
