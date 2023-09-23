#include "../../../include/Physics/Solvers/solveGravity.h"

void Physics::solveGravity(Physics::Point *p, glm::vec2 gravity, float dt)
{
    p->applyForce(gravity * p->getMass());
}