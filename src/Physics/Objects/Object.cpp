#include "../../../include/Physics/Objects/Object.h"

#include <stdexcept>

int Physics::Object::nextId = 0;

Physics::Object::Object(ObjectType type, std::vector<glm::vec2> &points, float mass, float restitution, float friction, float drag) : type(type)
{
    setPoints(points);
    setMass(mass);
    setRestitution(restitution);
    setFriction(friction);
    setDrag(drag);

    id = nextId++;
}

void Physics::Object::move(glm::vec2 move)
{
    for (auto p : points)
    {
        p->setPosition(p->getPosition() + move);
    }
}

void Physics::Object::applyForce(glm::vec2 force, glm::vec2 p)
{
    auto point = getPoint(p);
    if (point == nullptr)
        throw std::invalid_argument("Point is not on object");

    point->applyForce(force);
}

float Physics::Object::getMass()
{
    return mass;
}

void Physics::Object::setMass(float m)
{
    for (auto p : points)
    {
        p->setMass(m / points.size());
    }

    mass = m;
}

float Physics::Object::getInvMass()
{
    if (mass == 0)
        return 0;

    return 1.0f / mass;
}

float Physics::Object::getRestitution()
{
    return restitution;
}

void Physics::Object::setRestitution(float r)
{
    for (auto p : points)
    {
        p->setRestitution(r);
    }

    restitution = r;
}

float Physics::Object::getFriction()
{
    return friction;
}

void Physics::Object::setFriction(float f)
{
    for (auto p : points)
    {
        p->setFriction(f);
    }

    friction = f;
}

float Physics::Object::getDrag()
{
    return drag;
}

void Physics::Object::setDrag(float d)
{
    for (auto p : points)
    {
        p->setDrag(d);
    }

    drag = d;
}

std::vector<Physics::Point *> &Physics::Object::getPoints()
{
    return points;
}

void Physics::Object::setPoints(std::vector<glm::vec2> &p)
{
    for (auto point : points)
    {
        delete point;
    }

    points.clear();

    for (auto point : p)
    {
        addPoint(point);
    }
}

void Physics::Object::addPoint(glm::vec2 p)
{
    Point *point = new Point(p, mass, restitution, friction);
    points.push_back(point);
}

void Physics::Object::removePoint(glm::vec2 p)
{
    for (int i = 0; i < points.size(); i++)
    {
        if (points[i]->getPosition() == p)
        {
            points.erase(points.begin() + i);
            return;
        }
    }
}

bool Physics::Object::hasPoint(glm::vec2 p)
{
    return getPoint(p) != nullptr;
}

Physics::Point *Physics::Object::getPoint(glm::vec2 p)
{
    for (auto point : points)
    {
        if (point->getPosition() == p)
            return point;
    }

    return nullptr;
}

glm::vec2 Physics::Object::getCentre()
{
    if (points.size() == 0)
        throw std::invalid_argument("Object has no points");
    if (points.size() == 1)
        return points[0]->getPosition();

    // calculate centre of all points
    // just the average of all points
    glm::vec2 centre = glm::vec2(0.0f, 0.0f);

    for (auto p : points)
    {
        centre += p->getPosition();
    }

    centre /= points.size();

    return centre;
}

Physics::ObjectType Physics::Object::getType()
{
    return type;
}

int Physics::Object::getId()
{
    return id;
}