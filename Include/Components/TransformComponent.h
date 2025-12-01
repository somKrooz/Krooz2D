#pragma once

#include "Core/utility/Types.h"
#include "Core/utility/Maths.h"

struct TransformComponent
{
	private:
	Vec2 Position = Vec2::Zero();
	Vec2 Scale = Vec2::Zero();

	public:
	TransformComponent(Vec2 Pos , Vec2 Sc) : Position(Pos) , Scale(Sc) {}
	TransformComponent(Vec2 Pos , float Sc) : Position(Pos) , Scale(Vec2(Sc,Sc)) {}

	Vec2 GetPosition();
	float GetScale();
	Vec2& GetScaleVec();

	void AddOffset(Vec2 offset);
	void SetScale(float sc);
	void SetScaleVec(Vec2 sc);
	void SetPosition(Vec2 newPos);
};
