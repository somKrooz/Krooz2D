#include "glad/glad.h"
#include "Core/Texture.h"
#include "Core/Utility/Logs.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"


Ref<RawImage> Texture::load(string path)
{
	if(_registry.size() > 30){
		Error("Size Limit Reached: {}" , _registry.size());
		exit(0);
	}

    Ref<RawImage> local = createRef<RawImage>(); 
	local->id = 0;
    unsigned char* data = stbi_load(path.c_str(), &local->width, &local->height, &local->channel, 4);	
	// unsigned char* resizedData = new unsigned char[512 * 512 * 4];
	// stbir_resize_uint8_srgb(
    // 	data, local->width, local->height, 0,            
    // 	resizedData, 512, 512, 0, STBIR_RGBA                             
	// );

	// local->width = 512;
	// local->height = 512;
	local->data.assign(data , data + (local->width * local->height *4 ));	


	stbi_image_free(data);

	// if(resizedData != nullptr){
		// delete[] resizedData;
	// }
	
	glGenTextures(1, &local->id);
	glBindTexture(GL_TEXTURE_2D ,local->id);
	glTexImage2D(GL_TEXTURE_2D , 0, GL_RGBA, local->width , local->height ,0,GL_RGBA , GL_UNSIGNED_BYTE , local->Get());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glGenerateMipmap(GL_TEXTURE_2D);  

	_registry[local->id] = local;
    return local;
}


Array<Ref<RawImage>>& Texture::Get() {
    static Array<Ref<RawImage>> cache;
    cache.clear();
    for (auto& el : _registry)
        cache.push_back(el.second);
    return cache;
}

void Texture::ReplaceTexture(int id, Ref<RawImage> newimage)
{
    if(newimage->data.empty()) return;
	glBindTexture(GL_TEXTURE_2D ,id);
	glTexImage2D(GL_TEXTURE_2D , 0, GL_RGBA, newimage->width , newimage->height ,0,GL_RGBA , GL_UNSIGNED_BYTE , newimage->Get());
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::UploadTexturesByIds()
{
	// Only bind first 30 textures to units 0-29
	// size_t maxTextures = std::min(Texture::Get().size(), size_t(30));
	for (size_t i = 0; i < Texture::Get().size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, Texture::Get()[i]->id);
	}
}
