#include "../../../include/Physics/Collision/NarrowPhase.h"

#include <glm/glm.hpp>
#include <stdexcept>

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

std::vector<Physics::Manifold *> *Physics::narrowPhaseSlow(std::vector<Object *> *objects)
{
    std::vector<Manifold *> *manifolds = new std::vector<Manifold *>();

    for (auto a : *objects)
    {
        for (auto b : *objects)
        {
            if (a == b)
                continue;

            Manifold *m = nullptr;

            if (a->getType() == ObjectType::CircleObject && b->getType() == ObjectType::CircleObject)
            {

                m = circleCircle(static_cast<Circle *>(a), static_cast<Circle *>(b));
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
    }

    return manifolds;
}

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

    m->normal = glm::normalize(aToB);

    float distance = glm::length(aToB);
    m->depth = maxDistance - distance;

    return m;
}