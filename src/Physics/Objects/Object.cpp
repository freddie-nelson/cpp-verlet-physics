#include "../../../include/Physics/Objects/Object.h"

void Physics::Object::move(glm::vec2 move)
{
    centre += move;
}

void Physics::Object::applyForce(glm::vec2 force)
{
    velocity += force / mass; // f = ma -> a = f / m (acceleration applied instantly to velocity)
}

glm::vec2 Physics::Object::getCentre()
{
    return centre;
}

void Physics::Object::setCentre(glm::vec2 c)
{
    centre = c;
}

glm::vec2 Physics::Object::getVelocity()
{
    return velocity;
}

void Physics::Object::setVelocity(glm::vec2 v)
{
    velocity = v;
}

float Physics::Object::getMass()
{
    return mass;
}

void Physics::Object::setMass(float m)
{
    mass = m;
}

float Physics::Object::getRestitution()
{
    return restitution;
}

void Physics::Object::setRestitution(float r)
{
    restitution = r;
}