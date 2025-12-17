#include "External/OpenglBind.h"
#include "Pipeline/Loader.h"
#include "EngineCore/Buffer.h"
#include "EngineCore/Shader.h"
#define RGFW_IMPLEMENTATION
#define RGFW_OPENGL
#include <External/WindowBind.h>
#include <Utility/Embed.h>
#include <EngineCore/Scene.h>
#include <Pipeline/Camera.h>
#include "EngineCore/TextureManager.h"
#include <vector>
#include "chrono"
#include "EngineCore/Input.h"

#include "Components/TransformComponent.h"
#include "Components/TextureComponent.h"
#include "Components/AnimationComponent.h"

#include <Pipeline/Renderer.h>
float GetDelta()
{
	static auto last = std::chrono::high_resolution_clock::now();
	auto now = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<float> delta = now-last; 
	last = now;

	float deltatime = delta.count();
	return deltatime;
}

bool isloaded = false;

vec<Vec2> waypoints;

int main(void) 
{

	auto Wwalk = AnimSpec{8,6,0,8};
	auto Swalk = AnimSpec{8,6,3,8};
	
	auto Awalk = AnimSpec{8,6,1,8};
	auto Dwalk = AnimSpec{8,6,5,8};

	
    RGFW_window* window = RGFW_createWindow("krooz", 0, 0, 1280, 720, RGFW_windowOpenGL);
    gladLoadGLLoader((GLADloadproc)RGFW_getProcAddress_OpenGL);

	#ifdef LEGACY
    	Shader shader(LegacyDefault::vertexshader, LegacyDefault::fragmentshader);
	#else
    	Shader shader(Default::vertexshader, Default::fragmentshader);
	#endif

	Scene scene;

	ent enemy = scene.create();
	auto ssc = AsyncTexture::Enqueue_texture("Assets/Tex_0.png" , enemy);
	scene.add<TransformComponent>(enemy , Vec2(0,0) , Vec2(ssc._width,ssc._height));
	scene.add<TextureComponent>(enemy);

	ent ttx = scene.create();
	scene.add<TextureComponent>(ttx);
	auto hello = AsyncTexture::Enqueue_texture("Assets/boxy.png" , ttx);
	

    Renderer render(scene);
	Camera cam;
	RGFW_event event;
	bool isMoving = false;
	cam.setTarget(scene.get<TransformComponent>(enemy));

	Vec2 TargetPos = Vec2::Zero();

	float frametime = 0.0f;
	while (!RGFW_window_shouldClose(window)) 
	{
		RGFW_pollEvents();
		RGFW_window_checkEvent(window , &event);
		
		float dt = GetDelta();
		cam.Update(dt);
		
		if (Input::IsKeyPressed((int)('w')))
		{
			u64 handle = TextureManager::Get(ttx);
			printf("%llu\n", handle);
			scene.get<TextureComponent>(enemy).ReplaceData(handle);
		}
		if (Input::IsKeyPressed((int)('d')))
		{
			u64 handle = TextureManager::Get(enemy);
			printf("%llu\n", handle);
			scene.get<TextureComponent>(enemy).ReplaceData(handle);
		}

        render.Update(&shader, dt);
		Input::Update(event);
        RGFW_window_swapBuffers_OpenGL(window);
        
    }
    AsyncTexture::Shutdown();
    RGFW_window_close(window);
    return 0;
}

		// frametime += dt;
		// // printf("st: %.5f\n" , frametime);
		// if(frametime >= 1.0f)  
		// {
		// 	frametime = 0.0f;
		// 	auto position = scene.get<TransformComponent>(player).GetPosition();
		// 	waypoints.push_back(position);

		// 	if (waypoints.size() > 10)
        // 		waypoints.erase(waypoints.begin());
		// }


		// if(!waypoints.empty())
		// {
		// 	Vec2 waypointPos = waypoints.front();
		// 	auto enpos = scene.get<TransformComponent>(enemy).GetPosition();
		// 	float dist = (waypointPos - enpos).length();

		// 	if(dist >= 50.0f)
		// 	{
		// 		TargetPos = waypointPos;  
		// 		printf("Position: %.1f %.1f\n" , TargetPos.x ,TargetPos.y);
		// 	}
			
		// 	if(dist <= 10.0f)
		// 	{
		// 		waypoints.erase(waypoints.begin());
		// 	}
		// }

		// // Move toward target
		// auto enemyPos = scene.get<TransformComponent>(enemy).GetPosition();
		// Vec2 direction = (TargetPos - enemyPos);
		// float distance = direction.length();

		// if(distance > 1.0f)  // Avoid jittering when very close
		// {
		// 	direction = direction / distance;  // Normalize
		// 	scene.get<TransformComponent>(enemy).AddOffset({direction.x * 50 * dt, direction.y * 50 * dt});
		// }

		// // printf("Target Pos %.1f , %.1f\n" , TargetPos.x , TargetPos.y);
				
		// isMoving = false;
		// if(Input::IsKeyPressed((u32)('w'))){
		// 	isMoving = true;
		// 	scene.get<AnimationComponent>(player).SwapAnim(Swalk);
		// 	scene.get<TransformComponent>(player).AddOffset({0 , -100*dt});
		// }
		// if(Input::IsKeyPressed((u32)('s'))){
		// 	isMoving = true;
		// 	scene.get<AnimationComponent>(player).SwapAnim(Wwalk);
		// 	scene.get<TransformComponent>(player).AddOffset({0 , 100*dt});
		// }
		// if(Input::IsKeyPressed((u32)('a'))){
		// 	isMoving = true;
		// 	scene.get<AnimationComponent>(player).SwapAnim(Awalk);
		// 	scene.get<TransformComponent>(player).AddOffset({-100*dt , 0});
		// }
		// if(Input::IsKeyPressed((u32)('d'))){
		// 	isMoving = true;
		// 	scene.get<AnimationComponent>(player).SwapAnim(Dwalk);
		// 	scene.get<TransformComponent>(player).AddOffset({100*dt , 0});
		// }
		// if(!isMoving){
		// 	scene.get<AnimationComponent>(player).SwapAnim(AnimSpec{4,4,2,2});
		// }
		
		// // if(Input::IsJustPressed((u32)('p')))
		// // {
		// // 	TextureManager::RemoveBindless(tex2.handle , tex2.texid);
		// // 	scene.get<TextureComponent>(enemy).ReplaceData(tex.handle);
		// // }