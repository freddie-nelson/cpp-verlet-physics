#include "../../../include/Physics/Objects/Object.h"

void Physics::Object::move(glm::vec2 move)
{
    centre += move;
}

void Physics::Object::applyForce(glm::vec2 force)
{
    newAcceleration += force / mass; // f = ma -> a = f / m
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

glm::vec2 Physics::Object::getAcceleration()
{
    return acceleration;
}

void Physics::Object::setAcceleration(glm::vec2 a)
{
    acceleration = a;
}

glm::vec2 Physics::Object::getNewAcceleration()
{
    return newAcceleration;
}

void Physics::Object::setNewAcceleration(glm::vec2 a)
{
    newAcceleration = a;
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

glm::vec2 Physics::Object::getFriction()
{
    return friction;
}

void Physics::Object::setFriction(glm::vec2 f)
{
    if (f.x < 0)
        f.x = 0;
    else if (f.x > 1)
        f.x = 1;
    if (f.y < 0)
        f.y = 0;
    else if (f.y > 1)
        f.y = 1;

    friction = f;
}