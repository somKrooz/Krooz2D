#include "QuadComponent.h"

namespace Krooz2D
{
	QuadComponent::QuadComponent(bool hasTexture, ShaderDesciption desc)
	{
		_buffer = CreateRef<QuadBuffer>();
		_buffer->InitStaticQuad(hasTexture);

		_Shader = CreateRef<Shader>();
		if(desc._isPath){
			_Shader->LoadShaderFromFile(desc);
		}
		else{	
			_Shader->LoadFromString(desc);
		}
	}

	QuadBuffer& QuadComponent::Get()
	{
		return *_buffer;
	}

	
	uint32 QuadComponent::GetShader(){
		return _Shader->Get();
	} 
}
