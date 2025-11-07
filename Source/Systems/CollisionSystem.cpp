#include "Systems/CollisionSystem.h"
#include "Core/StateManager.h"

struct BoundingBox {
    float minX, minY, maxX, maxY;
};

BoundingBox MakeBBox(TransformComponent& t) {
    Vec2 pos = t.GetPosition();
    Vec2 scale = t.GetScaleVec();
    
    return {
        pos.x,           
        pos.y,           
        pos.x + scale.x, 
        pos.y + scale.y 
    };
}


CollisionSystem::CollisionSystem()
{
    World* currentWorld = StateManager::GetCurrentWorld();
    if(currentWorld == nullptr) Error("No World Found.. Collision System");

    TiledComponent tile("Assets/Tiled.json");
	dat = tile.GetData();

	for(auto& [id , Comp] : currentWorld->all<CollisionComponent>())
	{
		for(auto& el : Comp.GetCollisionType())
		{
			if(el == CollisionType::STATIC)
			{
				Dynamic.push_back({id , &Comp});
			}
		}
	}
}

void CollisionSystem::Update(float dt)
{
	World* current = StateManager::GetCurrentWorld();
	
	if(StateManager::GetMode() == WorldMode::TOPDOWN)
	{
		for(auto& [id , comp] : Dynamic)
		{
			TransformComponent& trs = current->get<TransformComponent>(id);
			for(auto& el : dat)
			{
				TransformComponent src(el.Pos , el.Scale);
				ResolveTopDown(trs ,  src);
				
			}
		}
	}
	if(StateManager::GetMode() == WorldMode::PLATFORMER)
	{
		for(auto& [id , comp] : Dynamic)
		{
			TransformComponent& trs = current->get<TransformComponent>(id);
			RigidBodyComponent& rb = current->get<RigidBodyComponent>(id);
			rb._onGround = false;

			const float gravity = 900.0f;   
			rb._vel.y += gravity * dt;

			Vec2 pos = trs.GetPosition();
			pos.y += rb._vel.y * dt;
			trs.SetPosition(pos);

			for(auto& el : dat)
			{
				TransformComponent src(el.Pos , el.Scale);
				ResolvePlatformer(trs , src , rb);
			}
		}
	}

}

bool CollisionSystem::AABB_Collision(TransformComponent& A, TransformComponent& B)
{
    BoundingBox a = MakeBBox(A);
    BoundingBox b = MakeBBox(B);

    return !(a.maxX <= b.minX || 
             a.minX >= b.maxX || 
             a.maxY <= b.minY || 
             a.minY >= b.maxY);
}

void CollisionSystem::ResolveTopDown(TransformComponent& Dynamic, TransformComponent& Collider)
{
    if(!AABB_Collision(Dynamic, Collider)) return;
	
	BoundingBox dyn = MakeBBox(Dynamic);
	BoundingBox col = MakeBBox(Collider);

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


void CollisionSystem::ResolvePlatformer(TransformComponent& Dynamic, TransformComponent& Collider, RigidBodyComponent& Rigid)
{
    if(!AABB_Collision(Dynamic, Collider)) return; 

	BoundingBox dyn = MakeBBox(Dynamic);
	BoundingBox col = MakeBBox(Collider);

	float overlapLeft = dyn.maxX - col.minX;
	float overlapRight = col.maxX - dyn.minX;
	float overlapBottom = dyn.maxY - col.minY;
	float overlapTop = col.maxY - dyn.minY;

	float minX = std::min(overlapLeft , overlapRight);
	float minY = std::min(overlapBottom , overlapTop);

	Vec2 NextPosition = Dynamic.GetPosition();
	Vec2 Velocity = Rigid._vel; 

	if(minX < minY)
	{
		if(overlapLeft < overlapRight)
		{
			NextPosition.x -= overlapLeft;
			Velocity.x = 0.0f;
		}
		else
		{
			NextPosition.x += overlapRight;
			Velocity.x = 0.0f;
		}
	}
	else
	{
		if(overlapBottom < overlapTop)
		{
			NextPosition.y -= overlapBottom;
			if(Velocity.y > 0.0f){
				Velocity.y = 0.0f;
				Rigid._onGround = true;
			}
		}
		else
		{
			NextPosition.y += overlapTop;
			if(Velocity.y < 0.0f){
				Velocity.y = 0.0f;
			}
		}
	}

	Dynamic.SetPosition(NextPosition);
	Rigid._vel = Velocity;

}
