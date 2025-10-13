#include "CollisionComponent.h"


namespace Krooz2D
{
	CollisionComponent::CollisionComponent(CollisionType type){
		_Type = type;
	}	
	CollisionType& CollisionComponent::Get(){
		return _Type;
	}

	bool CollisionComponent::AABB(TransformComponent& comp1, TransformComponent& comp2){
		Vec2 SourcePos = comp1.GetPosition();
		Vec2 TargetPos = comp2.GetPosition();
		
		Vec2 SourceSize = comp1.GetScale();
		Vec2 TargetSize = comp2.GetScale();
		

		bool noOverlapX = SourcePos.x + SourceSize.x < TargetPos.x || TargetPos.x + TargetSize.x < SourcePos.x;
    bool noOverlapY = SourcePos.y + SourceSize.y < TargetPos.y || TargetPos.y + TargetSize.y < SourcePos.y;
	
		return !(noOverlapX || noOverlapY);
	
	}

	void CollisionComponent::ResolveStatic(TransformComponent& comp1, TransformComponent& comp2)
	{
		if(AABB(comp1 , comp2)){
			printf("Overlapping Bodies Yaaaaaaa....\n");
		}
	}

} 


