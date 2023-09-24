#pragma once

#include "./Object.h"

namespace Physics
{
    class Circle : public Object
    {
    public:
        Circle(glm::vec2 c, float r, float mass = 1.0f, float restitution = 1.0f, float friction = 0.0f);

        void setCentre(glm::vec2 c);

        float getRadius();
        void setRadius(float r);

        AABB getAABB();

    private:
        glm::vec2 centre;
        float radius;
    };
}