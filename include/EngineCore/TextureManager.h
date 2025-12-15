#pragma once
#include "Utility/Types.h"


struct DeleteTex {
    GLuint id;
    GLuint64 handle;
    GLsync fence;
};
struct TextureManager
{
	private:
	inline static u64 DefaultTexture = 0;
	inline static std::queue<DeleteTex> deleteQueue;
	
	public:
	static u64 createBindlessHandle(ImageResource* image, Texture* tex);
	static void RemoveBindless(u64 handle , u32 id);
	static u32 createSamplerHandle(ImageResource* image);
	static void createDefaultTexture();
	static void processDelete();
	static u64& GetDefaultHandle();
};
