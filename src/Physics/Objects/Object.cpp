#include "../../../include/Physics/Objects/Object.h"

glm::vec2 Physics::Object::getVelocity()
{
    return velocity;
}

void Physics::Object::setVelocity(glm::vec2 v)
{
    velocity = v;
}