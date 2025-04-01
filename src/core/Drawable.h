#pragma once
#include "graphics/Shader.h"

class Drawable {
public:
    virtual ~Drawable() {}
    virtual void draw(Shader &shader) const = 0;
};
