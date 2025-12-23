#include "External/OpenglBind.h"
#include "Pipeline/Loader.h"
#include "EngineCore/Buffer.h"
#include "EngineCore/Shader.h"
// #define RGFW_IMPLEMENTATION
// #define RGFW_OPENGL
// #include <External/WindowBind.h>
#include <EngineCore/Window.h>
#include <Utility/Embed.h>
#include <EngineCore/Scene.h>
#include <Pipeline/Camera.h>
#include "EngineCore/TextureManager.h"
#include "EngineCore/Input.h"

#include "Components/TransformComponent.h"
#include "Components/TextureComponent.h"
#include "Components/AnimationComponent.h"
#include "Components/CollisionComponent.h"

#include <Pipeline/Renderer.h>
#include <Pipeline/Collision.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cmath>

float GetDelta()
{
	static auto last = std::chrono::high_resolution_clock::now();
	auto now = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<float> delta = now-last; 
	last = now;

	float deltatime = delta.count();
	return deltatime;
}

void ChangeBulkTexture(Scene& sc , vec<u32>& vec , u32 tex)
{
	for(auto& i : vec)
	{
		auto handle = TextureManager::Get(tex);
		sc.get<TextureComponent>(i).ReplaceData(handle);
	}
} 


int main(void) 
{
	auto window = KroozWindow::createWindow(1280, 720, "Krooz");
	KroozWindow::defineWindowAttr(WindowAttributes::ClearBorder | WindowAttributes::Centered);

	#ifdef LEGACY
    	Shader shader(LegacyDefault::vertexshader, LegacyDefault::fragmentshader);
	#else
    	Shader shader(Default::vertexshader, Default::fragmentshader);
	#endif

	Scene scene;

	ent ttx = scene.create();
	AsyncTexture::Enqueue_texture("Assets/boxy.png" , ttx);

	ent rc = scene.create();
	AsyncTexture::Enqueue_texture("Assets/boxy_open.png" , rc);

	ent bochi = scene.create();
	AsyncTexture::Enqueue_texture("Assets/bochi.jpg" , bochi);

	ent def = scene.create();
	AsyncTexture::Enqueue_texture("Assets/Tex_0.png" , def);

	vec<ent> randtex = {ttx, rc, bochi, def};
	std::srand((unsigned)std::time(nullptr));

	vec<ent> ids;
	constexpr int COUNT = 50000;
	constexpr int COLS  = 500;
	constexpr int ROWS  =(COUNT + COLS - 1) / COLS; 

	constexpr float TILE_SIZE = 10.0f; 
	constexpr float SPACING = 2.0f;    

	for (int i = 0; i < COUNT; i++)
	{
		int x = i % COLS;
		int y = i / COLS;

		Vec2 pos;
		pos.x = x * (TILE_SIZE + SPACING);
		pos.y = y * (TILE_SIZE + SPACING);

		ent id = scene.create();
		scene.add<TransformComponent>(id, pos, Vec2(TILE_SIZE, TILE_SIZE));
		scene.add<TextureComponent>(id);

		ids.push_back(id);
	}	
	
	
	bool isMoving = false;
	bool randomized = false;

	scene.add<CollisionComponent>(ids[0] , CollisonType::COLLIDABLE);

	for(auto& i : ids )
	{
		if(i == ids[0])
			continue;
		if(i<= 5000){
			scene.add<CollisionComponent>(i , CollisonType::DYNAMIC);
		}
		else{
			scene.add<CollisionComponent>(i , CollisonType::COLLISION);
		}
	}
	
	Renderer render(scene);
	Collision col(scene);

	Camera cam;
	Camera::setZoom(0.5f);
	Input::InitInput(Camera::GetZoom());

	cam.setTarget(scene.get<TransformComponent>(ids[0]));

	while (!KroozWindow::isWindowValid()) 
	{
		KroozWindow::PoolEvent();
		
		float dt = GetDelta();
		cam.Update(dt);

		cam.setZoomLerp(Input::GetScrollData() , dt);

		isMoving = false;
		if(Input::IsKeyPressed((u32)('w'))){
			randomized = false;
			isMoving = true;
			scene.get<TransformComponent>(ids[0]).AddOffset({0 , -100*dt});
			ChangeBulkTexture(scene, ids, rc);
		}
		if(Input::IsKeyPressed((u32)('s'))){
			randomized = false;
			isMoving = true;
			scene.get<TransformComponent>(ids[0]).AddOffset({0 , 100*dt});
			ChangeBulkTexture(scene, ids, rc);
		}
		if(Input::IsKeyPressed((u32)('a'))){
			randomized = false;
			isMoving = true;
			scene.get<TransformComponent>(ids[0]).AddOffset({-100*dt , 0});
			ChangeBulkTexture(scene, ids, rc);
		}
		if(Input::IsKeyPressed((u32)('d'))){
			randomized = false;
			isMoving = true;
			scene.get<TransformComponent>(ids[0]).AddOffset({100*dt , 0});
			ChangeBulkTexture(scene, ids, rc);
		}
		if(Collision::GetCollisionEvent()){
			// cam.setZoomLerp(2.0f, dt);
			Camera::ShakeCam();
		}
		if(!isMoving && !randomized)
		{
			randomized = true;
			for(auto&i : ids)
			{
				int index = std::rand() % randtex.size();
				auto entity = randtex[index];
				auto handle = TextureManager::Get(entity);
				scene.get<TextureComponent>(i).ReplaceData(handle);
			}
		}

		render.Update(&shader, dt);
		col.Update(dt);
		KroozWindow::swapBuffers();
	}
	KroozWindow::destroyWindow();
    return 0;
}