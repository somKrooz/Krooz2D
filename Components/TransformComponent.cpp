#include "TransformComponent.h"

namespace Krooz2D
{
    TransformComponent::TransformComponent(Vec2 Position , Vec2 Scale)
    {
        _trs.Pos = Position;
        _trs.Scale = Scale;
    }

    TransformComponent::TransformComponent(Vec2 Position , float Scale)
    {
        _trs.Pos = Position;
        _trs.Scale = Vec2(Scale , Scale);
    }

    Vec2& TransformComponent::GetScale(){
        return _trs.Scale;
    }

    Vec2& TransformComponent::GetPosition(){
        return _trs.Pos;
    }

    void TransformComponent::SetPosition(const Vec2& Position){
        _trs.Pos = Position;
    }

    void TransformComponent::SetScale(const Vec2& Scale){        
        _trs.Scale = Scale;
    }

    TrsDef& TransformComponent::GetTransform(){
        return _trs;
    }

    Mat4 TransformComponent::Get(){
        Mat4 _Matrix = Mat4::identity();
        _Matrix = Mat4::identity();
        _Matrix = _Matrix * Mat4::translate(_trs.Pos);
        _Matrix = _Matrix * Mat4::scale(_trs.Scale);

        return _Matrix;
    }
}
