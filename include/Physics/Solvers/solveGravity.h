#pragma once

#include "../Objects/Point.h"

namespace Physics
{
    void solveGravity(Physics::Point *p, glm::vec2 gravity, float dt);
}