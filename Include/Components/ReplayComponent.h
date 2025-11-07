#pragma once

#include "utility/Maths.h"
#include "utility/Types.h"

struct ReplayContainer
{
	Vec2 position;
};

struct ReplayComponent{
	Array<ReplayContainer> ReplayData;
	bool isRecording = false;
	int playindex = 0;
	bool isPlaying = false;
	float timeStep = 0.0f;

	ReplayComponent();
	void StartRecording();
	void EndRecording();
	void StartPlaying();
	void StopPlaying();
	int GetSize();
};
