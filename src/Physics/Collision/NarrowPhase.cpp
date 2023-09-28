#include "../../../include/Physics/Collision/NarrowPhase.h"

#include <glm/glm.hpp>
#include <stdexcept>
#include <iostream>

std::vector<Physics::Manifold *> *Physics::narrowPhase(std::vector<CollisionPair *> *pairs)
{
    std::vector<Manifold *> *manifolds = new std::vector<Manifold *>();

    for (auto p : *pairs)
    {
        auto [a, b] = *p;

        if (a == b)
            continue;

        Manifold *m = nullptr;

        if (a->getType() == ObjectType::CircleObject && b->getType() == ObjectType::CircleObject)
        {
            // circle vs circle
            m = circleCircle(static_cast<Circle *>(a), static_cast<Circle *>(b));
        }
        else if (a->getType() == ObjectType::PolygonObject && b->getType() == ObjectType::CircleObject)
        {
            // circle vs polygon
        }
        else if (a->getType() == ObjectType::CircleObject && b->getType() == ObjectType::PolygonObject)
        {
            // circle vs polygon
        }
        else if (a->getType() == ObjectType::PolygonObject && b->getType() == ObjectType::PolygonObject)
        {
            // polygon vs polygon
            m = sat(a, b);
        }
        else
        {
            throw std::invalid_argument("Unsupported object type");
        }

        if (m == nullptr)
            continue;

        if (m->depth <= 0.0f)
        {
            delete m;
            continue;
        }

        manifolds->push_back(m);
    }

    return manifolds;
}

// std::vector<Physics::Manifold *> *Physics::narrowPhaseSlow(std::vector<Object *> *objects)
// {
//     std::vector<Manifold *> *manifolds = new std::vector<Manifold *>();

//     for (auto a : *objects)
//     {
//         for (auto b : *objects)
//         {
//             if (a == b)
//                 continue;

//             Manifold *m = nullptr;

//             if (a->getType() == ObjectType::CircleObject && b->getType() == ObjectType::CircleObject)
//             {

//                 m = circleCircle(static_cast<Circle *>(a), static_cast<Circle *>(b));
//             }
//             else
//             {
//                 throw std::invalid_argument("Unsupported object type");
//             }

//             if (m == nullptr)
//                 continue;

//             if (m->depth <= 0.0f)
//             {
//                 delete m;
//                 continue;
//             }

//             manifolds->push_back(m);
//         }
//     }

//     return manifolds;
// }

void Physics::cleanupManifolds(std::vector<Manifold *> *manifolds)
{
    for (auto m : *manifolds)
    {
        delete m;
    }

    manifolds->clear();
    delete manifolds;
}

Physics::Manifold *Physics::circleCircle(Circle *a, Circle *b)
{
    glm::vec2 aToB = b->getCentre() - a->getCentre();

    float distanceSqr = glm::dot(aToB, aToB);
    float maxDistance = a->getRadius() + b->getRadius();

    if (distanceSqr > maxDistance * maxDistance)
        return nullptr;

    Manifold *m = new Manifold();

    m->a = a;
    m->b = b;

    m->pa = a->getPoints()[0];
    m->pb = b->getPoints()[0];

    m->normal = glm::normalize(-aToB);

    float distance = glm::length(aToB);
    m->depth = maxDistance - distance;

    return m;
}

Physics::Manifold *Physics::sat(Object *a, Object *b)
{
    if (a->getType() != ObjectType::PolygonObject || b->getType() != ObjectType::PolygonObject)
        throw std::invalid_argument("Objects must be polygons for SAT.");

    // get all edges
    std::vector<Edge *> aEdges = a->getEdges();
    std::vector<Edge *> bEdges = b->getEdges();

    // min distance will be used as depth in manifold
    float minDistance = FLT_MAX;
    Edge *edge = nullptr;
    Object *edgeParent = nullptr;

    // loop through all edges of a and b
    for (int i = 0; i < aEdges.size() + bEdges.size(); i++)
    {
        Edge *e;
        Object *parent;

        if (i < aEdges.size())
        {
            e = aEdges[i];
            parent = a;
        }
        else
        {
            e = bEdges[i - aEdges.size()];
            parent = b;
        }

        if (e->getIsBrace())
            continue;

        glm::vec2 axis = e->getNormal();

        // project all points onto axis
        float minA, maxA, minB, maxB;

        projectPointsToAxis(a, axis, minA, maxA);
        projectPointsToAxis(b, axis, minB, maxB);

        float distance = getIntervalDistance(minA, maxA, minB, maxB);

        // no collision
        if (distance > 0.0f)
            return nullptr;

        // keep track of minimum distance and store collision info for later
        else if (std::abs(distance) < minDistance)
        {
            edge = e;
            edgeParent = parent;
            minDistance = std::abs(distance);
        }
    }

    // collision found
    Manifold *m = new Manifold();

    // make sure edge is on b and point is on a
    if (edgeParent != b)
    {
        auto temp = a;
        a = b;
        b = temp;
    }

    // fill manifold
    m->a = a;
    m->b = b;
    m->edge = edge;

    m->depth = minDistance;
    m->normal = edge->getNormal();

    // get point on a involved in collision (m->pa)

    // make sure collision normal is pointing at a
    auto bToA = a->getCentre() - b->getCentre();
    int sign = glm::dot(m->normal, bToA) > 0 ? 1 : -1;

    // normal is pointing away from a so flip it
    // to point normal from b to a
    if (sign != 1)
    {
        m->normal *= -1;
    }

    // find closest point in a to b's centre in the direction of the normal
    float closestDistance = FLT_MAX;

    for (auto p : a->getPoints())
    {
        auto bToP = p->getPosition() - b->getCentre();
        float dist = glm::dot(m->normal, bToP);

        if (dist < closestDistance)
        {
            closestDistance = dist;
            m->pa = p;
        }
    }

    return m;
}

void Physics::projectPointsToAxis(Object *o, glm::vec2 &axis, float &min, float &max)
{
    min = FLT_MAX;
    max = -FLT_MAX;

    for (auto p : o->getPoints())
    {
        float dot = glm::dot(p->getPosition(), axis);
        if (dot < min)
            min = dot;
        if (dot > max)
            max = dot;
    }
}

float Physics::getIntervalDistance(float minA, float maxA, float minB, float maxB)
{
    if (minA < minB)
    {
        return minB - maxA;
    }
    else
    {
        return minA - maxB;
    }
}
