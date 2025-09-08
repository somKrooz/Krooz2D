#pragma once

#include "Maths.h"
#include "vector"

struct CollisionDim {
    Vec2 Position;
    Vec2 Size;
};

struct BoundingBox
{
    float Left;
    float Right;
    float Top;
    float Bottom;
};


class Platformer
{
    private:
    BoundingBox PlayerBound;
    bool IsOnGround = false;

    public:
    Platformer(Vec2& Position, Vec2& Velocity ,BoundingBox PlayerDim , std::vector<CollisionDim> dims);
    static void TopDownCollisionModel(Vec2& PlayerPosition,BoundingBox PlayerBound , std::vector<CollisionDim>& cols);
    bool GetOnGround();
};
