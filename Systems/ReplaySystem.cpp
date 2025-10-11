#include "ReplaySystem.h"
#include "ReplayComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "Input.h"

#include "stdio.h"

namespace Krooz2D
{
	void ReplaySystem::Update(World& world, float dt)
	{
		
		auto entities = world.GetAllComponentsOfTypeID<ReplayComponent>();

		for (auto& ent : entities)
		{
				auto replay = world.GetComponent<ReplayComponent>(ent);
				if (!replay->is_playing()) continue;

				replay->_playbackTimer += dt;
				auto& data = replay->Get();
				int idx = replay->get_index();


				if (replay->_playbackTimer >= data[idx].timestamp)
				{
						auto trs = world.GetComponent<TransformComponent>(ent);
						trs->SetPosition(data[idx].Position);

						auto tex = world.GetComponent<TextureComponent>(ent);
						tex->ReplaceTexture(*data[idx].desc);

						replay->advance_index();
						if(replay->get_index() >= data.size()-1)
						{
							replay->reset();
						}
				}
		}
	}


	void ReplaySystem::RecordFrames(World& world, float dt)
	{
		auto entities = world.GetAllComponentsOfTypeID<ReplayComponent>();
		for (auto& ent : entities)
		{
			auto replay = world.GetComponent<ReplayComponent>(ent);
			auto trs = world.GetComponent<TransformComponent>(ent);
			auto tex = world.GetComponent<TextureComponent>(ent);

			SnapShots snap = {trs->GetPosition() , CreateRef<TextureDescription>(tex->Get().Get())};
			replay->update(snap , dt);
		}
		
	}

	void ReplaySystem::StartReplay(World& world)
	{
		Input::SetLock(true);
		auto entities = world.GetAllComponentsOfTypeID<ReplayComponent>();
		for (auto& ent : entities)
		{
			auto replay = world.GetComponent<ReplayComponent>(ent);
			replay->start_playing();
		}
	}

	void ReplaySystem::StartRecording(World& world)
	{
		auto entities = world.GetAllComponentsOfTypeID<ReplayComponent>();
		for (auto& ent : entities)
		{
			auto replay = world.GetComponent<ReplayComponent>(ent);
			replay->start_recordind();
		}
	}

	void ReplaySystem::EndRecording(World& world)
	{
		printf("tiggered\n");
		Input::SetLock(false);
		auto entities = world.GetAllComponentsOfTypeID<ReplayComponent>();
		for (auto& ent : entities)
		{
			auto replay = world.GetComponent<ReplayComponent>(ent);
			replay->end_recording();

			auto vec = replay->Get();
			auto data = replay->Get().data();
			
			auto trs = world.GetComponent<TransformComponent>(ent);
			trs->SetPosition(data[vec.size()-1].Position);
		}
	}
}
