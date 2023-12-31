#pragma once

#include "../../Utility/EventEmitter.h"
#include "./Point.h"
#include "./AABB.h"
#include "./Edge.h"

#include <glm/vec2.hpp>
#include <string>
#include <vector>

namespace Physics
{
    enum ObjectType
    {
        CircleObject,
        PolygonObject,
    };

    struct EventData
    {
        std::string event;
        void *data;
    };

    /**
     * Base class for all objects in the physics engine.
     *
     * This class is abstract and should not be instantiated.
     *
     * This class is also an event emitter and emits the following events:
     *
     * - collision: emitted when the object collides with another object
     *   `data`: `Manifold *`
     * - resolution: emitted when the object is resolved from a collision
     *   `data`: `Manifold *`
     */
    class Object : public EventEmitter<EventData>
    {
    public:
        Object(ObjectType type, std::vector<glm::vec2> &points, float mass = 1.0f, float restitution = 1.0f, float friction = 0.0f, float drag = 0.0f);

        /**
         * Moves the object by the given vector.
         */
        void move(glm::vec2 move);

        /**
         * Applies the given force to the object at the given point.
         *
         * @param force The force to apply
         * @param point The point to apply the force at (must be a point on the object or it's centre)
         */
        void applyForce(glm::vec2 force, glm::vec2 point);

        float getMass();

        /**
         * Sets the mass of the point.
         *
         * A mass of 0 will make the object immovable/static.
         */
        void setMass(float m);

        float getInvMass();

        float getRestitution();
        void setRestitution(float r);

        float getFriction();
        void setFriction(float f);

        float getDrag();
        void setDrag(float d);

        std::vector<Point *> &getPoints();

        /**
         * Sets the points of the object.
         *
         * The points must be in clockwise order.
         *
         * @param p The points to set
         */
        void setPoints(std::vector<glm::vec2> &p);

        void addPoint(glm::vec2 p);
        void removePoint(glm::vec2 p);
        bool hasPoint(glm::vec2 p);

        std::vector<Edge *> &getEdges();
        void setEdges(std::vector<Edge *> &edges);

        void addEdge(Edge *e);
        void removeEdge(Edge *e);

        virtual void setCentre(glm::vec2 c) = 0;
        virtual glm::vec2 getCentre();

        virtual AABB getAABB();

        ObjectType getType();
        int getId();

    private:
        static int nextId;

        ObjectType type;
        int id;

        float mass = 1.0f;
        float restitution = 1.0f;
        float friction = 0.0f;
        float drag = 0.0f;

        std::vector<Point *> points;
        std::vector<Edge *> edges;

        Point *getPoint(glm::vec2 p);
    };
}