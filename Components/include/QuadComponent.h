#pragma once

#include "TextureComponent.h"
#include "TransformComponent.h"

namespace Krooz2D
{
    struct QuadComponent
    {
        Ref<TransformComponent> _trs = nullptr;
        Ref<TextureComponent> _tex = nullptr;
        
        QuadComponent() = default;
        QuadComponent(TransformComponent& Trs , TextureComponent& Tex);
        QuadComponent(TransformComponent& Trs);
    };

}
