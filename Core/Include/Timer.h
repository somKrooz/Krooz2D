#pragma once
#include <functional>

namespace Krooz2D
{
	struct TimeTask
	{
		float _time = 0;
		std::function<void()> _callback;

	};

	class WorldTimer
	{
		private:
		inline static std::vector<TimeTask> _tasks;

		public:
		static void Update(float deltatime);
		static void SetTimeout(float seconds, std::function<void()> func);

	};

	inline void SetTimeout(float seconds, std::function<void()> func)
	{
		WorldTimer::SetTimeout(seconds, func);
	}
}
