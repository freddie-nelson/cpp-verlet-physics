#include "../../../include/Physics/Objects/Edge.h"

#include <glm/glm.hpp>
#include <stdexcept>

Physics::Edge::Edge(Point *p1, Point *p2, bool isBrace, float stiffness, float length)
{
    this->p1 = p1;
    this->p2 = p2;

    this->isBrace = isBrace;
    setLength(length);
    setStiffness(stiffness);
}

glm::vec2 Physics::Edge::getNormal(bool clockwise)
{
    auto p1Pos = p1->getPosition();
    auto p2Pos = p2->getPosition();

    if (clockwise)
    {
        // y, -x (clockwise) (perpendicular vector)
        return glm::normalize(glm::vec2(p2Pos.y - p1Pos.y, p1Pos.x - p2Pos.x));
    }
    else
    {
        // -y, x (anticlockwise) (perpendicular vector)
        return glm::normalize(glm::vec2(p1Pos.y - p2Pos.y, p2Pos.x - p1Pos.x));
    }
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

bool Physics::Edge::getIsBrace()
{
    return isBrace;
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