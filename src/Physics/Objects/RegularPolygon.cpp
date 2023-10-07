#include "../../../include/Physics/Objects/RegularPolygon.h"

#include <stdexcept>
#include <iostream>
#include <numbers>
#include <glm/gtx/rotate_vector.hpp>
#include <unordered_map>
#include <utility>

Physics::RegularPolygon::RegularPolygon(glm::vec2 centre, float radius, int sides, float mass, float restitution, float friction, float drag) : Object(ObjectType::PolygonObject, *(new std::vector<glm::vec2>{centre}), mass, restitution, friction, drag)
{
    setCentre(centre);
    setRadius(radius);
    setSides(sides);
}

void Physics::RegularPolygon::setCentre(glm::vec2 c)
{
    centre = c;

    // move every point by the difference
    // between the new centre and old centre
    for (auto p : getPoints())
    {
        p->move(c - getCentre());
    }
}

float Physics::RegularPolygon::getRadius()
{
    return radius;
}

void Physics::RegularPolygon::setRadius(float r)
{
    if (r < 0)
        throw std::invalid_argument("Radius must be greater than or equal to 0.");

    radius = r;

    if (sides != 0)
        setSides(sides);
}

int Physics::RegularPolygon::getSides()
{
    return sides;
}

void Physics::RegularPolygon::setSides(int s)
{
    if (s < 3)
        throw std::invalid_argument("Sides must be greater than or equal to 3.");

    sides = s;

    // update points
    std::vector<glm::vec2> pVecs;

    auto c = getCentre();
    // pVecs.push_back(c);

    float angle = 2.0f * std::numbers::pi / static_cast<float>(sides);
    glm::vec2 dir(0, -1);

    for (int i = 0; i < sides; i++)
    {
        auto pointDir = glm::rotate(dir, angle * i);
        glm::vec2 point = c + pointDir * radius;
        pVecs.push_back(point);
    }

    setPoints(pVecs);

    // add edges
    auto points = getPoints();

    std::vector<Edge *> edges;

    for (int i = 0; i < sides; i++)
    {
        int nextI = (i + 1) % sides;

        edges.push_back(new Edge(points[i], points[nextI]));
    }

    // add braces
    for (int i = 0; i < sides; i++)
    {
        // connect to opposite point
        edges.push_back(new Edge(points[i], points[(i + sides / 2) % sides], true));

        // additional braces
        int i1 = (i + 3) % sides;
        int i2 = (i + 7) % sides;
        int i3 = (i + 11) % sides;
        std::vector<int> additionalBraces = {i1,
                                             i2,
                                             i3};

        for (auto j : additionalBraces)
        {
            // prevent adding of duplicate braces
            bool exists = false;
            for (auto e : edges)
            {
                if ((e->getP1() == points[i] && e->getP2() == points[j]) || (e->getP1() == points[j] && e->getP2() == points[i]))
                {
                    exists = true;
                    break;
                }
            }

            if (!exists)
                edges.push_back(new Edge(points[i], points[j], true));
        }
    }

    setEdges(edges);
}

Physics::AABB Physics::RegularPolygon::getAABB()
{
    auto centre = getCentre();
    auto r = glm::vec2(radius, radius);

    return AABB{min : centre - r, max : centre + r};
}
