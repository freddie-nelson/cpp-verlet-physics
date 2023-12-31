#pragma once

#include "./Shapes/Circle.h"
#include "./Shapes/Rect.h"
#include "./Color.h"

#include <vector>

namespace Renderer
{
    class Renderer
    {
    public:
        virtual void clear() = 0;
        virtual void present() = 0;

        virtual void line(glm::vec2 start, glm::vec2 end, const Color &color) = 0;
        virtual void circle(const Circle &circle, const Color &color) = 0;
        virtual void rect(const Rect &rect, const Color &color) = 0;

        /**
         * Draws a polygon with the given vertices.
         *
         * @param vertices The vertices of the polygon. (must be in clockwise order)
         * @param color The color of the polygon.
         */
        virtual void polygon(const std::vector<glm::vec2> &vertices, const Color &color) = 0;
    };

}