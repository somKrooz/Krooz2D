#pragma once
#include "Types.h"


namespace Krooz2D{

    struct TrsDef{
        Vec2 Pos = Vec2::Zero();
        Vec2 Scale = Vec2::Zero();
    };

    struct TransformComponent{
        TrsDef _trs;

        TransformComponent() : _trs{} {}
        TransformComponent(Vec2 Position , Vec2 Scale) ;
        TransformComponent(Vec2 Position , float Scale);
        
        Vec2& GetPosition();
        Vec2& GetScale();
        TrsDef& GetTransform();

        void SetPosition(const Vec2& position);
        void SetScale(const Vec2& position);

        Mat4 Get();
    };
}
