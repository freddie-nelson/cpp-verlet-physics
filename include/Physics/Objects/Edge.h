#include "./Point.h"

namespace Physics
{

    class Edge
    {
    public:
        Edge(Point *p1, Point *p2, float length = -1.0f, float stiffness = 1.0f);

        Point *getP1();
        void setP1(Point *p);

        Point *getP2();
        void setP2(Point *p);

        float getLength();

        /**
         * Sets the length of the edge.
         *
         * If the length is set to -1, the length will be calculated automatically from
         * the current distance between p1 and p2.
         *
         * @param l The length of the edge.
         */
        void setLength(float l);

        float getStiffness();

        /**
         * Sets the stiffness of the edge.
         *
         * The stiffness is a value between 0 and 1, where 0 is a completely flexible edge and 1 is a completely stiff edge.
         *
         * @param s The stiffness of the edge.
         */
        void setStiffness(float s);

    private:
        Point *p1;
        Point *p2;

        float length = -1.0f;
        float stiffness = 0.0f;
    };
}