#include "TextureComponent.h"


namespace Krooz2D
{
    TextureComponent::TextureComponent(Texture& texData){
       _tex = CreateRef<Texture>(texData);
    }

    bool TextureComponent::ReplaceTexture(const std::vector<uint8>& newPixels, int width, int height, int channels)
    {
        if (!_tex) return false;
        _tex->_pixels = newPixels;
        _tex->_width = width;
        _tex->_height = height;
        _tex->_channels = channels;
        
        _tex->_dirty = true; 
        return true;
    }
    const Texture& TextureComponent::Get(){
        return *_tex;
    } 
}
