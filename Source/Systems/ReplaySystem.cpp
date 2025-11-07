#include "Systems/ReplaySystem.h"
#include "Core/World.h"
#include "Core/StateManager.h"
#include "Components/TransformComponent.h"

float FPS = 1.0f/60.0f; 

void ReplaySystem::StartRecording(){
	World* currentWorld = StateManager::GetCurrentWorld();
	if(currentWorld == nullptr) return;

	for(auto&[id , replay] : currentWorld->all<ReplayComponent>()){
		replay.StartRecording();
	}
}

void ReplaySystem::StopRecording(){
	World* currentWorld = StateManager::GetCurrentWorld();
	if(currentWorld == nullptr) return;

	for(auto&[id , replay] : currentWorld->all<ReplayComponent>()){
		replay.EndRecording();
	}
}

void ReplaySystem::Play(){
	World* currentWorld = StateManager::GetCurrentWorld();
	if(currentWorld == nullptr) return;

	for(auto&[id , replay] : currentWorld->all<ReplayComponent>()){
		replay.StartPlaying();
	}
}

void ReplaySystem::Stop(){
	World* currentWorld = StateManager::GetCurrentWorld();
	if(currentWorld == nullptr) return;

	for(auto&[id , replay] : currentWorld->all<ReplayComponent>()){
		replay.StopPlaying();
	}
}

void ReplaySystem::Update(float dt) {
	World* currentWorld = StateManager::GetCurrentWorld();
	if (!currentWorld) return;

	for (auto& [id, replay] : currentWorld->all<ReplayComponent>()) {
		auto& transform = currentWorld->get<TransformComponent>(id);
		
		replay.timeStep += dt; 

		if (replay.isRecording) {
			if (replay.timeStep >= FPS) {
				replay.ReplayData.push_back({
					transform.GetPosition(),
				});
				replay.timeStep = 0.0f;
			}
		}

		if (replay.isPlaying && !replay.ReplayData.empty()) {
			auto& frame = replay.ReplayData[replay.playindex];
			
			transform.SetPosition(frame.position);
			if(replay.timeStep >= FPS){
				if (replay.playindex + 1 < replay.ReplayData.size()) {
					replay.playindex++;
				} else {
					replay.playindex = 0;   
				}
				replay.timeStep = 0.0f;
			}
		}
	}
}

