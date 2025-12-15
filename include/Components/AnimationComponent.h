#pragma once
#include "Utility/Types.h"

struct AnimSpec {
	int countX; 
	int countY;
	int column;
	int end; 
};


struct AnimationComponent
{
	private:
	scope<AnimSpec> Anim;
	int CurrentAnimationIndex = 0;
	float frametime = 0.0f;
	int index = 0;
	int frameNum = 0;
	
	public:
	AnimationComponent(AnimSpec anim){
		Anim = createScope<AnimSpec>(anim);
	}

	void SwapAnim(AnimSpec newAnim)
	{
		Anim.reset();
		Anim = createScope<AnimSpec>(newAnim);
	}

	AnimSpec* Get(){
		return Anim.get();
	}

	void Update(float dt) {
		if(!Anim ||Anim->end <= 0) return;
		frametime += dt;
		float frameDuration = 1.0f / 10.0f;

		while (frametime >= frameDuration) {
			frametime -= frameDuration;
			index += 1;
			frameNum = index % Anim->end;
		}
	}

	int GetFrameNumber()
	{
		return frameNum;
	}

};
