#include "Timer.h"

namespace Krooz2D
{
	void WorldTimer::Update(float deltatime)
	{
		 for (auto it = _tasks.begin(); it != _tasks.end();)
		 {
				it->_time -= deltatime;
				if (it->_time <= 0.0f)
				{
					if (it->_callback) it->_callback();
					it = _tasks.erase(it);
		 		}
			else ++it;
		}
	}

	void WorldTimer::SetTimeout(float seconds, std::function<void()> func)
	{
		_tasks.push_back({seconds , func});
	}
}
