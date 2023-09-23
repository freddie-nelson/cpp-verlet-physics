#pragma once

#include "./Objects/Object.h"

#include <vector>

namespace Physics
{
    class World
    {
    public:
        /**
         * Creates a new world
         *
         * @param gravity The gravity force to apply to all objects in the world
         * @param friction The friction force to apply to all objects in the world
         */
        World(glm::vec2 gravity = glm::vec2(0.0f, 0.0f), glm::vec2 friction = glm::vec2(0.0f, 0.0f));

        void step(float dt);

        float calculateKineticEnergy();

        glm::vec2 getGravity();
        void setGravity(glm::vec2 g);

        glm::vec2 getFriction();
        void setFriction(glm::vec2 f);

        std::vector<Object *> &getObjects();
        void addObject(Object *o);
        bool removeObject(const Object *o);

    private:
        glm::vec2 gravity;
        glm::vec2 friction;

        std::vector<Object *> objects;
    };
}