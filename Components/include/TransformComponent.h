#pragma once
#include "Types.h"


namespace Krooz2D{

	struct TrsDef{
		Vec2 Pos = Vec2::Zero();
		float rot = 0.0f;
		Vec2 Scale = Vec2::Zero();
	};

	struct TransformComponent{
		TrsDef _trs;

		TransformComponent() : _trs{} {}
		TransformComponent(Vec2 Position , Vec2 Scale) ;
		TransformComponent(Vec2 Position , float Scale);
		
		Vec2& GetPosition();
		Vec2& GetScale();
		float GetRot();
		TrsDef& GetTransform();

		void SetPosition(const Vec2& position);
		void SetScale(const Vec2& position);
		void SetRotation(const float rot);

		Mat4 Get();
	};
	
}
