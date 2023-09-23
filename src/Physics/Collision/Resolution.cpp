#include "../../../include/Physics/Collision/Resolution.h"

#include <glm/glm.hpp>
#include <math.h>
#include <iostream>

void Physics::resolveCollisions(std::vector<Manifold *> &manifolds)
{
    for (auto m : manifolds)
    {
        auto [a, b, pa, normal, depth] = *m;

        glm::vec2 oldPosition = pa->getPosition();

        auto moveVector = -normal * depth * 0.5f;
        pa->move(moveVector);

        // handle restitution
        float invMassA = a->getInvMass();
        float invMassB = b->getInvMass();

        float massCoeff = (invMassA / (invMassA + invMassB));
        float restitutionCoeff = std::min(a->getRestitution(), b->getRestitution());

        glm::vec2 velocity = pa->getVelocity();
        float velocityAlongNormal = glm::dot(velocity, normal);
        glm::vec2 normalVelocity = normal * velocityAlongNormal;

        pa->setOldPosition((restitutionCoeff == 0 ? pa->getPosition() : oldPosition) + normalVelocity * restitutionCoeff);
    }
}