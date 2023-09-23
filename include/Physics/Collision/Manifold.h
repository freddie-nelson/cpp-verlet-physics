#pragma once

#include "../Objects/Object.h"

namespace Physics
{
    struct Manifold
    {
        Object *a;
        Object *b;

        Point *pa;

        glm::vec2 normal;
        float depth;
    };
}