#include <glm/vec2.hpp>

namespace Physics
{
    class Object
    {
    public:
        glm::vec2 getVelocity();
        glm::vec2 setVelocity(glm::vec2 v);

        virtual glm::vec2 getPosition();
        virtual glm::vec2 setPosition();

        /**
         * Changes the object's position by the given vector.
         */
        virtual void move(glm::vec2 move);

    private:
        glm::vec2 velocity;
    };
}