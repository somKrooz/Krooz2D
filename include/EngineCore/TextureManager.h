#pragma once
#include "Utility/Types.h"
class TextureManager
{
	private:
	inline static umap<u32, u64> Ent_Texture_Handle;

	public:
		static size_t GetSize();
		static int CreateTextureHandle(ImageResource *image);
		static u64 CreateBindLess(ImageResource *image);
		static void Push(u32 Ent, u64 Handle);
		static u64 Get(u32 Ent);
};