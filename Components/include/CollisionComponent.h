#pragma once
#include "TransformComponent.h"

enum CollisionType{
	Collider,
	Static,
	Dynamic
};


namespace Krooz2D
{
	struct CollisionComponent
	{
		private:
		CollisionType _Type;
		static bool AABB(TransformComponent& comp1, TransformComponent& comp2);

		public:
		CollisionComponent(CollisionType type);
		CollisionType& Get();
		void ResolveStatic(TransformComponent& comp1, TransformComponent& comp2);
	};
	
}

