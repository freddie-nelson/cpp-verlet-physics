#include "../../../include/Physics/Objects/Rect.h"

#include <stdexcept>

Physics::Rect::Rect(glm::vec2 c, float w, float h, float mass, float restitution, float friction, float drag) : Object(ObjectType::PolygonObject, *(new std::vector<glm::vec2>{c}), mass, restitution, friction, drag)
{
    setCentre(c);
    setWidth(w);
    setHeight(h);
}

void Physics::Rect::setCentre(glm::vec2 c)
{
    centre = c;

    auto w = getWidth();
    auto h = getHeight();

    // set points
    std::vector<glm::vec2> pVecs = {
        c + glm::vec2(-w / 2, -h / 2),
        c + glm::vec2(w / 2, -h / 2),
        c + glm::vec2(w / 2, h / 2),
        c + glm::vec2(-w / 2, h / 2)};

    setPoints(pVecs);

    // set edges
    auto points = getPoints();

    std::vector<Edge *> edges = {
        // edges
        new Edge(points[0], points[1]),
        new Edge(points[1], points[2]),
        new Edge(points[2], points[3]),
        new Edge(points[3], points[0]),

        // brace
        new Edge(points[0], points[2], true),
        new Edge(points[1], points[3], true)};

    setEdges(edges);
};

float Physics::Rect::getWidth()
{
    return width;
}

void Physics::Rect::setWidth(float w)
{
    if (w < 0)
        throw std::invalid_argument("Width must be greater than or equal to 0.");

    width = w;

    setCentre(centre);
}

float Physics::Rect::getHeight()
{
    return height;
}

void Physics::Rect::setHeight(float h)
{
    if (h < 0)
        throw std::invalid_argument("Height must be greater than or equal to 0.");

    height = h;

    setCentre(centre);
}
