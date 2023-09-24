#pragma once

#include <glm/vec2.hpp>

namespace Physics
{
    struct AABB
    {
        glm::vec2 min;
        glm::vec2 max;
    };
}