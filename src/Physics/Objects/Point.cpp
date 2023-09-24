#include "../../../include/Physics/Objects/Point.h"

#include <stdexcept>

Physics::Point::Point(glm::vec2 position, float mass, float restitution, float friction, float drag)
{
    this->position = position;
    this->oldPosition = position;

    setMass(mass);
    setRestitution(restitution);
    setFriction(friction);
    setDrag(drag);
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
    if (m <= 0)
        throw std::invalid_argument("Mass must be greater than or equal to 0.");

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
    if (r < 0 || r > 1)
        throw std::invalid_argument("Restitution must be between 0 and 1.");

    restitution = r;
}

float Physics::Point::getFriction()
{
    return friction;
}

void Physics::Point::setFriction(float f)
{
    if (f < 0 || f > 1)
        throw std::invalid_argument("Friction must be between 0 and 1.");

    friction = f;
}

float Physics::Point::getDrag()
{
    return drag;
}

void Physics::Point::setDrag(float d)
{
    if (d < 0)
        throw std::invalid_argument("Drag must be greater than or equal to 0.");

    drag = d;
}

glm::vec2 &Physics::Point::getPosition()
{
    return position;
}

void Physics::Point::setPosition(glm::vec2 p)
{
    position = p;
}

glm::vec2 &Physics::Point::getOldPosition()
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

glm::vec2 &Physics::Point::getAcceleration()
{
    return acceleration;
}

void Physics::Point::setAcceleration(glm::vec2 a)
{
    acceleration = a;
}

glm::vec2 &Physics::Point::getNewAcceleration()
{
    return newAcceleration;
}

void Physics::Point::setNewAcceleration(glm::vec2 a)
{
    newAcceleration = a;
}