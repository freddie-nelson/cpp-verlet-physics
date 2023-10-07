#include "../../../include/Physics/Objects/Object.h"

#include <stdexcept>
#include <iostream>

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
    auto c = getCentre();
    if (p == c)
    {
        for (auto point : points)
        {
            point->applyForce(force / static_cast<float>(points.size()));
        }

        return;
    }

    auto point = getPoint(p);
    if (point == nullptr)
        throw std::invalid_argument("Point does not exist on object.");

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

    // redistribute mass to points
    setMass(mass);
}

void Physics::Object::addPoint(glm::vec2 p)
{
    Point *point = new Point(p, mass / points.size() + 1, restitution, friction);
    points.push_back(point);
}

void Physics::Object::removePoint(glm::vec2 p)
{
    for (int i = 0; i < points.size(); i++)
    {
        if (points[i]->getPosition() == p)
        {
            delete points[i];
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

std::vector<Physics::Edge *> &Physics::Object::getEdges()
{
    return edges;
}

void Physics::Object::setEdges(std::vector<Edge *> &edges)
{
    for (auto edge : this->edges)
    {
        delete edge;
    }

    this->edges.clear();

    for (auto edge : edges)
    {
        addEdge(edge);
    }
}

void Physics::Object::addEdge(Edge *e)
{
    edges.push_back(e);
}

void Physics::Object::removeEdge(Edge *e)
{
    for (int i = 0; i < edges.size(); i++)
    {
        if (edges[i] == e)
        {
            edges.erase(edges.begin() + i);
            return;
        }
    }
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

Physics::AABB Physics::Object::getAABB()
{
    auto points = getPoints();
    auto initial = points[0]->getPosition();

    glm::vec2 min = glm::vec2(initial.x, initial.y);
    glm::vec2 max = glm::vec2(initial.x, initial.y);

    for (auto p : points)
    {
        auto pos = p->getPosition();

        if (pos.x < min.x)
            min.x = pos.x;
        if (pos.x > max.x)
            max.x = pos.x;
        if (pos.y < min.y)
            min.y = pos.y;
        if (pos.y > max.y)
            max.y = pos.y;
    }

    return AABB{min : min, max : max};
}

Physics::ObjectType Physics::Object::getType()
{
    return type;
}

int Physics::Object::getId()
{
    return id;
}
