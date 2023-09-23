#pragma once

#include "../Objects/Object.h"

namespace Physics
{
    /**
     * Applies global damping and local damping to an object
     *
     * @param o The object to apply damping to
     * @param globalDamping The damping to apply to the object (0 to 1)
     * @param dt The time step
     */
    void solveDamping(Physics::Object *o, glm::vec2 globalDamping, float dt);
}