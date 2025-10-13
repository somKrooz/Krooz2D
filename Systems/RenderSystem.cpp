
#include "RenderSystem.h"
#include "QuadComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "glad/glad.h"
#include "Debug.h"
#include "algorithm"
#include "Camera.h"
#include "TagComponent.h"

Mat4 projection = Mat4::ortho(0.0f, 1280, 720, 0.0f, -1.0f, 1.0f);

namespace Krooz2D
{
	void RenderSystem::SetWorld(World& world){
		_currentWorld = &world;
			if(Debug::GetDebugMode()){
			_debug = CreateRef<Debug>();
			Debug::InitWorld(world);
			_debug->DrawState();
		}
	}
  void RenderSystem::Update(float dt) 
    {
			float fade = 0.0f;
			if(IsChanged != Debug::GetStateChange()) {
				fade = Debug::getopacity();
				fade -= dt * 3.0f;
				fade = std::clamp(fade, 0.0f, 1.0f);
				Debug::setOpacity(fade);

				if(fade <= 0.0f) {
					Debug::setOpacity(1.0f);
					IsChanged = Debug::GetStateChange();
				}
			}

			if (!_currentWorld->HasComponent<QuadComponent>()) return;

			auto quadIDs = _currentWorld->GetAllComponentsOfTypeID<QuadComponent>();

			for (auto& id : quadIDs) 
			{
				auto Trs = _currentWorld->GetComponent<TransformComponent>(id);
				auto Tex = _currentWorld->GetComponent<TextureComponent>(id);
				auto Quad = _currentWorld->GetComponent<QuadComponent>(id);
				auto shaderProgram = Quad->GetShader();

				glUseProgram(shaderProgram);

				float alpha = 1.0f;
				Mat4 proj = Camera::GetProjection();
				Mat4 view = Camera::GetMat();

			if (_currentWorld->HasComponentId<TagComponent>(id)) {
				auto tag = _currentWorld->GetComponent<TagComponent>(id)->GetTag();
				if (tag == "Debug") 
				{
					alpha = fade;
					proj = projection;           
					view = Mat4::identity();     
				}
			}

			GLint uAlphaLoc = glGetUniformLocation(shaderProgram, "u_alpha");
			glUniform1f(uAlphaLoc, alpha);
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "u_Model"), 1, GL_FALSE, Trs->Get().value_ptr());
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "u_Projection"), 1, GL_FALSE, proj.value_ptr());
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "u_View"), 1, GL_FALSE, view.value_ptr());

			Tex->Get().Use();
			glUniform1i(glGetUniformLocation(shaderProgram, "u_Texture"), 0);
			Quad->Get().Draw();
		}
	}
}
