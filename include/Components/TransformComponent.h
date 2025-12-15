#pragma once

#include "Utility/Types.h"
#include "Utility/Maths.h"

struct TransformComponent
{
private:
	Vec2 Position = Vec2::Zero();
	Vec2 Scale = Vec2::Zero();

public:
	TransformComponent(Vec2 Pos, Vec2 Sc) : Position(Pos), Scale(Sc) {}
	TransformComponent(Vec2 Pos, float Sc) : Position(Pos), Scale(Vec2(Sc, Sc)) {}

	Vec2 GetPosition() {
		return Position;
	}
	float GetScale() {
		return Scale.x;
	}
	Vec2& GetScaleVec() {
		return Scale;
	}

	void AddOffset(Vec2 offset) {
		auto current = GetPosition();
		current.x += offset.x;
		current.y += offset.y;
		SetPosition(current);
	}
	void SetScale(float sc) {
		Scale = Vec2(sc, sc);
	}
	void SetScaleVec(Vec2 sc) {
		Scale = Vec2(sc.x, sc.y);
	}
	void SetPosition(Vec2 newPos) {
		Position = newPos;
	}
};
