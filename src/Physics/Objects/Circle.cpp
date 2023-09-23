#include "../../../include/Physics/Objects/Circle.h"

#include <stdexcept>

Physics::Circle::Circle(glm::vec2 centre, float radius, float mass, float restitution, glm::vec2 friction) : Object(ObjectType::CircleObject, *(new std::vector<glm::vec2>{centre}), mass, restitution, friction)
{
    setRadius(radius);
}

glm::vec2 Physics::Circle::getCentre()
{
    return getPoints()[0]->getPosition();
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
