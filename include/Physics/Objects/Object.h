#pragma once

#include <glm/vec2.hpp>
#include <string>
#include <vector>

namespace Physics
{
    class Object
    {
    public:
        /**
         * Changes the object's centre by the given vector.
         */
        void move(glm::vec2 move);

        /**
         * Applies the given force to the object at it's centre on the next step.
         */
        void applyForce(glm::vec2 force);

        float getMass();
        void setMass(float m);

        float getRestitution();
        void setRestitution(float r);

        glm::vec2 getFriction();

        /**
         * Sets the friction of the object.
         *
         * @param f The friction to set (values will be clamped between 0 and 1)
         */
        void setFriction(glm::vec2 f);

        glm::vec2 getCentre();
        void setCentre(glm::vec2 c);

        glm::vec2 getVelocity();
        void setVelocity(glm::vec2 v);

        glm::vec2 getAcceleration();
        void setAcceleration(glm::vec2 a);

        glm::vec2 getNewAcceleration();
        void setNewAcceleration(glm::vec2 a);

        virtual std::vector<float> getSize() = 0;
        virtual bool setSize(std::vector<float> size) = 0;

    private:
        float mass = 1.0f;
        float restitution = 1.0f;
        glm::vec2 friction = glm::vec2(1.0f, 1.0f);

        glm::vec2 centre;
        glm::vec2 acceleration;
        glm::vec2 newAcceleration;
        glm::vec2 velocity;
    };
}