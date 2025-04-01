#pragma once

#include "Types.h"
#include <set>


class System
{
public:
    virtual ~System() = default;

    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;

    std::set<Entity> mEntities;
};
