#include "../../../include/Physics/Objects/Circle.h"

Physics::Circle::Circle(glm::vec2 c, float r, float m) : radius(r)
{
    Object::setCentre(c);
    Object::setMass(m);

    if (radius < 0)
        radius = 0;
}

std::vector<float> Physics::Circle::getSize()
{
    std::vector<float> s;
    s.push_back(radius);

    return s;
}

bool Physics::Circle::setSize(std::vector<float> size)
{
    if (size.size() != 1)
        return false;
    if (size[0] < 0)
        return false;

    radius = size[0];

    return true;
}

float Physics::Circle::getRadius()
{
    return radius;
}

void Physics::Circle::setRadius(float r)
{
    radius = r;
}
