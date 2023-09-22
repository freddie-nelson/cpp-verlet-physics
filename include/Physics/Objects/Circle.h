#pragma once

#include "./Object.h"

namespace Physics
{
    class Circle : public Object
    {
    public:
        Circle(glm::vec2 c, float r, float m = 1.0);

        /**
         * Returns the size of the circle as a vector containing the radius.
         */
        std::vector<float> getSize();

        /**
         * Sets the radius of the circle to the given vector's first element.
         */
        bool setSize(std::vector<float> size);

        float getRadius();
        void setRadius(float r);

    private:
        glm::vec2 centre;
        float radius;
    };
}