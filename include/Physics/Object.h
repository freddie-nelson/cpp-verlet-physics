#include <glm/vec2.hpp>

namespace Physics
{
    class Object
    {
    public:
        glm::vec2 position;
        glm::vec2 velocity;

        /**
         * Changes the object's position by the given vector.
         */
        void move(glm::vec2 move);
    };
}