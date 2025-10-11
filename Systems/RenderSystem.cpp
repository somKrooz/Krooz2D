
#include "RenderSystem.h"
#include "QuadComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "glad/glad.h"
#include "Debug.h"
#include "algorithm"

Mat4 projection = Mat4::ortho(0.0f, 1280, 720, 0.0f, -1.0f, 1.0f);
Mat4 view = Mat4::identity();

namespace Krooz2D
{
	void RenderSystem::SetWorld(World& world){
			if(Debug::GetDebugMode()){
			_debug = CreateRef<Debug>();
			_debug->DrawState();
		}
		_currentWorld = CreateRef<World>(world);
	}


void RenderSystem::Update(float dt){
	// Needs Better System
		float fade = 0.0f;
    if(IsChanged != Debug::GetStateChange()){
				fade = Debug::getopacity();
				fade -= dt * 3.0f;
        fade = std::clamp(fade, 0.0f, 1.0f);
        Debug::setOpacity(fade);

        if(fade <= 0.0f) {
            Debug::setOpacity(1.0f);
            IsChanged = Debug::GetStateChange();
        }
    }
		//

    if (_currentWorld->HasComponent<QuadComponent>()) {
        auto Quads = _currentWorld->GetAllComponentsOfTypeID<QuadComponent>();

        for (auto& el : Quads) {
            auto Trs = _currentWorld->GetComponent<TransformComponent>(el);
            auto Tex = _currentWorld->GetComponent<TextureComponent>(el);
            auto Quad = _currentWorld->GetComponent<QuadComponent>(el);
            auto shaderProgram = Quad->GetShader(); 
            glUseProgram(shaderProgram);

            GLint uAlphaLoc = glGetUniformLocation(shaderProgram, "u_alpha");

            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "u_Projection"), 1, GL_FALSE, projection.value_ptr());
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "u_View"), 1, GL_FALSE, view.value_ptr());
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "u_Model"), 1, GL_FALSE, Trs->Get().value_ptr());

            if(_currentWorld->HasComponentId<TagComponent>(el)){
                glUniform1f(uAlphaLoc, fade);
            } else {
                glUniform1f(uAlphaLoc, 1.0f);
            }
            
            Tex->Get().Use();
            glUniform1i(glGetUniformLocation(shaderProgram, "u_Texture"), 0);
            Quad->Get().Draw();
        }
    }
}
}
