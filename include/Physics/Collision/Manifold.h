#pragma once

#include "../Objects/Object.h"
#include "../Objects/Edge.h"

namespace Physics
{
    struct Manifold
    {
        Object *a;
        Object *b;

        Point *pa;
        Point *pb;

        Edge *edge;

        // normal points towards a (from b to a)
        glm::vec2 normal;
        float depth;
    };
}