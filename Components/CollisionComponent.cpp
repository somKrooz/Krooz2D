#include "CollisionComponent.h"

struct BoudingBox
{
	float _left = 0.0f;
	float _right = 0.0f;
	float _top = 0.0f;
	float _bottom = 0.0f;
};

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
		if(!AABB(comp1 , comp2)) return;

		Vec2 pos_1 = comp1.GetPosition();
		Vec2 size_1 = comp1.GetScale();

		Vec2 pos_2 = comp2.GetPosition();
		Vec2 size_2 = comp2.GetScale();

		BoudingBox Comp1;
		Comp1._left = pos_1.x;
		Comp1._right = pos_1.x + size_1.x;
		Comp1._top = pos_1.y + size_1.y;
		Comp1._bottom = pos_1.y;


		BoudingBox Comp2;
		Comp2._left = pos_2.x;
		Comp2._right = pos_2.x + size_2.x;
		Comp2._top = pos_2.y + size_2.y;
		Comp2._bottom = pos_2.y;

		float OverLapX = std::min(Comp1._right, Comp2._right) - std::max(Comp1._left, Comp2._left);
		float OverLapY = std::min(Comp1._top, Comp2._top) - std::max(Comp1._bottom, Comp2._bottom);


		if (OverLapX < OverLapY){
			if(pos_1.x < pos_2.x){
				pos_1.x -= OverLapX;
			}
			else{
				pos_1.x += OverLapX;
			}  
		}else{
			if (pos_1.y < pos_2.y)
            pos_1.y -= OverLapY; 
        else
            pos_1.y += OverLapY; 
		}
		comp1.SetPosition(pos_1);
	}

} 


