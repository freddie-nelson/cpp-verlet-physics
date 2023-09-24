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

        virtual void circle(const Circle &circle, const Color &color) = 0;
        virtual void rect(const Rect &rect, const Color &color) = 0;
    };

}