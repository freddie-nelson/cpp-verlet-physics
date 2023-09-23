#pragma once

#include "./Object.h"

namespace Physics
{
    class Circle : public Object
    {
    public:
        Circle(glm::vec2 c, float r, float mass = 1.0f, float restitution = 1.0f, glm::vec2 friction = glm::vec2(0.0f, 0.0f));

        glm::vec2 getCentre();
        void setCentre(glm::vec2 c);

        float getRadius();
        void setRadius(float r);

    private:
        glm::vec2 centre;
        float radius;
    };
}