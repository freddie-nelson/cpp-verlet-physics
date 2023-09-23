#include "../../include/Physics/World.h"
#include "../../include/Physics/Solvers/solvePosition.h"
#include "../../include/Physics/Solvers/solveGravity.h"
#include "../../include/Physics/Solvers/solveDamping.h"
#include "../../include/Physics/Solvers/solveVelocity.h"

#include <iostream>
#include <stdexcept>

Physics::World::World(glm::vec2 gravity, glm::vec2 friction) : gravity(gravity), friction(friction)
{
    if (friction.x < 0 || friction.x > 1 || friction.y < 0 || friction.y > 1)
        throw std::invalid_argument("Friction must be between 0 and 1");
}

void Physics::World::step(float dt)
{
    // run solvers
    for (auto o : objects)
    {
        // update position
        solvePosition(o, dt);

        // apply forces
        // calculates o.newAcceleration
        solveGravity(o, gravity, dt);

        // calculate new velocity
        solveVelocity(o, dt);

        // apply damping
        solveDamping(o, friction, dt);

        // update acceleration
        o->setAcceleration(o->getNewAcceleration());
        o->setNewAcceleration(glm::vec2(0.0, 0.0));
    }

    // auto o = objects[0];
    // std::cout << std::endl
    //           << "x: " << o->getCentre().x << " y: " << o->getCentre().y << std::endl
    //           << "vx: " << o->getVelocity().x << " vy: " << o->getVelocity().y << std::endl
    //           << "ax: " << o->getAcceleration().x << " ay: " << o->getAcceleration().y << std::endl;
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