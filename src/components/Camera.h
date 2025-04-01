#pragma once
#define _USE_MATH_DEFINES

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>>
#include <math.h>

struct Camera
{
    glm::mat4 projectionMatrix;

    static glm::mat4 BuildProjectionMatrix(float fov, float nearClip, float farClip, unsigned int windowWidth, unsigned int windowHeight)
    {
        return glm::perspective (fov, static_cast<float>(windowWidth / windowHeight), nearClip, farClip);
    }
};
