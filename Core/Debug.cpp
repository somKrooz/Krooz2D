#include "Debug.h"
#include "QuadComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

namespace Krooz2D
{

	Debug::Debug()
	{

		State = CreateRef<EngineState>();

		auto recording = Texture::LoadTexture("ReplayMode.png");
		auto stage = Texture::LoadTexture("StageMode.png");
		auto playing = Texture::LoadTexture("Playing.png");
		
		State->Stage = *stage;
		State->Playing = *playing;
		State->Recording = *recording;
		
	}
	void Debug::DebugMode(bool state)
	{
		_DebugMode = state;
	}

	void Debug::DrawState()
	{
		Ent debbuger = _world->CreateEntity();
		id = debbuger.id;
		_world->AddComponent<QuadComponent>(debbuger.id);
		_world->AddComponent<TransformComponent>(debbuger.id , Vec2(20,20) , Vec2(200,50));
		_world->AddComponent<TextureComponent>(debbuger.id, State->Stage);
		_world->AddComponent<TagComponent>(debbuger.id , "Debug");
	}

	void Debug::ChangeMode(EngineStateType mode)
	{
		auto state = _world->GetComponent<TextureComponent>(id);
		CurrentState += 1;

		if(CurrentState > 10)
		{
			CurrentState = 0;
		}
		
		switch (mode)
		{
		case EngineStateType::STAGE:
			state->ReplaceTexture(State->Stage);
			break;
		case EngineStateType::RECORD:
			state->ReplaceTexture(State->Recording);
			break;
		case EngineStateType::PLAY:
			state->ReplaceTexture(State->Playing);
			break;
		
		default:
			state->ReplaceTexture(State->Stage);
			break;
		}
	}

	void Debug::InitWorld(World& world){
		_world = &world;
	}
} 

