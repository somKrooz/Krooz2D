#include "TextureComponent.h"

namespace Krooz2D
{
	TextureComponent::TextureComponent(Ref<TextureDescription> desc){
		 _tex = CreateRef<Texture>(*desc); 
	}

	bool TextureComponent::ReplaceTexture(Ref<TextureDescription> tex)
	{
		_tex->ReplaceTexture(*tex);
    return true;
	}

	Texture& TextureComponent::Get()
	{
		return *_tex;
	}

}
