#pragma once

#include "core/System.h"
#include <vector>
#include <string>
#include <memory>
#include "graphics/Shader.h"
#include "graphics/Skybox.h"
#include "core/Types.h" // For Entity
#include <glm/glm.hpp>

class SkyboxRenderSystem : public System {
public:
    SkyboxRenderSystem();
    ~SkyboxRenderSystem();

    void Init();

    void Update(float dt);

private:
    std::unique_ptr<Skybox> mSkybox;
    std::unique_ptr<Shader> mSkyboxShader;
};

