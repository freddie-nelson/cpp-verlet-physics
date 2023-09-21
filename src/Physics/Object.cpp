#include "../../include/Physics/Object.h"

glm::vec2 Physics::Object::getVelocity()
{
    return velocity;
}

glm::vec2 Physics::Object::setVelocity(glm::vec2 v)
{
    velocity = v;
}