#include "Components/TransformComponent.h"

Vec2 TransformComponent::GetPosition(){
	return Position;
}
float TransformComponent::GetScale(){
	return Scale.x;
}

Vec2& TransformComponent::GetScaleVec(){
	return Scale;
}


void TransformComponent::SetScale(float sc){
	Scale = Vec2(sc,sc);
}

void TransformComponent::SetScaleVec(Vec2 sc){
	Scale = Vec2(sc.x,sc.y);
}

void TransformComponent::SetPosition(Vec2 newPos){
	Position = newPos;
}

void TransformComponent::AddOffset(Vec2 offset){
	auto current = GetPosition();
	current.x += offset.x;
	current.y += offset.y;
	SetPosition(current);
}
