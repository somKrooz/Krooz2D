#pragma once

// enum KroozSystem{
//     RENDER,
//     COLLISION,
//     REPLAY
// };

class System
{
	public:
	virtual void Update(float deltatime) = 0;
	virtual ~System() = default;
};
