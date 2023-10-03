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

        // fix collisions with 2 massless objects
        if (totalInvMass == 0)
            totalInvMass = 1;

        float massCoeffA = invMassA / totalInvMass;
        float restitutionCoeff = std::min(a->getRestitution(), b->getRestitution()) + 0.6f;

        // halfed because we want to move each object half the depth
        auto moveVector = normal * depth * restitutionCoeff * massCoeffA;
        pa->move(moveVector);

        // edge resolution code
        if (edge != nullptr)
        {
            auto p1 = edge->getP1();
            auto p2 = edge->getP2();

            auto p1Pos = p1->getPosition();
            auto p2Pos = p2->getPosition();
            auto paPos = pa->getPosition();

            // calculate coefficient for where collision vertex lies on collision edge
            // collision code is from https://www.gamedev.net/tutorials/programming/math-and-physics/a-verlet-based-approach-for-2d-game-physics-r2714/#:~:text=Acceleration%20is%20change%20in%20velocity,change%20in%20the%20rotational%20velocity.
            // check here for explanations

            float t;
            if (std::abs(p1Pos.x - p2Pos.x) > std::abs(p1Pos.y - p2Pos.y))
            {
                t = (paPos.x - moveVector.x - p1Pos.x) / (p2Pos.x - p1Pos.x);
            }
            else
            {
                t = (paPos.y - moveVector.y - p1Pos.y) / (p2Pos.y - p1Pos.y);
            }

            float lambda = 1.0f / (t * t + (1 - t) * (1 - t));

            float edgeInvMass = p1->getInvMass() + p2->getInvMass();

            // fix collisions with massless object
            if (edgeInvMass == 0)
                edgeInvMass = 1;

            float p1MassCoeff = p1->getInvMass() / edgeInvMass;
            float p2MassCoeff = p2->getInvMass() / edgeInvMass;

            p1->setPosition(p1Pos - moveVector * (1 - t) * p1MassCoeff * lambda);
            p2->setPosition(p2Pos - moveVector * t * p2MassCoeff * lambda);
        }

        // apply friction
        float friction = std::fmax(a->getFriction(), b->getFriction());

        // get direction perpendicular to normal and in the opposite direction of the objects velocity
        glm::vec2 frictionDir = glm::vec2(-normal.y, normal.x);

        if (glm::dot(frictionDir, pa->getVelocity()) > 0)
        {
            frictionDir = -frictionDir;
        }

        // this should be negative
        // as friction direction is in opposite direction to velocity
        float frictionDirVelocity = glm::dot(frictionDir, pa->getVelocity());
        float frictionCoeff = a->getType() == Physics::ObjectType::CircleObject ? 0.1 : 1;

        pa->setPosition(pa->getPosition() - frictionDir * frictionDirVelocity * friction * frictionCoeff);

        // if (std::isnan(pa->getPosition().x))
        // {
        //     std::cout << "id: " << a->getId() << ", pa: " << pa->getPosition().x << ", " << pa->getPosition().y << std::endl;
        // }

        // std::cout << "velocity after: " << pa->getVelocity().x << ", " << pa->getVelocity().y << std::endl;
    }
}