#pragma once

#include"core/Drawable.h"
#include <glm/glm.hpp>

struct Renderable
{
    std::shared_ptr<Drawable> drawable;
    glm::vec3 color = { 1.0f, 1.0f, 1.0f};
};
