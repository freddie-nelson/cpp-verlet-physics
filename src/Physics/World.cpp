#include "../../include/Physics/World.h"
#include "../../include/Physics/Solvers/solvePosition.h"
#include "../../include/Physics/Solvers/solveGravity.h"
#include "../../include/Physics/Solvers/solveFriction.h"
#include "../../include/Physics/Collision/NarrowPhase.h"
#include "../../include/Physics/Collision/Resolution.h"

#include <glm/glm.hpp>
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
        auto points = o->getPoints();

        for (auto p : points)
        {
            // update position
            solvePosition(p, dt);

            // apply forces
            // calculates o.newAcceleration
            solveGravity(p, gravity, dt);

            // apply friction
            solveFriction(p, friction, dt);

            // update acceleration
            p->setAcceleration(p->getNewAcceleration());
            p->setNewAcceleration(glm::vec2(0.0, 0.0));
        }
    }

    // solve constraints
    int substeps = 8;
    float subDt = dt / substeps;

    for (int i = 0; i < subDt; i++)
    {
        // run broad phase collision detection
        // TODO

        // run narrow phase collision detection
        auto manifolds = narrowPhase(objects);

        // run collision resolution
        resolveCollisions(manifolds);

        // delete manifolds
        cleanupManifolds(manifolds);
    }

    // auto o = objects[0]->getPoints()[0];
    // std::cout << std::endl
    //           << "x: " << o->getPosition().x << " y: " << o->getPosition().y << std::endl
    //           << "ax: " << o->getAcceleration().x << " ay: " << o->getAcceleration().y << std::endl;
}

float Physics::World::calculateKineticEnergy()
{
    float ke = 0.0f;

    for (auto o : objects)
    {
        auto points = o->getPoints();

        for (auto p : points)
        {
            glm::vec2 velocity = p->getPosition() - p->getOldPosition();

            ke += 0.5f * o->getMass() * glm::dot(velocity, velocity);
        }
    }

    return ke;
}

glm::vec2 Physics::World::getGravity()
{
    return gravity;
}

void Physics::World::setGravity(glm::vec2 g)
{
    gravity = g;
}

glm::vec2 Physics::World::getFriction()
{
    return friction;
}

void Physics::World::setFriction(glm::vec2 f)
{
    friction = f;
}

std::vector<Physics::Object *> &Physics::World::getObjects()
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
