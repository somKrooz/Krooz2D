#include "Components/CollisionComponent.h"
#include "Components/TransformComponent.h"
#include "Pipeline/Collision.h"
#include "Pipeline/helper.h"

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
            CollisionData.push_back(NativeCollision{id , Pos, Scale});
        }
        if(Comp.Get() == CollisonType::COLLIDABLE)
        {
            TransformComponent &trs = CurrentScene->get<TransformComponent>(id);
            Vec2 Pos = trs.GetPosition();
            Vec2 Scale = trs.GetScaleVec();

            Static.push_back(NativeCollision{id , Pos, Scale});
        }

        if(Comp.Get() == CollisonType::DYNAMIC)
        {
            TransformComponent &trs = CurrentScene->get<TransformComponent>(id);
            Vec2 Pos = trs.GetPosition();
            Vec2 Scale = trs.GetScaleVec();
            Dynamic.push_back(NativeCollision{id , Pos, Scale});
        }
    }

    printf("Static Size: %d\n", Static.size());
    printf("Collider Size: %d\n", CollisionData.size());
    printf("Dynamic Size: %d\n", Dynamic.size());
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
    if(!Static.empty()) Static.clear();
    hasCollided = false;
    for (auto &[id, Comp]: CurrentScene->all<CollisionComponent>())
    {
        if(Comp.Get() == CollisonType::COLLIDABLE)
        {
            auto trs = CurrentScene->get<TransformComponent>(id);
            Vec2 Pos = trs.GetPosition();
            Vec2 Scale = trs.GetScaleVec();

            Static.push_back(NativeCollision{id,Pos, Scale});
        }
    }

    for (auto &stat : Static)
    {
        BBox s = Helper::MakeBoundingBox(stat._Position, stat._Scale);
        auto Current = &CurrentScene->get<TransformComponent>(stat._id);
        for (auto &collision : CollisionData)
        {
            BBox c = Helper::MakeBoundingBox(collision._Position, collision._Scale);
            if (Helper::AABB(c, s))
            {
                hasCollided = true;
                ResolveTopDown(s, c, *Current);
            }
        }
    }

    for (auto &collision : Dynamic)
    {
        auto& dynTrs = CurrentScene->get<TransformComponent>(collision._id);
        BBox dynBox = Helper::MakeBoundingBox(dynTrs);

        for (auto &stat : Static)
        {
            BBox statBox = Helper::MakeBoundingBox(stat._Position, stat._Scale);

            if (Helper::AABB(dynBox, statBox))
            {
                hasCollided = true;
                ResolveTopDown(dynBox, statBox, dynTrs);
            }
        }
    }

}

bool Collision::GetCollisionEvent()
{
    return hasCollided;
}

