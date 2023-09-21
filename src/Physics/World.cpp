#include "../../include/Physics/World.h"

Physics::World World()
{
}

void Physics::World::step(float dt)
{
    // apply velocity
    for (auto o : objects)
    {
        o.move(o.getVelocity() * dt);
    }
}