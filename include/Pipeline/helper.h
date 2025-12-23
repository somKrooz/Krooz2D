#pragma once
#include "Utility/Types.h"
#include "Utility/Maths.h"
#include "Components/TransformComponent.h"

namespace Helper
{
    BBox MakeBoundingBox(TransformComponent &src)
    {
        Vec2 Pos = src.GetPosition();
        Vec2 Scale = src.GetScaleVec();

        return {Pos.x, Pos.x + Scale.x, Pos.y, Pos.y + Scale.y};
    }
    BBox MakeBoundingBox(Vec2 &Position, Vec2 &Scale)
    {
        return {Position.x, Position.x + Scale.x, Position.y, Position.y + Scale.y};
    }

    bool AABB(const BBox& a, const BBox& b)
    {
        return !(a.maxX <= b.minX ||
                a.minX >= b.maxX ||
                a.maxY <= b.minY ||
                a.minY >= b.maxY);
    }

}