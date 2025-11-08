#pragma once 

#include "utility/Types.h"

enum CollisionType{
	DYNAMIC,
	COLLIDER
};


struct CollisionComponent
{
	private:
	Array<CollisionType> _collisions;
	
	public:
	CollisionComponent(CollisionType type){
		_collisions.push_back(type); 
	}

	Array<CollisionType>& GetCollisionType(){
		return _collisions;
	}
};
