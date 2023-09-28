#include "../../../include/Physics/Objects/AABB.h"

bool Physics::aabbIntersects(AABB *a, AABB *b)
{
    return a->min.x < b->max.x && a->max.x > b->min.x && a->min.y < b->max.y && a->max.y > b->min.y;
}