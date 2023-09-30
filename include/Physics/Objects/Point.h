#pragma once

#include <glm/vec2.hpp>
#include <string>
#include <vector>

namespace Physics
{
    class Point
    {
    public:
        Point(glm::vec2 position, float mass = 1.0f, float restitution = 1.0f, float friction = 0.0f, float drag = 0.0f);

        /**
         * Changes the point's position by the given vector.
         */
        void move(glm::vec2 move);

        /**
         * Applies the given force to the point.
         */
        void applyForce(glm::vec2 force);

        float getMass();

        /**
         * Sets the mass of the point.
         *
         * A mass of 0 will make the object immovable/static.
         */
        void setMass(float m);

        float getInvMass();

        float getRestitution();
        void setRestitution(float r);

        float getFriction();
        void setFriction(float f);

        float getDrag();
        void setDrag(float d);

        glm::vec2 &getPosition();
        void setPosition(glm::vec2 p);

        glm::vec2 &getOldPosition();
        void setOldPosition(glm::vec2 p);

        glm::vec2 getVelocity();

        glm::vec2 &getAcceleration();
        void setAcceleration(glm::vec2 a);

        glm::vec2 &getNewAcceleration();
        void setNewAcceleration(glm::vec2 a);

    private:
        float mass = 1.0f;
        float restitution = 1.0f;
        float friction = 0.0f;
        float drag = 0.0f;

        glm::vec2 position;
        glm::vec2 oldPosition;

        glm::vec2 acceleration = glm::vec2(0.0f, 0.0f);
        glm::vec2 newAcceleration = glm::vec2(0.0f, 0.0f);
    };
}