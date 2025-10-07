#pragma once
#include "Types.h"


namespace Krooz2D{

    struct TextureComponent 
    {
        Ref<Texture> _tex = nullptr;
        
        TextureComponent() = default;
        TextureComponent(Texture& texData);
        bool ReplaceTexture(const std::vector<uint8>& newPixels, int width, int height, int channels);
        const Texture& Get(); 
    };

}

