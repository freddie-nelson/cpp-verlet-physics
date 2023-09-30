#pragma once

namespace Physics
{
    class Constraint
    {
    public:
        virtual void solve(float dt) = 0;
    };
}