#pragma once

#include "./DistanceConstraint.h"
#include "../../Objects/Point.h"

#include <glm/glm.hpp>

namespace Physics
{
    class DistanceConstraintPoints : public DistanceConstraint
    {
    public:
        /**
         * Creates a new distance constraint between two points.
         *
         * @param p1 The first point.
         * @param p2 The second point.
         * @param stiffness The stiffness of the constraint (0 flexible, 1 stiff)
         * @param distance The distance to maintain between the points (set to -1.0f to calculate automatically)
         */
        DistanceConstraintPoints(Point *p1, Point *p2, float stiffness = 1.0f, float distance = -1.0f);

        void solve(float dt = 0);

        Point *getP1();
        void setP1(Point *p);

        Point *getP2();
        void setP2(Point *p);

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
        Point *p1;
        Point *p2;
    };
}