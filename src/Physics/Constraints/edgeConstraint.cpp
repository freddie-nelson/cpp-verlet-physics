#include "../../../include/Physics/Constraints/edgeConstraint.h"

#include <glm/glm.hpp>

void Physics::applyEdgeConstraint(std::vector<Object *> *objects)
{
    for (auto o : *objects)
    {
        for (auto e : o->getEdges())
        {
            auto a = e->getP1();
            auto b = e->getP2();

            auto aToB = b->getPosition() - a->getPosition();
            auto aToBLen = glm::length(aToB);

            auto diff = aToBLen - e->getLength();
            auto dir = glm::normalize(aToB);

            auto offset = dir * diff * e->getStiffness() * 0.5f;

            a->setPosition(a->getPosition() + offset);
            b->setPosition(b->getPosition() - offset);
        }
    }
}