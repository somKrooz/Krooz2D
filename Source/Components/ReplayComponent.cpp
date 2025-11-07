#include "Components/ReplayComponent.h"

ReplayComponent::ReplayComponent(){
	playindex = 0;
	timeStep = 0.0f;
}

void ReplayComponent::StartRecording(){
	if(isPlaying) return;
	if(!ReplayData.empty()){
		ReplayData.clear();
	}
	playindex = 0;
	timeStep = 0.0f;
	isRecording = true;
}
void ReplayComponent::EndRecording(){
	if(isPlaying) return;
	if(isRecording) isRecording = false;
}

void ReplayComponent::StartPlaying(){
	isPlaying = true;
	playindex = 0;
}

void ReplayComponent::StopPlaying(){
	if(isPlaying) isPlaying = false;
	playindex = 0;
}

int ReplayComponent::GetSize(){
	return ReplayData.size();
}
