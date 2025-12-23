#pragma once

#define IsPressed(key) Input::IsKeyPressed(key)
#define IsRelased(key) Input::IsKeyPressed(key)
#define isJust(key) Input::IsJustPressed(key)

union RGFW_event;
class Input
{
	private:
	static inline bool CurrenKey[512] = {false};
	static inline bool LastKey[512] = {false};
	static inline float scrollFactor = 0.0f;

	public:
		static void InitInput(float val);
		static bool IsKeyPressed(int Key);
		static bool IsKeyReleased(int Key);
		static bool IsJustPressed(int Key);
		static float &GetScrollData();
		static void Update(RGFW_event &event);
};
