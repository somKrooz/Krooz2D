#include "Pipeline/Renderer.h"
#include "Components/TextureComponent.h"
#include "Components/TransformComponent.h"
#include "Components/AnimationComponent.h"
#include "Pipeline/Loader.h"
#include "External/OpenglBind.h"
#include "EngineCore/TextureManager.h"
#include "Utility/Maths.h"
#include "Pipeline/Camera.h"

#define LEGACY
Mat4 Ortho = Mat4::ortho(0, 1280, 720, 0, -1, 1);
Mat4 View = Mat4::identity();


#define GL_CHECK(x) \
  do { x; GLenum e = glGetError(); \
  if (e != GL_NO_ERROR) printf("GL error %d at %s:%d\n", e, __FILE__, __LINE__); } while(0)



Renderer::Renderer(Scene& scene)
{
	buffer = createScope<GpuLayout>();

	CurrentWorld = &scene;
	buffer->vao.Bind();
	buffer->vbo.Bind();
	buffer->vbo.Push(quad, staticDraw);
	buffer->vao.Push(0, 2, 4 * sizeof(float), (void*)0);
	buffer->vao.Push(1, 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	buffer->vao.unBind();

	BuildMeshData();
	
	#ifdef LEGACY
	{
		buffer->vao.Bind();
		buffer->ins.Bind();
		buffer->ins.Push(Objects, dynamicDraw);
		buffer->vao.Push(2, 2, sizeof(Instance), (void*)0);
		buffer->vao.Divisor(2);
	
		buffer->vao.Push(3, 2, sizeof(Instance), (void*)(2 * sizeof(float)));
		buffer->vao.Divisor(3);
		buffer->vao.Push(4, 1, sizeof(Instance), (void*)(4 * sizeof(float)));
		buffer->vao.Divisor(4);
	}
	#else
	{
		buffer->vao.Bind();
		buffer->ins.Bind();
		buffer->ins.Push(BindlessObjects, dynamicDraw);
		buffer->vao.Push(2, 2, sizeof(BindlessInstance), (void*)(offsetof(BindlessInstance ,x)));
		buffer->vao.Divisor(2);
	
		buffer->vao.Push(3, 2, sizeof(BindlessInstance), (void*)(offsetof(BindlessInstance ,sx)));
		buffer->vao.Divisor(3);
		
		buffer->vao.PushInt(4, 1, sizeof(BindlessInstance),(void*)offsetof(BindlessInstance, low));
		buffer->vao.Divisor(4);

		buffer->vao.PushInt(5, 1, sizeof(BindlessInstance),(void*)offsetof(BindlessInstance, high));
		buffer->vao.Divisor(5);

	}
	#endif

}

void Renderer::Update(Shader* shader, float delta)
{
	glViewport(0, 0, 1280, 720);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(.1, .1, .1, 1.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	if(Camera::isCameraExist()){
		Ortho = Camera::GetProjection();
		View = Camera::GetView();
	}
	shader->Use();
	shader->setMat4("uProjection", Ortho);
	shader->setMat4("uView", View);

	while(AsyncTexture::HasCompleted())
	{
		auto Result = AsyncTexture::GetResults();
		#ifdef LEGACY
		auto handle = TextureManager::CreateTextureHandle(Result.image.get());
		CurrentWorld->get<TextureComponent>(Result.Ent).ReplaceData(handle);
		TextureManager::Push(Result.Ent , handle);


		#else
		auto handle = TextureManager::CreateBindLess(Result.image.get());
		CurrentWorld->get<TextureComponent>(Result.Ent).ReplaceData(handle);
		TextureManager::Push(Result.Ent ,handle);
		#endif

		printf("Current Size: %lu\n", TextureManager::GetSize());
	}
	BuildMeshData();
	#ifdef LEGACY
	buffer->ins.Bind();
	buffer->ins.Push(Objects, dynamicDraw);
	buffer->vao.Bind();
	BufferRenderCall::DrawDyamic(Objects.size());
	#else
	buffer->ins.Bind();
	buffer->ins.Push(BindlessObjects, dynamicDraw);
	buffer->vao.Bind();
	GL_CHECK(glUseProgram(shader->Get()));
	BufferRenderCall::DrawDyamic(BindlessObjects.size());
	#endif
}


// void Renderer::BuildMeshData()
// {
//     BindlessObjects.clear();

//     for (auto& [id, trs] : CurrentWorld->all<TransformComponent>())
//     {
//         u64 handle = CurrentWorld
//             ->get<TextureComponent>(id)
//             .GetHandle();

//         // ❗ CRITICAL: never push invalid bindless handles
//         if (handle == 0)
//             continue;

//         BindlessObjects.push_back({
//             trs.GetPosition().x,
//             trs.GetPosition().y,
//             trs.GetScale(),
//             trs.GetScale(),

//             // split 64-bit bindless handle
//             static_cast<uint32_t>(handle & 0xFFFFFFFFu),
//             static_cast<uint32_t>(handle >> 32)
//         });
//     }
// }

void Renderer::BuildMeshData() {
	Objects.clear();
	BindlessObjects.clear();
	
	for (auto& [id, trs] : CurrentWorld->all<TransformComponent>()) {
		u64 handle = CurrentWorld->get<TextureComponent>(id).GetHandle();

		printf("%llu\n", handle);
#ifdef LEGACY
		Objects.push_back({
			trs.GetPosition().x,
			trs.GetPosition().y,
			trs.GetScale(),
			trs.GetScale(),
			(float)handle
		});
	#else
		if (handle == 0) continue;
		BindlessObjects.push_back({
			trs.GetPosition().x,
			trs.GetPosition().y,
			trs.GetScale(),
			trs.GetScale(),
			static_cast<uint32_t>(handle & 0xFFFFFFFFu),
            static_cast<uint32_t>(handle >> 32)
		});
	#endif
		
    }
}


// buffer->vao.Push(
// 6,
// 2,
// sizeof(Instance),
// (void*)offsetof(Instance, uvox)
// );
// buffer->vao.Divisor(6);

// buffer->vao.Push(
// 	7,
// 	2,
// 	sizeof(Instance),
// 	(void*)offsetof(Instance, uvsx)
// );
// buffer->vao.Divisor(7);

// buffer->vao.unBind();

// TextureManager::createDefaultTexture();



// Vec2 GetUVOffset(int tileX, int tileY, int tilesX, int tilesY)
// {
//     float sx = 1.0f / tilesX;
//     float sy = 1.0f / tilesY;

//     return Vec2(
//         tileX * sx,   
//         tileY * sy  
//     );
// }

// Vec2 offset = Vec2(0,0);
// Vec2 scale = Vec2(1,1);
// if(CurrentWorld->has<AnimationComponent>(id))
// {
// 	auto& anim = CurrentWorld->get<AnimationComponent>(id);
// 	auto* animation = anim.Get();
// 	offset = GetUVOffset(
// 		anim.GetFrameNumber(),
// 		animation->column,
// 		animation->countX,
// 		animation->countY
// 	);

// 	scale = Vec2(
// 		1.0f / animation->countX,
// 		1.0f / animation->countY
// 	);
// }
// if (handle == 0) {
// 	    handle = TextureManager::GetDefaultHandle();
// 	}



// buffer->vao.Push(
// 6,
// 2,
// sizeof(Instance),
// (void*)offsetof(Instance, uvox)
// );
// buffer->vao.Divisor(6);

// buffer->vao.Push(
// 	7,
// 	2,
// 	sizeof(Instance),
// 	(void*)offsetof(Instance, uvsx)
// );
// buffer->vao.Divisor(7);

// buffer->vao.unBind();

// TextureManager::createDefaultTexture();



// Vec2 GetUVOffset(int tileX, int tileY, int tilesX, int tilesY)
// {
//     float sx = 1.0f / tilesX;
//     float sy = 1.0f / tilesY;

//     return Vec2(
//         tileX * sx,   
//         tileY * sy  
//     );
// }

// Vec2 offset = Vec2(0,0);
// Vec2 scale = Vec2(1,1);
// if(CurrentWorld->has<AnimationComponent>(id))
// {
// 	auto& anim = CurrentWorld->get<AnimationComponent>(id);
// 	auto* animation = anim.Get();
// 	offset = GetUVOffset(
// 		anim.GetFrameNumber(),
// 		animation->column,
// 		animation->countX,
// 		animation->countY
// 	);

// 	scale = Vec2(
// 		1.0f / animation->countX,
// 		1.0f / animation->countY
// 	);
// }
// if (handle == 0) {
// 	    handle = TextureManager::GetDefaultHandle();
// 	}
