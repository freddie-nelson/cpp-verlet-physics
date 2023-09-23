#include "../../../include/Physics/Solvers/solveFriction.h"

void Physics::solveFriction(Physics::Point *p, glm::vec2 globalFriction, float dt)
{
    p->applyForce(p->getFriction() + globalFriction);
}