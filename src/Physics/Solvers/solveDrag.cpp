#include "../../../include/Physics/Solvers/solveDrag.h"

#include <math.h>

void Physics::solveDrag(Physics::Point *p, float globalDrag, float dt)
{
    auto velocity = p->getVelocity();

    float dragCoeff = std::fmax(globalDrag, p->getDrag());
    auto drag = 0.5f * dragCoeff * velocity * velocity;

    p->applyForce(-drag);
}