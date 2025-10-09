#pragma once
#include "Types.h"

namespace Krooz2D
{
	class Texture
	{
		private:
		Ref<TextureDescription> _tex = nullptr;
		
		public:
		Texture(){}
		Texture(TextureDescription& desc);

		TextureDescription& Get();
		static Ref<TextureDescription> LoadTexture(const std::string& path);
		
		void Use();
	};

}
