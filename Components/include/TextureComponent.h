#pragma once
#include "Types.h"
#include "Texture.h"

namespace Krooz2D{

	struct TextureComponent 
	{
		private:
		Ref<Texture> _tex = nullptr;
		
		public:
		TextureComponent(Ref<TextureDescription> desc);
		bool ReplaceTexture(Ref<TextureDescription> tex);
		Texture& Get();

	};
	
}

