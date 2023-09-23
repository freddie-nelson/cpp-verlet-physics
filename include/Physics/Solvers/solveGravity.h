#pragma once

#include "../Objects/Point.h"

namespace Physics
{
    void solveGravity(Physics::Point *o, glm::vec2 gravity, float dt);
}