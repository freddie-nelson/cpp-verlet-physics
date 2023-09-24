#include "../../../include/Physics/Collision/BroadPhase.h"
#include "../../../include/Renderer/Color.h"

#include <math.h>
#include <iostream>

std::vector<Physics::CollisionPair *> *Physics::broadPhase(std::vector<Object *> &objects, int maxGridSize, Renderer::Renderer *renderer)
{
    std::vector<CollisionPair *> *collisionPairs = new std::vector<CollisionPair *>();

    // Find the min and max x and y values of all objects
    float minX = __FLT_MAX__;
    float minY = __FLT_MAX__;

    float maxX = -__FLT_MAX__;
    float maxY = -__FLT_MAX__;

    float maxW = -__FLT_MAX__;
    float maxH = -__FLT_MAX__;

    std::vector<BroadPhaseCellData> cells;

    for (auto o : objects)
    {
        auto c = o->getCentre();
        if (std::isnan(c.x) || std::isnan(c.y))
            continue;

        if (c.x < minX)
            minX = c.x;
        if (c.x > maxX)
            maxX = c.x;
        if (c.y < minY)
            minY = c.y;
        if (c.y > maxY)
            maxY = c.y;

        auto aabb = o->getAABB();
        float w = aabb.max.x - aabb.min.x;
        float h = aabb.max.y - aabb.min.y;

        if (w > maxW)
            maxW = w;
        if (h > maxH)
            maxH = h;

        cells.push_back(BroadPhaseCellData{object : o, aabb : &aabb});
    }

    if (minX == __FLT_MAX__ || minY == __FLT_MAX__ || maxX == -__FLT_MAX__ || maxY == -__FLT_MAX__)
        return collisionPairs;

    // Calculate the dimensions of the grid
    float cellWidth = maxW * 1.2f;
    float cellHeight = maxH * 1.2f;

    minX -= cellWidth;
    minY -= cellHeight;
    maxX += cellWidth;
    maxY += cellHeight;

    float width = maxX - minX;
    float height = maxY - minY;

    int gridSizeX = std::ceil(width / cellWidth);
    int gridSizeY = std::ceil(height / cellHeight);

    gridSizeX = std::max(1, std::min(maxGridSize, gridSizeX));
    gridSizeY = std::max(1, std::min(maxGridSize, gridSizeY));

    // Calculate new width and height of each cell
    cellWidth = width / gridSizeX;
    cellHeight = height / gridSizeY;

    // debug info
    // std::cout << "minX: " << minX << std::endl;
    // std::cout << "minY: " << minY << std::endl;
    // std::cout << "maxX: " << maxX << std::endl;
    // std::cout << "maxY: " << maxY << std::endl;
    // std::cout << "maxW: " << maxW << std::endl;
    // std::cout << "maxH: " << maxH << std::endl;
    // std::cout << "width: " << width << std::endl;
    // std::cout << "height: " << height << std::endl;
    // std::cout << "grid size x: " << gridSizeX << ", grid size y: " << gridSizeY << std::endl;
    // std::cout << "cellWidth: " << cellWidth << std::endl;
    // std::cout << "cellHeight: " << cellHeight << std::endl;

    std::vector<BroadPhaseCellData *> **grid = new std::vector<BroadPhaseCellData *> *[gridSizeX];

    for (int x = 0; x < gridSizeX; x++)
    {
        grid[x] = new std::vector<BroadPhaseCellData *>[gridSizeY];
    }

    // populate the grid
    for (auto &d : cells)
    {
        auto [o, aabb] = d;

        // get the cell the object is in
        auto c = o->getCentre();
        int x = (c.x - minX) / cellWidth;
        int y = (c.y - minY) / cellHeight;

        x = std::max(0, std::min(gridSizeX - 1, x));
        y = std::max(0, std::min(gridSizeY - 1, y));

        // add the object to the grid
        grid[x][y].push_back(&d);
    }

    // check for collisions
    for (int x = 0; x < gridSizeX; x++)
    {
        for (int y = 0; y < gridSizeY; y++)
        {
            auto &cell = grid[x][y];

            // check every object in the current cell against all other objects in same and neighbouring cells
            for (auto d : cell)
            {
                auto [o, aabb] = *d;

                // iterate over neighbouring cells
                for (int xOffset = -1; xOffset <= 1; xOffset++)
                {
                    for (int yOffset = -1; yOffset <= 1; yOffset++)
                    {
                        int nx = x + xOffset;
                        int ny = y + yOffset;

                        if (nx < 0 || nx >= gridSizeX || ny < 0 || ny >= gridSizeY)
                            continue;

                        auto &neighbour = grid[nx][ny];

                        // check for collisions with current object
                        for (auto nd : neighbour)
                        {
                            auto [no, naabb] = *nd;

                            if (o == no)
                                continue;

                            // check if the objects aabb's are colliding
                            // TODO

                            // add collision pair to list
                            collisionPairs->push_back(new CollisionPair{o, no});
                        }
                    }
                }

                // end of neighbour iteration
            }

            // next cell
        }
    }

    // draw debug grid
    drawDebugGrid(grid, gridSizeX, gridSizeY, cellWidth, cellHeight, minX, minY, renderer);

    return collisionPairs;
}

void Physics::drawDebugGrid(std::vector<BroadPhaseCellData *> **grid, int gridSizeX, int gridSizeY, float cellWidth, float cellHeight, float gridX, float gridY, Renderer::Renderer *renderer)
{
    for (int x = 0; x < gridSizeX; x++)
    {
        for (int y = 0; y < gridSizeY; y++)
        {
            int cellX = x * cellWidth + gridX;
            int cellY = y * cellHeight + gridY;
            auto &cell = grid[x][y];

            const Renderer::Rect rect{
                topLeft : glm::vec2(cellX, cellY),
                w : cellWidth,
                h : cellHeight
            };

            Renderer::Color color{r : 0, g : 0, b : 0, a : 255};

            if (cell.size() > 10)
            {
                color.g = 255;

                std::cout << "x: " << x << ", y: " << y << ", size: " << cell.size() << std::endl;
                for (auto d : cell)
                {
                    auto [o, aabb] = *d;
                    std::cout << " id: " << o->getId() << "    x: " << o->getCentre().x << ", y: " << o->getCentre().y << std::endl;
                }
            }
            else if (cell.size() > 5)
            {
                color.r = 255;
            }
            else if (cell.size() > 2)
            {
                color.r = 150;
            }
            else if (cell.size() > 0)
            {
                color.r = 75;
            }
            else
            {
                continue;
            }

            renderer->rect(rect, color);
        }
    }
}

void Physics::cleanupCollisionPairs(std::vector<CollisionPair *> *collisionPairs)
{
    for (auto p : *collisionPairs)
    {
        delete p;
    }

    collisionPairs->clear();
    delete collisionPairs;
}