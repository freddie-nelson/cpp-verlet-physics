#pragma once

#include "../Objects/Object.h"

namespace Physics
{
    void applyWindowConstraint(std::vector<Object *> *objects, int windowWidth, int windowHeight);
}