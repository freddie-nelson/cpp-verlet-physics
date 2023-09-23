#pragma once

#include "./Point.h"

#include <glm/vec2.hpp>
#include <string>
#include <vector>

namespace Physics
{
    enum ObjectType
    {
        CircleObject
    };

    class Object
    {
    public:
        Object(ObjectType type, std::vector<glm::vec2> &points, float mass = 1.0f, float restitution = 1.0f, glm::vec2 friction = glm::vec2(0.0f, 0.0f));

        /**
         * Moves the object by the given vector.
         */
        void move(glm::vec2 move);

        /**
         * Applies the given force to the object at the given point.
         *
         * @param force The force to apply
         * @param point The point to apply the force at (must be a point on the object)
         */
        void applyForce(glm::vec2 force, glm::vec2 point);

        float getMass();
        void setMass(float m);

        float getInvMass();

        float getRestitution();
        void setRestitution(float r);

        glm::vec2 getFriction();
        void setFriction(glm::vec2 f);

        std::vector<Point *> getPoints();
        void setPoints(std::vector<glm::vec2> &p);

        void addPoint(glm::vec2 p);
        void removePoint(glm::vec2 p);
        bool hasPoint(glm::vec2 p);

        ObjectType getType();

    private:
        ObjectType type;

        float mass = 1.0f;
        float restitution = 1.0f;
        glm::vec2 friction = glm::vec2(0.0f, 0.0f);

        std::vector<Point *> points;

        Point *getPoint(glm::vec2 p);
    };
}