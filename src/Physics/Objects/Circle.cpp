#include "../../../include/Physics/Objects/Circle.h"

#include <stdexcept>
#include <iostream>

Physics::Circle::Circle(glm::vec2 centre, float radius, float mass, float restitution, float friction, float drag) : Object(ObjectType::CircleObject, *(new std::vector<glm::vec2>{centre}), mass, restitution, friction, drag)
{
    setRadius(radius);
}

void Physics::Circle::setCentre(glm::vec2 c)
{
    setPoints(*(new std::vector<glm::vec2>{c}));
}

float Physics::Circle::getRadius()
{
    return radius;
}

void Physics::Circle::setRadius(float r)
{
    if (r < 0)
        throw std::invalid_argument("Radius must be greater than or equal to 0.");

    radius = r;
}

Physics::AABB Physics::Circle::getAABB()
{
    auto centre = getCentre();
    auto r = glm::vec2(radius, radius);

    return AABB{min : centre - r, max : centre + r};
}

void Physics::Circle::projectPointsToAxis(glm::vec2 axis, float &min, float &max)
{
    float temp = glm::dot(getCentre(), axis);

    min = temp - radius;
    max = temp + radius;
}
