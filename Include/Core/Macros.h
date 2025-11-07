#pragma once

// ECS 
#define WORLD_REF StateManager::GetCurrentWorld()
#define CREATE() WORLD_REF->CreateEntity()

#define ADD(type, ...) \
    WORLD_REF->add<type>(__ecs_current->id, __VA_ARGS__)

#define GET(type) \
    WORLD_REF->get<type>(__ecs_current->id)

#define WITH(entity) \
    for (Ent* __ecs_current = &(entity); __ecs_current; __ecs_current = nullptr)

// ECS


// Engine Internals

float __GlobalDeltaTime = 0.0f;

#define DeltaContext(var) \
	float var = getDeltaTime(); \
	__GlobalDeltaTime = var; 

#define LoadTexture(name , path) \
	auto name = Texture::load(path)

#define SetWorldContext(world , type) \
	StateManager::setCurrentWorldContext(world, type)
	
#define SetActiveSystemList(...) \
	StateManager::CreateSystemList<__VA_ARGS__>();

#define UpdateSystems \
	StateManager::UpdateAllSystems(__GlobalDeltaTime);

#define GlobalDelta (__GlobalDeltaTime)
