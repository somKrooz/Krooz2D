#pragma once
#include "Maths.h"
#include "TransformComponent.h"

namespace Krooz2D
{
	struct Camera
	{
		inline static Mat4 _View = Mat4::identity();
		inline static Mat4 _Projection = Mat4::identity();
		inline static float zoom = 1.0f;

		Vec2 Position = Vec2::Zero();
		
void Follow(TransformComponent& trs, float dt){
    float lerpFactor = 6.0f * dt;
    Position = Vec2::mix(Position, trs.GetPosition(), lerpFactor);

    Vec2 spriteHalfSize = trs.GetScale() / 2.0f;
    Vec2 center = Position + spriteHalfSize;

    Vec2 screenCenter = Vec2(1280.0f / 2.0f, 720.0f / 2.0f);
    _View = Mat4::translate(Vec2(screenCenter.x - center.x, screenCenter.y - center.y));

    float halfWidth = (1280.0f / 2.0f) / zoom;
    float halfHeight = (720.0f / 2.0f) / zoom;
		_Projection = Mat4::ortho(screenCenter.x - halfWidth, screenCenter.x + halfWidth,
                          screenCenter.y + halfHeight, screenCenter.y - halfHeight,
                          -1.0f, 1.0f);
	}

	static void setZoom(float val, float dt)
	{
			float t = 20.0f * dt;
			if(t > 1.0f) t = 1.0f; 
			float currentZoom = zoom * (1.0f - t) + val * t;
			zoom = currentZoom;
			
	}



	static Mat4& GetMat(){return _View;} 
	static Mat4& GetProjection(){return _Projection;} 
	};
		
}
