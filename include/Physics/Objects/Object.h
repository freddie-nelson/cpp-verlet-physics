#pragma once

#include "./Point.h"
#include "./AABB.h"

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
        Object(ObjectType type, std::vector<glm::vec2> &points, float mass = 1.0f, float restitution = 1.0f, float friction = 0.0f);

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

        float getFriction();
        void setFriction(float f);

        std::vector<Point *> &getPoints();
        void setPoints(std::vector<glm::vec2> &p);

        void addPoint(glm::vec2 p);
        void removePoint(glm::vec2 p);
        bool hasPoint(glm::vec2 p);

        glm::vec2 getCentre();

        virtual AABB getAABB() = 0;

        ObjectType getType();
        int getId();

    private:
        static int nextId;

        ObjectType type;
        int id;

        float mass = 1.0f;
        float restitution = 1.0f;
        float friction = 0.0f;

        std::vector<Point *> points;

        Point *getPoint(glm::vec2 p);
    };
}