#include "../../../include/Physics/Solvers/solveDamping.h"

void Physics::solveDamping(Physics::Object *o, glm::vec2 globalDamping, float dt)
{
    o->setVelocity(o->getVelocity() * globalDamping * o->getFriction());
}