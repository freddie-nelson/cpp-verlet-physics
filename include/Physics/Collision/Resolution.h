#pragma once

#include "./Manifold.h"

namespace Physics
{
    void resolveCollisions(std::vector<Manifold *> *manifolds);
}