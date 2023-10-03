#pragma once

#include "./DistanceConstraint.h"
#include "../../Objects/Object.h"

#include <glm/glm.hpp>

namespace Physics
{
    class DistanceConstraintObjects : public DistanceConstraint
    {
    public:
        /**
         * Creates a new distance constraint between two object's centres;
         *
         * @param a The first object.
         * @param b The second object.
         * @param stiffness The stiffness of the constraint (0 flexible, 1 stiff)
         * @param distance The distance to maintain between the points (set to -1.0f to calculate automatically)
         */
        DistanceConstraintObjects(Object *a, Object *b, float stiffness = 1.0f, float distance = -1.0f);

        void solve(float dt = 0);

        Object *getA();
        void setA(Object *a);

        Object *getB();
        void setB(Object *b);

        /**
         * Sets the distance to maintain between p1 and p2.
         *
         * If the distance is set to -1, the distance will be calculated automatically from
         * the current distance between p1 and p2.
         *
         * @param d The distance to set.
         */
        void setDistance(float d);

    private:
        Object *a;
        Object *b;
    };
}