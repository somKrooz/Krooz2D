#pragma once
#include "Core/World.h"

enum WorldMode {
	TOPDOWN,
	PLATFORMER
};

class StateManager
{
	private:
	static inline WorldMode MODE = WorldMode::TOPDOWN;
	static inline World* GlobalWorld = nullptr;
	static inline Array<Scope<System>> SystemBuilder;

	public:
	static void setCurrentWorldContext(World& world , WorldMode mode){
		GlobalWorld = &world;
		MODE = mode;
	}

	static World* GetCurrentWorld(){
		return GlobalWorld;
	} 

	template<typename... T>		
	static void CreateSystemList(){
		(SystemBuilder.push_back(createScope<T>()), ...);
	} 

	static void UpdateAllSystems(float delta){
		for (auto& sys : SystemBuilder)
        	sys->Update(delta);
	}
	static WorldMode& GetMode(){
		return MODE;
	}
};
