#pragma once

#include "World.h"

namespace Krooz2D
{
	class ReplaySystem
	{
		public:
		void Update(World& world , float dt);		
		void RecordFrames(World& world,float dt);
		void StartReplay(World& world);
		
		void StartRecording(World& world);
		void EndRecording(World& world);
	};
	
}
