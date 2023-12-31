#include "../../../include/Physics/Collision/NarrowPhase.h"

#include <glm/glm.hpp>
#include <stdexcept>
#include <iostream>

std::vector<Physics::Manifold *> *Physics::narrowPhase(std::vector<CollisionPair *> *pairs)
{
    std::vector<Manifold *> *manifolds = new std::vector<Manifold *>();

    for (auto p : *pairs)
    {
        auto m = narrowPhasePair(p);

        if (m == nullptr)
            continue;

        // emit collision event
        m->a->emit("collision", EventData{
                                    "collision",
                                    m,
                                });

        manifolds->push_back(m);
    }

    return manifolds;
}

Physics::Manifold *Physics::narrowPhasePair(Physics::CollisionPair *pair)
{
    auto [a, b] = *pair;

    if (a == b)
        return nullptr;

    Manifold *m = nullptr;

    if (a->getType() == ObjectType::CircleObject && b->getType() == ObjectType::CircleObject)
    {
        // circle vs circle
        m = circleCircle(static_cast<Circle *>(a), static_cast<Circle *>(b));
    }
    else if (a->getType() == ObjectType::PolygonObject && b->getType() == ObjectType::CircleObject)
    {
        // polygon vs circle
        m = sat(b, a);
    }
    else if (a->getType() == ObjectType::CircleObject && b->getType() == ObjectType::PolygonObject)
    {
        // circle vs polygon
        m = sat(a, b);
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

    if (m != nullptr && m->depth == 0.0f)
    {
        delete m;
        return nullptr;
    }

    return m;
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

/**
 * Performs SAT collision detection.
 *
 * For circle vs polygon collision:
 *  `a` = circle
 *  `b` = polygon
 */
Physics::Manifold *Physics::sat(Object *a, Object *b)
{
    if (a->getType() == ObjectType::CircleObject && b->getType() != ObjectType::PolygonObject)
        throw std::invalid_argument("SAT circle vs polygon must have A as a circle and B as a polygon.");

    // get all edges
    std ::vector<Edge *> aEdges = a->getEdges();
    std::vector<Edge *> bEdges = b->getEdges();

    // get all axes
    std::vector<Axis> axes;
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

        axes.push_back(Axis{
            axis,
            e,
            parent,
        });
    }

    // add closest point axis for circle vs polygon
    if (a->getType() == ObjectType::CircleObject)
    {
        // find closest point to circle
        float minDist = FLT_MAX;
        Point *closest;

        for (auto p : b->getPoints())
        {
            auto aToP = p->getPosition() - a->getCentre();
            auto dist = glm::dot(aToP, aToP);

            if (dist < minDist)
            {
                minDist = dist;
                closest = p;
            }
        }

        // get axis
        auto closestToA = a->getCentre() - closest->getPosition();
        auto axis = glm::normalize(closestToA);

        // find edge closest point is part of with normal pointing in direction of axis (towards circle)
        float bestDir = -FLT_MAX;
        Edge *edge;

        for (auto e : b->getEdges())
        {
            if (e->getP1() != closest && e->getP2() != closest)
                continue;

            float dir = glm::dot(e->getNormal(), axis);
            if (dir > bestDir)
            {
                bestDir = dir;
                edge = e;
            }
        }

        axes.push_back(Axis{
            axis,
            edge,
            b,
        });
    }

    // min distance will be used as depth in manifold
    float minDistance = FLT_MAX;
    Edge *edge = nullptr;
    Object *edgeParent = nullptr;

    // loop through axes
    for (auto &axisData : axes)
    {
        auto [axis, e, parent] = axisData;

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
    // this also insures that sat works for circles
    // since circles are always passed in as a to the function
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

    std::vector<Point *> *points = &o->getPoints();

    // get points on edge of circle to project
    if (o->getType() == Physics::ObjectType::CircleObject)
    {
        auto c = static_cast<Circle *>(o);
        c->projectPointsToAxis(axis, min, max);
        return;
    }

    for (auto p : *points)
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
