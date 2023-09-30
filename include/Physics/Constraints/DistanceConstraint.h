#pragma once

#include "./Constraint.h"
#include "../Objects/Point.h"

#include <glm/glm.hpp>

namespace Physics
{
    class DistanceConstraint : public Constraint
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
        DistanceConstraint(Point *p1, Point *p2, float stiffness = 1.0f, float distance = -1.0f);

        void solve(float dt = 0);

        Point *getP1();
        void setP1(Point *p);

        Point *getP2();
        void setP2(Point *p);

        float getDistance();

        /**
         * Sets the distance to maintain between p1 and p2.
         *
         * If the distance is set to -1, the distance will be calculated automatically from
         * the current distance between p1 and p2.
         *
         * @param d The distance to set.
         */
        void setDistance(float l);

        float getStiffness();

        /**
         * Sets the stiffness of the edge.
         *
         * The stiffness is a value between 0 and 1, where 0 is a completely flexible edge and 1 is a completely stiff edge.
         *
         * @param s The stiffness of the edge.
         */
        void setStiffness(float s);

    private:
        Point *p1;
        Point *p2;

        float distance = -1.0f;
        float stiffness = 0.0f;
    };
}