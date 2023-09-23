#include "../../../include/Physics/Collision/Resolution.h"

void Physics::resolveCollisions(std::vector<Manifold *> &manifolds, float dt)
{
    for (auto m : manifolds)
    {
        auto [a, b, pa, normal, depth] = *m;

        float invMassA = a->getInvMass();
        float invMassB = b->getInvMass();

        float massCoeff = (invMassA / (invMassA + invMassB));

        auto moveVector = -normal * depth * massCoeff * dt;
        pa->move(moveVector);
    }
}