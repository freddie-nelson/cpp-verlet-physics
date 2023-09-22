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
         * Applies the given force to the object at it's centre.
         */
        void applyForce(glm::vec2 force);

        float getMass();
        void setMass(float m);

        float getRestitution();
        void setRestitution(float r);

        glm::vec2 getCentre();
        void setCentre(glm::vec2 c);

        glm::vec2 getVelocity();
        void setVelocity(glm::vec2 v);

        virtual std::vector<float> getSize() = 0;
        virtual bool setSize(std::vector<float> size) = 0;

    private:
        float mass;
        float restitution;

        glm::vec2 centre;
        glm::vec2 velocity;
    };
}