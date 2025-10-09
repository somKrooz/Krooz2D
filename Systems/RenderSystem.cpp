
#include "RenderSystem.h"
#include "iostream"

#include "QuadComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "glad/glad.h"

namespace Krooz2D
{
	void RenderSystem::SetWorld(World& world){
		_currentWorld = CreateRef<World>(world);
	}

	void RenderSystem::Update(uint32 shaderProg){
		if(_currentWorld->HasComponent<QuadComponent>()){

			auto Quads = _currentWorld->GetAllComponentsOfTypeID<QuadComponent>();
			for(auto& el : Quads){

				auto Trs = _currentWorld->GetComponent<TransformComponent>(el);
				auto Tex = _currentWorld->GetComponent<TextureComponent>(el);
				auto Quad = _currentWorld->GetComponent<QuadComponent>(el);
				
				Tex->Get().Use();  
				glUniform1i(glGetUniformLocation(shaderProg, "u_Texture"), 0);

				GLint loc = glGetUniformLocation(shaderProg, "u_Model");
				glUniformMatrix4fv(loc, 1, GL_FALSE, Trs->Get().value_ptr());
				Quad->Get().Draw();
			}
		}
	}
}
