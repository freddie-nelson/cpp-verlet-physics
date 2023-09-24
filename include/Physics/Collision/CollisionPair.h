#pragma once

#include "../Objects/Object.h"

namespace Physics
{
    struct CollisionPair
    {
        Object *a;
        Object *b;
    };
}