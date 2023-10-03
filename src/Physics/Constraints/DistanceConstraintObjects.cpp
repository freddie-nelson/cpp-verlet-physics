#include "../../../include/Physics/Constraints/DistanceConstraint/DistanceConstraintObjects.h"

#include <stdexcept>
#include <iostream>

Physics::DistanceConstraintObjects::DistanceConstraintObjects(Object *a, Object *b, float stiffness, float distance) : DistanceConstraint(0, 0)
{
    this->a = a;
    this->b = b;

    setDistance(distance);
    setStiffness(stiffness);
}

void Physics::DistanceConstraintObjects::solve(float dt)
{
    auto distance = getDistance();
    auto stiffness = getStiffness();

    auto aToB = b->getCentre() - a->getCentre();
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

    a->move(offset * (a->getInvMass() / totalInvMass));
    b->move(-offset * (b->getInvMass() / totalInvMass));
}

Physics::Object *Physics::DistanceConstraintObjects::getA()
{
    return a;
}

void Physics::DistanceConstraintObjects::setA(Object *a)
{
    this->a = a;
}

Physics::Object *Physics::DistanceConstraintObjects::getB()
{
    return b;
}

void Physics::DistanceConstraintObjects::setB(Object *b)
{
    this->b = b;
}

void Physics::DistanceConstraintObjects::setDistance(float d)
{
    if (d == -1.0f)
    {
        DistanceConstraint::setDistance(glm::distance(a->getCentre(), b->getCentre()));
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