#include "Pipeline/Renderer.h"
#include "Components/TextureComponent.h"
#include "Components/TransformComponent.h"
#include "Components/AnimationComponent.h"
#include "Pipeline/Loader.h"
#include "External/OpenglBind.h"
#include "EngineCore/TextureManager.h"
#include "Utility/Maths.h"
#include "Pipeline/Camera.h"

Mat4 Ortho = Mat4::ortho(0, 1280, 720, 0, -1, 1);
Mat4 View = Mat4::identity();


Vec2 GetUVOffset(int tileX, int tileY, int tilesX, int tilesY)
{
    float sx = 1.0f / tilesX;
    float sy = 1.0f / tilesY;

    return Vec2(
        tileX * sx,   
        tileY * sy  
    );
}

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
	buffer->vao.Bind();
	buffer->ins.Bind();
	buffer->ins.Push(Objects, dynamicDraw);
	buffer->vao.Push(2, 2, sizeof(Instance), (void*)0);
	buffer->vao.Divisor(2);

	buffer->vao.Push(3, 2, sizeof(Instance), (void*)(2 * sizeof(float)));
	buffer->vao.Divisor(3);

	buffer->vao.Push(4, 1, sizeof(Instance), (void*)(offsetof(Instance , id)));
	buffer->vao.Divisor(4);

	// buffer->vao.Push(5, 1, sizeof(Instance), (void*)(4 * sizeof(float) + 4)); 
	// buffer->vao.Divisor(5);

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
		auto image = AsyncTexture::GetResults();
		auto handle = TextureManager::CreateTextureHandle(image.image.get());
		CurrentWorld->get<TextureComponent>(image.tex->entid).ReplaceData(handle);
	}
	
	BuildMeshData();
	for(auto& [_ , comp] : CurrentWorld->all<AnimationComponent>()){
		comp.Update(delta);
	}

	buffer->ins.Bind();
	buffer->ins.Push(Objects, dynamicDraw);
	buffer->vao.Bind();
	BufferRenderCall::DrawDyamic(Objects.size());
}


void Renderer::BuildMeshData() {
    Objects.clear();
    for (auto& [id, trs] : CurrentWorld->all<TransformComponent>()) {
        GLuint64 handle = 0;

		Vec2 offset = Vec2(0,0);
		Vec2 scale = Vec2(1,1);

		handle = CurrentWorld->get<TextureComponent>(id).GetHandle();

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
        //     handle = TextureManager::GetDefaultHandle();
        // }

		Objects.push_back({
			trs.GetPosition().x,
				trs.GetPosition().y,
				trs.GetScale(),
				trs.GetScale(),
				(float)handle
			// (uint32_t)(handle & 0xFFFFFFFF),
            // (uint32_t)((handle >> 32) & 0xFFFFFFFF),
			// offset.x,
			// offset.y,
			// scale.x,
			// scale.y
		});
		// Objects.push_back({
        //     trs.GetPosition().x,
        //     trs.GetPosition().y,
        //     trs.GetScale(),
        //     trs.GetScale(),
        //     (uint32_t)(handle & 0xFFFFFFFF),
        //     (uint32_t)((handle >> 32) & 0xFFFFFFFF),
		// 	offset.x,
		// 	offset.y,
		// 	scale.x,
		// 	scale.y
        // });
    }
}
