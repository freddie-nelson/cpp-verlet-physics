#include "../../../include/Physics/Objects/Edge.h"

#include <glm/glm.hpp>
#include <stdexcept>

Physics::Edge::Edge(Point *p1, Point *p2, float length, float stiffness)
{
    this->p1 = p1;
    this->p2 = p2;

    setLength(length);
    setStiffness(stiffness);
}

Physics::Point *Physics::Edge::getP1()
{
    return p1;
}

void Physics::Edge::setP1(Point *p)
{
    p1 = p;
}

Physics::Point *Physics::Edge::getP2()
{
    return p2;
}

void Physics::Edge::setP2(Point *p)
{
    p2 = p;
}

float Physics::Edge::getLength()
{
    return length;
}

void Physics::Edge::setLength(float l)
{
    if (l == -1.0f)
    {
        length = glm::distance(p1->getPosition(), p2->getPosition());
    }
    else if (l >= 0)
    {
        length = l;
    }
    else
    {
        throw std::invalid_argument("Length must be greater than or equal to 0 or -1.");
    }
}

float Physics::Edge::getStiffness()
{
    return stiffness;
}

void Physics::Edge::setStiffness(float s)
{
    if (s < 0 || s > 1)
        throw std::invalid_argument("Stiffness must be between 0 and 1.");

    stiffness = s;
}