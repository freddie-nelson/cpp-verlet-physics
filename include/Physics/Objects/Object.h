#pragma once

#include <glm/vec2.hpp>
#include <string>
#include <vector>

namespace Physics
{
    class Object
    {
    public:
        glm::vec2 getVelocity();
        void setVelocity(glm::vec2 v);

        virtual glm::vec2 getPosition() = 0;
        virtual void setPosition(glm::vec2 p) = 0;

        virtual std::vector<float> getSize() = 0;
        virtual bool setSize(std::vector<float> size) = 0;

        /**
         * Changes the object's position by the given vector.
         */
        virtual void move(glm::vec2 move) = 0;

    private:
        glm::vec2 velocity;
    };
}