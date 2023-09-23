#pragma once

#include "../Objects/Point.h"

namespace Physics
{
    /**
     * Applies global and local friction forces to a point
     *
     * @param p The point to apply damping to
     * @param globalFriction The world friction value
     * @param dt The time step
     */
    void solveFriction(Physics::Point *p, glm::vec2 globalFriction, float dt);
}