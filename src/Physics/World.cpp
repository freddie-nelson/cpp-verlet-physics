#include "../../include/Physics/World.h"
#include "../../include/Physics/Solvers/solvePosition.h"
#include "../../include/Physics/Solvers/solveGravity.h"
#include "../../include/Physics/Solvers/solveFriction.h"
#include "../../include/Physics/Constraints/windowConstraint.h"
#include "../../include/Physics/Collision/BroadPhase.h"
#include "../../include/Physics/Collision/NarrowPhase.h"
#include "../../include/Physics/Collision/Resolution.h"

#include <glm/glm.hpp>
#include <iostream>
#include <stdexcept>

Physics::World::World(int windowWidth, int windowHeight, glm::vec2 gravity, float friction) : windowWidth(windowWidth), windowHeight(windowHeight), gravity(gravity), friction(friction)
{
}

void Physics::World::step(float dt, int substeps, Renderer::Renderer *renderer)
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
            // solveFriction(p, friction, dt);

            // update acceleration
            p->setAcceleration(p->getNewAcceleration());
            p->setNewAcceleration(glm::vec2(0.0, 0.0));
        }
    }

    // solve constraints
    float subDt = dt / substeps;

    for (int i = 0; i < substeps; i++)
    {
        // apply constraints
        applyWindowConstraint(&objects, windowWidth, windowHeight);

        // run broad phase collision detection
        auto collisionPairs = broadPhase(objects, 200, renderer);

        // run narrow phase collision detection
        auto manifolds = narrowPhase(collisionPairs);
        // auto manifolds = narrowPhaseSlow(&objects);

        // check for missing manifolds
        // this code proves that any difference between narrow + broad phase and narrow phase alone is solely due to the broad phase
        // collecting manifolds in a different order than the slow method

        // auto manifoldsSlow = narrowPhaseSlow(&objects);
        // std::vector<Manifold *> reordered;

        // for (auto ms : *manifoldsSlow)
        // {
        //     bool found = false;

        //     for (auto m : *manifolds)
        //     {
        //         if (m->a->getId() == ms->a->getId() && m->b->getId() == ms->b->getId())
        //         {
        //             found = true;
        //             reordered.push_back(m);
        //             break;
        //         }
        //     }

        //     // if working then the following should never be printed
        //     if (!found)
        //     {
        //         std::cout << "Manifold not found" << std::endl;
        //     }
        // }

        // run collision resolution
        resolveCollisions(manifolds);

        // cleanup
        cleanupCollisionPairs(collisionPairs);
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

float Physics::World::getFriction()
{
    return friction;
}

void Physics::World::setFriction(float f)
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
