#pragma once

#include "./Point.h"
#include "../Constraints/DistanceConstraint/DistanceConstraintPoints.h"

namespace Physics
{

    class Edge : public DistanceConstraintPoints
    {
    public:
        /**
         * Creates a new edge between two points.
         *
         * @param p1 The first point.
         * @param p2 The second point.
         * @param isBrace Wether or not the edge is being used as an internal brace for an object
         * @param stiffness The stiffness of the edge (0 flexible, 1 stiff)
         * @param length The length of the edge (set to -1.0f to calculate automatically)
         */
        Edge(Point *p1, Point *p2, bool isBrace = false, float stiffness = 1.0f, float length = -1.0f);

        glm::vec2 getNormal(bool clockwise = true);

        bool getIsBrace();

        float getLength();

        /**
         * Sets the length of the edge.
         *
         * If the length is set to -1, the length will be calculated automatically from
         * the current distance between p1 and p2.
         *
         * @param l The length of the edge.
         */
        void setLength(float l);

    private:
        bool isBrace;
    };
}