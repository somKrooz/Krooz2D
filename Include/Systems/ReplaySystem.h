#pragma once
#include "utility/Types.h"
#include "utility/Maths.h"
#include "Components/ReplayComponent.h"
#include "Systems/System.h"


class ReplaySystem: public System
{
	private:
	float _timeStep = 0.0f;
	public:

	void Update(float dt) override;
	static void StartRecording();
	static void StopRecording();
	static void Play();
	static void Stop();
};
