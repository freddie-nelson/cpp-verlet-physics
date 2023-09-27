#include "../../../include/Physics/Constraints/windowConstraint.h"
#include "../../../include/Physics/Objects/Circle.h"

void Physics::applyWindowConstraint(std::vector<Object *> *objects, int windowWidth, int windowHeight)
{
    for (Object *object : *objects)
    {
        for (auto p : object->getPoints())
        {
            auto position = p->getPosition();
            auto velocity = p->getVelocity();
            float restitution = p->getRestitution();

            // use offset for circle radius
            // all other objects use points and edges so no need for offset
            glm::vec2 offset = glm::vec2(0, 0);

            glm::vec2 exitVelocity = glm::vec2(velocity.x, velocity.y) * -(restitution);

            if (object->getType() == ObjectType::CircleObject)
            {
                auto circle = static_cast<Circle *>(object);
                offset.x += circle->getRadius();
                offset.y += circle->getRadius();
            }

            if (position.x - offset.x < 0)
                position.x = offset.x + exitVelocity.x;
            else if (position.x + offset.x > windowWidth)
                position.x = windowWidth - offset.x + exitVelocity.x;

            if (position.y - offset.y < 0)
                position.y = offset.y + exitVelocity.y;
            else if (position.y + offset.y > windowHeight)
                position.y = windowHeight - offset.y + exitVelocity.y;

            p->setPosition(position);
        }
    }
}