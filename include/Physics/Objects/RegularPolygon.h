#pragma once

#include "./Object.h"

namespace Physics
{
    class RegularPolygon : public Object
    {
    public:
        RegularPolygon(glm::vec2 c, float r, int sides, float mass = 1.0f, float restitution = 1.0f, float friction = 0.0f, float drag = 0.0f);

        void setCentre(glm::vec2 c);

        float getRadius();
        void setRadius(float r);

        int getSides();
        void setSides(int s);

        AABB getAABB();

    private:
        glm::vec2 centre;
        float radius;
        int sides = 0;
    };
}