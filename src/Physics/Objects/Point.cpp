#include "../../../include/Physics/Objects/Point.h"

#include <stdexcept>

Physics::Point::Point(glm::vec2 position, float mass, float restitution, glm::vec2 friction)
{
    if (mass <= 0)
        throw std::invalid_argument("Mass must be greater than or equal to 0.");
    if (restitution < 0 || restitution > 1)
        throw std::invalid_argument("Restitution must be between 0 and 1.");

    this->position = position;
    this->oldPosition = position;

    this->mass = mass;
    this->restitution = restitution;
    this->friction = friction;
}

void Physics::Point::move(glm::vec2 move)
{
    position += move;
}

void Physics::Point::applyForce(glm::vec2 force)
{
    newAcceleration += force / mass; // f = ma -> a = f / m
}

float Physics::Point::getMass()
{
    return mass;
}

void Physics::Point::setMass(float m)
{
    mass = m;
}

float Physics::Point::getInvMass()
{
    if (mass == 0)
        return 0;

    return 1.0f / mass;
}

float Physics::Point::getRestitution()
{
    return restitution;
}

void Physics::Point::setRestitution(float r)
{
    restitution = r;
}

glm::vec2 Physics::Point::getFriction()
{
    return friction;
}

void Physics::Point::setFriction(glm::vec2 f)
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

glm::vec2 Physics::Point::getPosition()
{
    return position;
}

void Physics::Point::setPosition(glm::vec2 p)
{
    position = p;
}

glm::vec2 Physics::Point::getOldPosition()
{
    return oldPosition;
}

void Physics::Point::setOldPosition(glm::vec2 p)
{
    oldPosition = p;
}

glm::vec2 Physics::Point::getVelocity()
{
    return position - oldPosition;
}

glm::vec2 Physics::Point::getAcceleration()
{
    return acceleration;
}

void Physics::Point::setAcceleration(glm::vec2 a)
{
    acceleration = a;
}

glm::vec2 Physics::Point::getNewAcceleration()
{
    return newAcceleration;
}

void Physics::Point::setNewAcceleration(glm::vec2 a)
{
    newAcceleration = a;
}