#include "../../../include/Physics/Solvers/solveVelocity.h"

void Physics::solveVelocity(Physics::Object *o, float dt)
{
    o->setVelocity(o->getVelocity() + (o->getAcceleration() + o->getNewAcceleration()) * (dt * 0.5f));
}