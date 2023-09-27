#include "./Object.h"

namespace Physics
{
    class Rect : public Object
    {
    public:
        Rect(glm::vec2 c, float w, float h, float mass = 1.0f, float restitution = 1.0f, float friction = 0.0f, float drag = 0.0f);

        void setCentre(glm::vec2 c);

        float getWidth();
        void setWidth(float w);

        float getHeight();
        void setHeight(float h);

    private:
        glm::vec2 centre;
        float width;
        float height;
    };
}