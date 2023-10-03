#include "../../../include/Physics/Constraints/DistanceConstraint/DistanceConstraintPoints.h"

#include <stdexcept>
#include <iostream>

Physics::DistanceConstraintPoints::DistanceConstraintPoints(Point *p1, Point *p2, float stiffness, float distance) : DistanceConstraint(0, 0)
{
    this->p1 = p1;
    this->p2 = p2;

    setDistance(distance);
    setStiffness(stiffness);
}

void Physics::DistanceConstraintPoints::solve(float dt)
{
    auto a = p1;
    auto b = p2;

    auto distance = getDistance();
    auto stiffness = getStiffness();

    auto aToB = b->getPosition() - a->getPosition();
    auto aToBLen = glm::length(aToB);

    // points already the right distance apart
    if (aToBLen == distance)
    {
        return;
    }

    auto diff = aToBLen - distance;
    auto dir = glm::normalize(aToB);

    // correct direction when points are 0 distance apart
    // otherwise normalize results in divide by 0 and nan values
    if (aToBLen == 0)
    {
        dir = glm::vec2(0);
    }

    float totalInvMass = a->getInvMass() + b->getInvMass();
    if (totalInvMass == 0)
        totalInvMass = 1;

    auto offset = dir * diff * stiffness;

    a->setPosition(a->getPosition() + offset * (a->getInvMass() / totalInvMass));
    b->setPosition(b->getPosition() - offset * (b->getInvMass() / totalInvMass));
}

Physics::Point *Physics::DistanceConstraintPoints::getP1()
{
    return p1;
}

void Physics::DistanceConstraintPoints::setP1(Point *p)
{
    p1 = p;
}

Physics::Point *Physics::DistanceConstraintPoints::getP2()
{
    return p2;
}

void Physics::DistanceConstraintPoints::setP2(Point *p)
{
    p2 = p;
}

void Physics::DistanceConstraintPoints::setDistance(float d)
{
    if (d == -1.0f)
    {
        DistanceConstraint::setDistance(glm::distance(p1->getPosition(), p2->getPosition()));
    }
    else if (d >= 0)
    {
        DistanceConstraint::setDistance(d);
    }
    else
    {
        throw std::invalid_argument("Distance must be greater than or equal to 0 or -1.");
    }
}