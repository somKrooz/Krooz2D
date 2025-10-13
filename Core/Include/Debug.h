#pragma once
#include "Types.h"
#include "World.h"

struct EngineState
{
	Ref<TextureDescription> Stage = nullptr;
	Ref<TextureDescription> Recording = nullptr;
	Ref<TextureDescription> Playing = nullptr;
};

enum EngineStateType {
    STAGE,
    RECORD,
    PLAY
};

namespace Krooz2D
{
	class Debug
	{
		private:
		inline static Ref<EngineState> State = nullptr;
		inline static int CurrentState = 0;
		inline static uint32 id = 0;
		inline static bool _DebugMode = false; 	
		inline static float opacity = 1.0f;
		inline static World* _world = nullptr;

		public:
		Debug();
		~Debug(){_world = nullptr;}
		static void DebugMode(bool state);
		static void InitWorld(World& world);

		static int GetStateChange(){return CurrentState;}
		static void ChangeMode(EngineStateType mode);
		static bool GetDebugMode(){return _DebugMode;}
		static void setOpacity(float op){opacity = op;}
		static float& getopacity(){return opacity;}
		
		void DrawState();
	};
} 
