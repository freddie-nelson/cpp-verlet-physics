#pragma once

#include "../../../include/Physics/Collision/BroadPhase.h"
#include "./Manifold.h"
#include "../Objects/Object.h"
#include "../Objects/Circle.h"

#include <vector>

namespace Physics
{
    std::vector<Manifold *> *narrowPhase(std::vector<CollisionPair *> *pairs);

    /**
     * @returns the manifold when there is a collision, otherwise `nullptr`
     */
    Manifold *narrowPhasePair(CollisionPair *pair);

    // std::vector<Manifold *> *narrowPhaseSlow(std::vector<Object *> *objects);

    void cleanupManifolds(std::vector<Manifold *> *manifolds);

    Manifold *circleCircle(Circle *a, Circle *b);

    struct Axis
    {
        glm::vec2 axis;
        Edge *edge;
        Object *parent;
    };

    Manifold *sat(Object *a, Object *b);
    void projectPointsToAxis(Object *o, glm::vec2 &axis, float &min, float &max);
    float getIntervalDistance(float minA, float maxA, float minB, float maxB);
}