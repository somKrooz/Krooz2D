
#include "RenderSystem.h"
#include "iostream"

#include "QuadComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "glad/glad.h"


Mat4 projection = Mat4::ortho(0.0f, 1280, 720, 0.0f, -1.0f, 1.0f);
Mat4 view = Mat4::identity();

namespace Krooz2D
{
	void RenderSystem::SetWorld(World& world){
		_currentWorld = CreateRef<World>(world);
	}

	void RenderSystem::Update(uint32 null){
		if(_currentWorld->HasComponent<QuadComponent>()){

			auto Quads = _currentWorld->GetAllComponentsOfTypeID<QuadComponent>();
			for(auto& el : Quads){

				auto Trs = _currentWorld->GetComponent<TransformComponent>(el);
				auto Tex = _currentWorld->GetComponent<TextureComponent>(el);
				auto Quad = _currentWorld->GetComponent<QuadComponent>(el);

				auto shaderProgram = Quad->GetShader(); 
				glUseProgram(shaderProgram);
				glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "u_Projection"), 1, GL_FALSE, projection.value_ptr());
    		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "u_View"), 1, GL_FALSE, view.value_ptr());
				glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "u_Model"), 1, GL_FALSE, Trs->Get().value_ptr());

				Tex->Get().Use();
				glUniform1i(glGetUniformLocation(shaderProgram, "u_Texture"), 0);
				Quad->Get().Draw();
			}
		}
	}
}
