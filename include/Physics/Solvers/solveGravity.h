#pragma once

#include "../Objects/Object.h"

namespace Physics
{
    void solveGravity(Physics::Object *o, glm::vec2 gravity, float dt);
}