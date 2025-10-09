#pragma once
#include "Types.h"
#include "Texture.h"

namespace Krooz2D{

	struct TextureComponent 
	{
		private:
		Ref<Texture> _tex = nullptr;
		
		public:
		TextureComponent(TextureDescription& desc);
		bool ReplaceTexture(TextureDescription& tex);
		Texture& Get();

	};
	
}

