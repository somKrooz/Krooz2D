#pragma once
#include "Core/Window.h"
#include "utility/Keys.h"

#define IsPressed(key) Input::IsKeyPressed(key)
#define IsRelased(key) Input::IsKeyPressed(key)
#define isJust(key) Input::IsJustPressed(key)

class Input
{
	private:
	static inline bool CurrenKey[512] = {false};
	static inline bool LastKey[512] = {false};
	static inline float scrollvalue = 1.0f;
	
	public:
	static void Update();
	static bool IsKeyPressed(int Key);
	static bool IsKeyReleased(int Key);
	static bool IsJustPressed(int Key);
	static void SetInitialScroll(float value);
	static float ScrollFactor();
	
};

