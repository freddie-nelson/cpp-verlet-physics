#pragma once

#include "../Objects/Object.h"

namespace Physics
{
    struct Manifold
    {
        Object *a;
        Object *b;

        Point *pa;
        Point *pb;

        glm::vec2 normal;
        float depth;
    };
}