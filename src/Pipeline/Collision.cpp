#include "Components/CollisionComponent.h"
#include "Components/TransformComponent.h"
#include "Pipeline/Collision.h"

BBox MakeBoundingBox(TransformComponent& src)
{
    return BBox{src.GetPosition().x, src.GetPosition().x + src.GetScaleVec().x,
                src.GetPosition().y, src.GetPosition().y + src.GetScaleVec().y};
}

BBox MakeBoundingBox(Vec2 Pos , Vec2 Scale)
{
    return BBox{Pos.x, Pos.x + Scale.x,Pos.y, Pos.y + Scale.y};
}


bool AABB(BBox& a , BBox& b)
{
    return !(a.maxX <= b.minX || 
            a.minX >= b.maxX || 
            a.maxY <= b.minY || 
            a.minY >= b.maxY);
}

Collision::Collision(Scene& scene)
{
    CurrentScene = &scene;
    for(auto& [id , Comp] : CurrentScene->all<CollisionComponent>())
    {
        if(Comp.Get() == CollisonType::COLLISION)
        {
            TransformComponent &trs = CurrentScene->get<TransformComponent>(id);
            Vec2 Pos = trs.GetPosition();
            Vec2 Scale = trs.GetScaleVec();
            CollisionData.push_back(NativeCollision{Pos, Scale});
        }
        if(Comp.Get() == CollisonType::COLLIDABLE)
        {
            TransformComponent &trs = CurrentScene->get<TransformComponent>(id);
            Vec2 Pos = trs.GetPosition();
            Vec2 Scale = trs.GetScaleVec();

            Static.push_back(NativeCollision{Pos, Scale});
        }
    }

    printf("Static Size: %d\n", Static.size());
    printf("Colliders Size: %d\n", CollisionData.size());
}


void ResolveTopDown(BBox& dyn, BBox& col, TransformComponent& Dynamic)
{
	float overlapLeft = dyn.maxX - col.minX;
	float overlapRight = col.maxX - dyn.minX;
	float overlapBottom = dyn.maxY - col.minY;
	float overlapTop = col.maxY - dyn.minY;

	float minX = std::min(overlapLeft , overlapRight);
	float minY = std::min(overlapBottom , overlapTop);

	Vec2 NextPosition = Dynamic.GetPosition();
	if(minX < minY)
	{
		if(overlapLeft < overlapRight) NextPosition.x -= overlapLeft;
		else NextPosition.x += overlapRight; 
	}
	else
	{
		if(overlapBottom < overlapTop) NextPosition.y -= overlapBottom;
		else NextPosition.y += overlapTop;
	}

	Dynamic.SetPosition(NextPosition);

}

void Collision::Update(float dt)
{
    Static.clear();
    TransformComponent *Current = nullptr;
    for (auto &[id, Comp]: CurrentScene->all<CollisionComponent>())
    {
        if(Comp.Get() == CollisonType::COLLIDABLE)
        {
            Current = &CurrentScene->get<TransformComponent>(id);
            Vec2 Pos = Current->GetPosition();
            Vec2 Scale = Current->GetScaleVec();

            Static.push_back(NativeCollision{Pos, Scale});
        }
    }

    for (auto &stat : Static)
    {
        BBox s = MakeBoundingBox(stat._Position, stat._Scale);
        // printf("details: %.1f , %.1f\n", s.maxX , s.maxY);

        for (auto &collision : CollisionData)
        {
            BBox c = MakeBoundingBox(collision._Position, collision._Scale);
            if (AABB(c, s))
            {
                ResolveTopDown(s, c, *Current);
            }
        }
    }
}

