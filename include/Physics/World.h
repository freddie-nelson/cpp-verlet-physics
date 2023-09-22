#pragma once

#include "./Objects/Object.h"

#include <vector>

namespace Physics
{
    class World
    {
    public:
        World();

        void step(float dt);

        std::vector<Object *> getObjects();
        void addObject(Object *o);
        bool removeObject(const Object *o);

    private:
        std::vector<Object *> objects;
    };
}