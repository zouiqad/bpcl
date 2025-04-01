#pragma once

#include <glm/glm.hpp>

struct Transform
{
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
    glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::ivec2 toTileCoordinate(float tileSize) const {
        int tileX = static_cast<int>(glm::round(position.x / tileSize));
        int tileY = static_cast<int>(glm::round(position.z / tileSize));
        return glm::ivec2(tileX, tileY);
    }
};
