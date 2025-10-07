#pragma once
#include "Types.h"
#include "Texture.h"

namespace Krooz2D{

    struct TextureComponent 
    {
        Ref<Texture> _tex = nullptr;
        
        TextureComponent(string path);
        bool ReplaceTexture(TextureDescription& desc);
    };

}

