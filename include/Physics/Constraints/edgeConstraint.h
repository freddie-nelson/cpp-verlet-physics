#pragma once

#include "../Objects/Object.h"

#include <vector>

namespace Physics
{
    void applyEdgeConstraint(std::vector<Object *> *objects);
}