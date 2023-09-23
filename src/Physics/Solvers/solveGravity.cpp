#include "../../../include/Physics/Solvers/solveGravity.h"

void Physics::solveGravity(Physics::Object *o, glm::vec2 gravity, float dt)
{
    o->applyForce(gravity * o->getMass());
}