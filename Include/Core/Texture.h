#pragma once
#include "utility/Types.h"
#include "utility/Maths.h"
#include "unordered_map"

class Texture
{
	private:
	inline static Ref<RawImage> _texture;
	inline static std::unordered_map< int ,Ref<RawImage>> _registry;
	
	public:
	static Ref<RawImage> load(string path);
	static Array<Ref<RawImage>>& Get();
	static void UploadTexturesByIds();
	static void ReplaceTexture(int id, Ref<RawImage> newimage);
};
