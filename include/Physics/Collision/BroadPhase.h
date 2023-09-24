#pragma once

#include "./CollisionPair.h"
#include "../Objects/Object.h"
#include "../Objects/AABB.h"
#include "../../Renderer/Renderer.h"

#include <vector>

namespace Physics
{
    struct BroadPhaseCellData
    {
        Object *object;
        AABB *aabb;
    };

    std::vector<CollisionPair *> *broadPhase(std::vector<Object *> &objects, int maxGridSize, Renderer::Renderer *renderer);
    void drawDebugGrid(std::vector<BroadPhaseCellData *> **grid, int gridSizeX, int gridSizeY, float cellWidth, float cellHeight, float gridX, float gridY, Renderer::Renderer *renderer);

    void cleanupCollisionPairs(std::vector<CollisionPair *> *collisionPairs);
}