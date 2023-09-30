#include "../../../include/Physics/Constraints/edgeConstraint.h"

#include <glm/glm.hpp>

void Physics::applyEdgeConstraint(std::vector<Object *> *objects)
{
    for (auto o : *objects)
    {
        for (auto e : o->getEdges())
        {
            e->solve();
        }
    }
}