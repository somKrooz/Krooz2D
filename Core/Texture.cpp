#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glad/glad.h"


namespace Krooz2D
{
    Texture::Texture(string path)
    {   
        TextureDescription Tex;
        // stbi_set_flip_vertically_on_load(true);

        uint8* _data = stbi_load(path.c_str() , &Tex._width  ,&Tex._height , &Tex._channels ,4);
        _tex = CreateRef<TextureDescription>(Tex);

        glGenTextures(1, &_tex->_id);
        glBindTexture(GL_TEXTURE_2D ,_tex->_id);
        glTexImage2D(GL_TEXTURE_2D , 0, GL_RGBA, _tex->_width , _tex->_height ,0,GL_RGBA , GL_UNSIGNED_BYTE , _data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(_data);
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
}
