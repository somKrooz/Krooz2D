#pragma once
#include "Maths.h"
#include "StateManger.h"

class Camera2D
{
    private:
    Vec2 pos;
    Vec2 size = Vec2(1280/2 , 720/2);
    Mat4 m_matrix = Mat4::identity();

    public:
    void Follow(Vec2 target , Vec2 Size, float delta) {
        StateManger::SetView(GetCameraMat());
        Vec2 newPos;
        if(Vec2::distance(pos , target) <  0.5f){
            newPos = target;
        }
        else{
            newPos = Vec2::mix(pos , target , 5.0f * delta);
        }
        pos = newPos;
        Vec2 spriteHalfSize = Size / 2.0f;
        Vec2 offset = {-(pos.x + spriteHalfSize.x) + 1280.0f / 2.0f,
                    -(pos.y + spriteHalfSize.y) + 720.0f / 2.0f};
                    
        m_matrix = Mat4::translate(offset);
    }

    Mat4 GetCameraMat(){
        return m_matrix;
    }

};
