#pragma once

#include "Components/TransformComponent.h"
#include "Components/CollisionComponent.h"
#include "Components/RigidBodyComponent.h"
#include "Components/TiledComponent.h"
#include "Systems/System.h"

class CollisionSystem : public System
{
	private:
	void ResolveTopDown(TransformComponent& Target , TransformComponent& Cols);
	void ResolvePlatformer(TransformComponent& Target , TransformComponent& Cols , RigidBodyComponent& Rb);
	
	Array<std::pair<size_t, CollisionComponent*>> Dynamic;
	// Array<std::pair<size_t, CollisionComponent*>> Colliders;
	
	Array<ColData> dat;
	
	public:
	static bool AABB_Collision(TransformComponent& Target , TransformComponent& Cols);
	CollisionSystem();
	void Update(float dt) override;
};
