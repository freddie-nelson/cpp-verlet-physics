#include "../../../include/Physics/Collision/Resolution.h"

#include <glm/glm.hpp>
#include <math.h>
#include <iostream>

void Physics::resolveCollisions(std::vector<Manifold *> &manifolds)
{
    for (auto m : manifolds)
    {
        auto [a, b, pa, pb, normal, depth] = *m;

        std::cout << "start collision resolution" << std::endl;
        std::cout << "mass: " << a->getMass() << std::endl;
        std::cout << "velocity before: " << pa->getVelocity().x << ", " << pa->getVelocity().y << std::endl;

        float invMassA = a->getInvMass();
        float invMassB = b->getInvMass();
        float totalInvMass = invMassA + invMassB;

        float massCoeffA = invMassA / totalInvMass;
        float massCoeffB = invMassB / totalInvMass;

        float restitutionCoeff = std::min(a->getRestitution(), b->getRestitution());

        auto moveVector = -normal * depth * 0.5f * (restitutionCoeff + 1.0f);

        pa->move(moveVector * massCoeffA);
        pb->move(-moveVector * massCoeffB);

        std::cout << "velocity after: " << pa->getVelocity().x << ", " << pa->getVelocity().y << std::endl;
    }
}