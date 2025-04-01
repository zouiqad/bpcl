#pragma once
#include <memory>

#include "graphics/Skybox.h"


struct Cubemap {
    std::shared_ptr<Skybox> skybox;
};
