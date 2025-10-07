#include "QuadComponent.h"

namespace Krooz2D
{
    QuadComponent::QuadComponent(TransformComponent& Trs , TextureComponent& Tex)
    {
        _trs = CreateRef<TransformComponent>(Trs);
        _tex = CreateRef<TextureComponent>(Tex);
    }

    QuadComponent::QuadComponent(TransformComponent& Trs){
        _trs = CreateRef<TransformComponent>(Trs);
    }
}
