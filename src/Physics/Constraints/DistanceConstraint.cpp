#include "../../../include/Physics/Constraints/DistanceConstraint.h"

#include <stdexcept>

Physics::DistanceConstraint::DistanceConstraint(Point *p1, Point *p2, float stiffness, float distance)
{
    this->p1 = p1;
    this->p2 = p2;

    setDistance(distance);
    setStiffness(stiffness);
}

void Physics::DistanceConstraint::solve(float dt)
{
    auto a = p1;
    auto b = p2;

    auto aToB = b->getPosition() - a->getPosition();
    auto aToBLen = glm::length(aToB);

    auto diff = aToBLen - distance;
    auto dir = glm::normalize(aToB);

    auto offset = dir * diff * stiffness * 0.5f;

    a->setPosition(a->getPosition() + offset);
    b->setPosition(b->getPosition() - offset);
}

Physics::Point *Physics::DistanceConstraint::getP1()
{
    return p1;
}

void Physics::DistanceConstraint::setP1(Point *p)
{
    p1 = p;
}

Physics::Point *Physics::DistanceConstraint::getP2()
{
    return p2;
}

void Physics::DistanceConstraint::setP2(Point *p)
{
    p2 = p;
}

float Physics::DistanceConstraint::getDistance()
{
    return distance;
}

void Physics::DistanceConstraint::setDistance(float d)
{
    if (d == -1.0f)
    {
        distance = glm::distance(p1->getPosition(), p2->getPosition());
    }
    else if (d >= 0)
    {
        distance = d;
    }
    else
    {
        throw std::invalid_argument("Distance must be greater than or equal to 0 or -1.");
    }
}

float Physics::DistanceConstraint::getStiffness()
{
    return stiffness;
}

void Physics::DistanceConstraint::setStiffness(float s)
{
    if (s < 0 || s > 1)
        throw std::invalid_argument("Stiffness must be between 0 and 1.");

    stiffness = s;
}