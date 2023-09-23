#include "../../../include/Physics/Solvers/solvePosition.h"

void Physics::solvePosition(Point *p, float dt)
{
    glm::vec2 currPos = p->getPosition();
    glm::vec2 oldPos = p->getOldPosition();
    glm::vec2 acc = p->getAcceleration();

    glm::vec2 newPos = currPos + (currPos - oldPos) + (acc * (dt * dt));

    p->setOldPosition(currPos);
    p->setPosition(newPos);
}