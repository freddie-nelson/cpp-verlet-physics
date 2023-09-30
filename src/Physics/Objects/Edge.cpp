#include "../../../include/Physics/Objects/Edge.h"

#include <glm/glm.hpp>

Physics::Edge::Edge(Point *p1, Point *p2, bool isBrace, float stiffness, float length) : DistanceConstraint(p1, p2, stiffness, length), isBrace(isBrace)
{
    setLength(length);
}

glm::vec2 Physics::Edge::getNormal(bool clockwise)
{
    auto p1Pos = getP1()->getPosition();
    auto p2Pos = getP2()->getPosition();

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

bool Physics::Edge::getIsBrace()
{
    return isBrace;
}

float Physics::Edge::getLength()
{
    return getDistance();
}

void Physics::Edge::setLength(float l)
{
    setDistance(l);
}
