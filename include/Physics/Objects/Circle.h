#pragma once

#include "./Object.h"

namespace Physics
{
    class Circle : public Object
    {
    public:
        Circle(glm::vec2 c, float r, float mass = 1.0f, float restitution = 1.0f, float friction = 0.0f, float drag = 0.0f);

        void setCentre(glm::vec2 c);

        float getRadius();
        void setRadius(float r);

        AABB getAABB();

        /**
         * Projects the circle onto the given axis.
         */
        void projectPointsToAxis(glm::vec2 axis, float &min, float &max);

    private:
        float radius;
    };
}