#include "../../../include/Physics/Solvers/solvePosition.h"

void Physics::solvePosition(Physics::Object *o, float dt)
{
    o->setCentre(o->getCentre() + o->getVelocity() * dt + o->getAcceleration() * (dt * dt * 0.5f));
}