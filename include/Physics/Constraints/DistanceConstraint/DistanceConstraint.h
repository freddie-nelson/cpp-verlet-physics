#pragma once

#include "../Constraint.h"

#include <glm/glm.hpp>

namespace Physics
{
    class DistanceConstraint : public Constraint
    {
    public:
        /**
         * Creates a new distance constraint.
         *
         * @param stiffness The stiffness of the constraint (0 flexible, 1 stiff)
         * @param distance The distance to maintain between the points (set to -1.0f to calculate automatically)
         */
        DistanceConstraint(float stiffness = 1.0f, float distance = -1.0f);

        virtual void solve(float dt = 0) = 0;

        float getDistance();

        virtual void setDistance(float l);

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
        float distance = -1.0f;
        float stiffness = 0.0f;
    };
}