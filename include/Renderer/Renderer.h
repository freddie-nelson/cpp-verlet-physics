#pragma once

#include "./Shapes/Circle.h"
#include "./Color.h"

#include <vector>

namespace Renderer
{
    class Renderer
    {
    public:
        virtual void clear() = 0;
        virtual void present() = 0;

        virtual void circle(const Circle &circle, const Color &color) = 0;
    };

}