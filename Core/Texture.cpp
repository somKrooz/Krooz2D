#include "Texture.h"
#include "iostream"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glad/glad.h"


namespace Krooz2D
{
	Texture::Texture(TextureDescription& desc)
	{   
		_tex = CreateRef<TextureDescription>(desc);

		glGenTextures(1, &_tex->_id);
		glBindTexture(GL_TEXTURE_2D ,_tex->_id);
		glTexImage2D(GL_TEXTURE_2D , 0, GL_RGBA, _tex->_width , _tex->_height ,0,GL_RGBA , GL_UNSIGNED_BYTE , desc._pixels.data());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	}


	void Texture::Use()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D , _tex->_id);
	}
	
	TextureDescription& Texture::Get()
	{
		return *_tex;
	}

	Ref<TextureDescription> Texture::LoadTexture(const std::string& path)
	{
			Ref<TextureDescription> tex = CreateRef<TextureDescription>();

			uint8* data = stbi_load(path.c_str(), &tex->_width, &tex->_height, &tex->_channels, 4);
			tex->_pixels.assign(data, data + (tex->_width * tex->_height * 4));
			stbi_image_free(data);

			return tex; 
	}

}
