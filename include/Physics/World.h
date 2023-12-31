#pragma once

#include "./Objects/Object.h"
#include "./Constraints/Constraint.h"
#include "../Renderer/Renderer.h"
#include "./Collision/Manifold.h"

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
         */
        World(int windowWidth, int windowHeight, glm::vec2 gravity = glm::vec2(0.0f, 0.0f), float drag = 0.0f);

        void step(float dt, int substeps, Renderer::Renderer *renderer);

        float calculateKineticEnergy();

        glm::vec2 getGravity();
        void setGravity(glm::vec2 g);

        float getDrag();
        void setDrag(float d);

        std::vector<Object *> &getObjects();
        void addObject(Object *o);
        bool removeObject(const Object *o);

        std::vector<Constraint *> &getConstraints();
        void addConstraint(Constraint *c);
        bool removeConstraint(const Constraint *c);

    private:
        int windowWidth;
        int windowHeight;

        glm::vec2 gravity;
        float drag;

        std::vector<Object *> objects;
        std::vector<Constraint *> constraints;

        void compareManifolds(std::vector<Manifold *> *a, std::vector<Manifold *> *b);
        void drawDebugManifolds(std::vector<Manifold *> *manifolds, Renderer::Renderer *renderer);
    };
}