#pragma once

#include "./Object.h"

namespace Physics
{
    class Circle : public Object
    {
    public:
        Circle(glm::vec2 c, float r);

        glm::vec2 getPosition();
        void setPosition(glm::vec2 c);

        void move(glm::vec2 c);

        std::vector<float> getSize();
        bool setSize(std::vector<float> size);

        float getRadius();
        void setRadius(float r);

    private:
        glm::vec2 centre;
        float radius;
    };
}