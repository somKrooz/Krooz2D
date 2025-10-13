#include "CollisionSystem.h"
#include "CollisionComponent.h"
#include "TagComponent.h"

namespace Krooz2D
{
	CollisionSystem::CollisionSystem(World& world){
		_currentWorld = &world;
		auto Collisions = _currentWorld->GetAllComponentsOfTypeID<CollisionComponent>();

		for(auto id : Collisions){
			auto collisionComp = _currentWorld->GetComponent<CollisionComponent>(id);
			if(collisionComp->Get() == CollisionType::Collider){
				auto trs = _currentWorld->GetComponent<TransformComponent>(id);
				_Colliders.push_back(trs);
			}
		}
	}

	void CollisionSystem::Update(float dt)
	{
		auto Collisions = _currentWorld->GetAllComponentsOfTypeID<CollisionComponent>();

		for(auto id : Collisions){
			auto collisionComp = _currentWorld->GetComponent<CollisionComponent>(id);
				if(_currentWorld->HasComponentId<TagComponent>(id)){
						if(_currentWorld->GetComponent<TagComponent>(id)->GetTag() == "Player"){
							auto SourceTranformComp = _currentWorld->GetComponent<TransformComponent>(id);
							for(auto& cols : _Colliders){
								collisionComp->ResolveStatic(*SourceTranformComp ,*cols);
							}
					}	
				
				
			}
		}
	}
} 
