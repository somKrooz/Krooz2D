#pragma once
#include "Types.h"

namespace Krooz2D
{
    class Texture
    {
        private:
        Ref<TextureDescription> _tex = nullptr;
        
        public:
        Texture(string Path);
        TextureDescription& Get();
        void Use();
    };

}
