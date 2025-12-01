#include "glad/glad.h"
#include "Systems/RenderSystem.h"
#include "Components/TextureComponent.h"
#include "Core/Buffer.h"
#include "Core/Utility/Logs.h"
#include "Core/StateManager.h"
#include "Utility/Embed.h"
#include "Core/Camera.h"
#include "Core/Window.h"
#include "PostProcess.h"

inline float krooz = 0.0f;
RenderSystem::RenderSystem()
{
    buffer = createScope<GPU_LAYOUT>();
    globalShader = createScope<Shader>(Defaults::DefaultShader);

    buffer->array = createScope<vertexArray>();
    buffer->buf   = createScope<vertexBuffer>();
    buffer->ins   = createScope<vertexBuffer>();

    buffer->array->init();  
    buffer->buf->init();     
    buffer->ins->init();     

	// start quad
    buffer->array->bind();
    buffer->buf->bind();
    buffer->buf->push(quad, DrawMode::STATIC);
    buffer->array->push(0, 2, 4 * sizeof(float), (void*)0);        
    buffer->array->push(1, 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    buffer->array->unbind();
    buffer->ins->bind();
	// end quad

	globalShader->use();
    BuildInstanceData();

    buffer->ins->push(ObjectPool, DrawMode::DYNAMIC);
    buffer->array->bind();
	buffer->array->push(2,2,sizeof(Instance) , (void*)0);
	buffer->array->divisor(2);
	buffer->array->push(3,2,sizeof(Instance) , (void*)(2*sizeof(float)));
    buffer->array->divisor(3);
	buffer->array->push(4,1,sizeof(Instance) , (void*)(3*sizeof(float)));
    buffer->array->divisor(4);

    buffer->array->unbind();
    buffer->ins->unbind();

    Texture::UploadTexturesByIds();
    int samplers[32];
    for (int i = 0; i < 32; ++i) samplers[i] = i;
    globalShader->use();
    globalShader->setTex32("tex", samplers);

    getInfo();
}

void RenderSystem::Update(float dt)
{
    glViewport(0, 0, getWindowSize().x, getWindowSize().y);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    globalShader->use();
    globalShader->setMat4("uProjection", Camera::GetProjection());
    globalShader->setMat4("uView", Camera::GetMat());

    BuildInstanceData();
    Texture::UploadTexturesByIds(); 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
	buffer->ins->bind();
	buffer->ins->push(ObjectPool , DrawMode::DYNAMIC);

	buffer->array->bind();
    DrawBuffer::DrawInstance(ObjectPool.size());
}


void RenderSystem::BuildInstanceData()
{
	World* CurrentWorld = StateManager::GetCurrentWorld();
	if(CurrentWorld != nullptr)
	{
		ObjectPool.clear();
		for (auto& [id, tex] : CurrentWorld->all<TextureComponent>()) {
			 if (!CurrentWorld->IsEntityActive(id)) continue;  
			auto& trs = CurrentWorld->get<TransformComponent>(id);

			float x = trs.GetPosition().x;
			float y = trs.GetPosition().y;
			float sx = trs.GetScaleVec().x;
			float sy = trs.GetScaleVec().y;
			int texID = tex.GetShader(); 
			ObjectPool.push_back({ x, y, sx, sy, (texID - 1) });
		}
	}	

	if(CurrentWorld == nullptr){
		Error("Set Current World Context In StateManager...");;
	}
}


void RenderSystem::EnablePostProcess(bool val){
	_isPostProcess = val;
}
