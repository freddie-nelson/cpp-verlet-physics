#include "../../../include/Physics/Collision/Resolution.h"

#include <glm/glm.hpp>
#include <math.h>
#include <iostream>

void Physics::resolveCollisions(std::vector<Manifold *> *manifolds)
{
    for (auto m : *manifolds)
    {
        auto [a, b, pa, pb, edge, normal, depth] = *m;

        // std::cout << "start collision resolution" << std::endl;
        // std::cout << "mass: " << a->getMass() << std::endl;
        // std::cout << "velocity before: " << pa->getVelocity().x << ", " << pa->getVelocity().y << std::endl;

        float invMassA = a->getInvMass();
        float invMassB = b->getInvMass();
        float totalInvMass = invMassA + invMassB;

        float massCoeffA = invMassA / totalInvMass;
        float restitutionCoeff = std::min(a->getRestitution(), b->getRestitution());

        // halfed because we want to move each object half the depth
        auto moveVector = normal * depth * (restitutionCoeff + 0.6f) * massCoeffA;
        pa->move(moveVector);

        // if (std::isnan(pa->getPosition().x))
        // {
        //     std::cout << "id: " << a->getId() << ", pa: " << pa->getPosition().x << ", " << pa->getPosition().y << std::endl;
        // }

        // std::cout << "velocity after: " << pa->getVelocity().x << ", " << pa->getVelocity().y << std::endl;
    }
}