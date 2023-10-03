#include "../../../include/Physics/Constraints/DistanceConstraint/DistanceConstraint.h"

#include <stdexcept>
#include <iostream>

Physics::DistanceConstraint::DistanceConstraint(float stiffness, float distance)
{
    setDistance(distance);
    setStiffness(stiffness);
}

float Physics::DistanceConstraint::getDistance()
{
    return distance;
}

void Physics::DistanceConstraint::setDistance(float d)
{
    if (d >= 0)
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