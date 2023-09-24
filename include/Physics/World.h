#pragma once

#include "./Objects/Object.h"
#include "../Renderer/Renderer.h"

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
        World(int windowWidth, int windowHeight, glm::vec2 gravity = glm::vec2(0.0f, 0.0f), float friction = 0.0f);

        void step(float dt, int substeps, Renderer::Renderer *renderer);

        float calculateKineticEnergy();

        glm::vec2 getGravity();
        void setGravity(glm::vec2 g);

        float getFriction();
        void setFriction(float f);

        std::vector<Object *> &getObjects();
        void addObject(Object *o);
        bool removeObject(const Object *o);

    private:
        int windowWidth;
        int windowHeight;

        glm::vec2 gravity;
        float friction;

        std::vector<Object *> objects;
    };
}