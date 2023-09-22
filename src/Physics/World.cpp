#include "../../include/Physics/World.h"

Physics::World::World()
{
}

void Physics::World::step(float dt)
{
    // apply velocity
    for (auto o : objects)
    {
        o->move(o->getVelocity() * dt);
    }
}

std::vector<Physics::Object *> Physics::World::getObjects()
{
    return objects;
}

void Physics::World::addObject(Physics::Object *o)
{
    objects.push_back(o);
}

bool Physics::World::removeObject(const Physics::Object *o)
{
    for (auto it = objects.begin(); it < objects.end(); it++)
    {
        if (*it.base() == o)
        {
            objects.erase(it);
            return true;
        }
    }

    return false;
}