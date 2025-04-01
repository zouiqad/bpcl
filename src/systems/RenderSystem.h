#pragma once

#include "core/System.h"
#include "graphics/Shader.h"
#include <memory>


class Event;


class RenderSystem : public System
{
public:
    void Init();

    void Update(float dt);

    Entity GetCameraEntity() const { return mCamera; }

private:
    std::unique_ptr<Shader> mShader;

    Entity mCamera;

    GLuint mVAO{};
    GLuint mVBO{};

    // Listeners
    void WindowSizeListener(Event& event);
};
