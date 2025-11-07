#pragma once

#include "utility/Types.h"
#include "Core/Texture.h"

struct TextureComponent
{
	private:
	int ShaderID = 0;
	
	public:
	TextureComponent(Ref<RawImage> Texture){
		ShaderID = Texture->id;
	}

	int GetShader(){
		return ShaderID;
	}

};
