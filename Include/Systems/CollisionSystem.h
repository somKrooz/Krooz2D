#pragma once

#include "Components/TransformComponent.h"
#include "Components/CollisionComponent.h"
#include "Components/RigidBodyComponent.h"
#include "Components/TiledComponent.h"
#include "Systems/System.h"

class CollisionSystem : public System
{
	private:
	bool AABB_Collision(TransformComponent& Target , TransformComponent& Cols);
	void ResolveTopDown(TransformComponent& Target , TransformComponent& Cols);
	void ResolvePlatformer(TransformComponent& Target , TransformComponent& Cols , RigidBodyComponent& Rb);
	
	Array<std::pair<size_t, CollisionComponent*>> Dynamic;
	// Array<std::pair<size_t, CollisionComponent*>> colliders;

	Array<ColData> dat;

	public:
	CollisionSystem();
	void Update(float dt) override;
};
