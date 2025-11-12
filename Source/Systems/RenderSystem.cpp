#include "glad/glad.h"
#include "Systems/RenderSystem.h"
#include "Components/TextureComponent.h"
#include "Core/Buffer.h"
#include "Utility/Logs.h"
#include "Core/StateManager.h"
#include "Utility/Embed.h"
#include "Camera.h"
#include "Core/Window.h"
#include "Core/FBuffer.h"
#include "PostProcess.h"

inline float krooz = 0.0f;
RenderSystem::RenderSystem()
{
	buffer = createScope<Buffer>();
	globalShader = createScope<Shader>(Defaults::DefaultShader);
	buffer->InitStatic();
	globalShader->use();
	BuildInstanceData();


	buffer->InitInstance(ObjectPool);
	Texture::UploadTexturesByIds(); 

	int samplers[32];
	for (int i = 0; i < 32; ++i)
		samplers[i] = i;
	
	globalShader->use();
	globalShader->setTex32("tex", samplers);
	getInfo();

	if(_isPostProcess){
		FBuffer::Init();
		PostProcess::BuildPostQuad();
	}
}   

void RenderSystem::Update(float dt)
{
    glViewport(0, 0, getWindowSize().x, getWindowSize().y);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (_isPostProcess) {
        FBuffer::CaptureStart();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    globalShader->use();
    globalShader->setMat4("uProjection", Camera::GetProjection());
    globalShader->setMat4("uView", Camera::GetMat());

    BuildInstanceData();
    Texture::UploadTexturesByIds(); 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    buffer->UpdateInstance(ObjectPool);
    buffer->Draw();

    if (_isPostProcess) {
		krooz += dt;
        FBuffer::CaptureEnd();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, FBuffer::GetFBOTexture());

        PostProcess::GetShader()->use();
        PostProcess::GetShader()->setInt("screenTexture", 0);
        PostProcess::GetShader()->setFloat("uTime", krooz);

        PostProcess::Draw();

        glBindTexture(GL_TEXTURE_2D, 0);
        glUseProgram(0);
    }
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
		Error("Set Current World Context In StateManager...");
		exit(0);
	}
}


void RenderSystem::EnablePostProcess(bool val){
	_isPostProcess = val;
}
