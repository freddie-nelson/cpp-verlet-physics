#include "./Object.h"

#include <vector>

namespace Physics
{
    class World
    {
    public:
        World();

        void step(float dt);

    private:
        std::vector<Object> objects;
    };
}