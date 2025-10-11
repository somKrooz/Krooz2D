#pragma once 

#include "unordered_map"
#include "GLFW/glfw3.h"
#include "Engine.h"


namespace Krooz2D
{
	class Input
	{
		private:
		inline static bool isLocked = false;
		inline static bool keyStates[1024] = { false };
		
		public:
		static void GetCursorLocation(Vec2& loc);
		static bool isHold(int KeyState);
		static bool isReleased(int KeyState);
		static bool isJustPressed(int KeyState);
		
		static void SetLock(bool state){isLocked = state;}
	};
} 
