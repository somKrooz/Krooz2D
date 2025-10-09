#pragma once
#include "Types.h"
#include "World.h"

struct EngineState
{
	TextureDescription Stage;
	TextureDescription Recording;
	TextureDescription Playing;
	EngineState() = default;
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
		inline static uint32 id = 0;
		inline static bool _DebugMode = false; 	

		inline static World* _world = nullptr;

		public:
		Debug();
		static void DebugMode(bool state);
		static void InitWorld(World& world);
		static void ChangeMode(EngineStateType mode);
		static bool GetDebugMode(){return _DebugMode;}
		void DrawState();
	};
} 
