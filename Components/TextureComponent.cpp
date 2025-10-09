#include "TextureComponent.h"

namespace Krooz2D
{
	TextureComponent::TextureComponent(TextureDescription& desc){
		_tex = CreateRef<Texture>(desc);
	}

	bool TextureComponent::ReplaceTexture(TextureDescription& tex)
	{
		_tex = CreateRef<Texture>(tex);
		return true;
	}

	Texture& TextureComponent::Get()
	{
		return *_tex;
	}

}
