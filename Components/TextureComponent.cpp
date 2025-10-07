#include "TextureComponent.h"

namespace Krooz2D
{
    TextureComponent::TextureComponent(string Path){
       _tex = CreateRef<Texture>(Path);
    }

    bool TextureComponent::ReplaceTexture(TextureDescription& desc)
    {
        if (!_tex) return false;
        _tex->Get() = std::move(desc);
        return true;
    }


}
