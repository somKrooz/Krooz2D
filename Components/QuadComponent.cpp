#include "QuadComponent.h"

namespace Krooz2D
{
    QuadComponent::QuadComponent(bool hasTexture)
    {
        _buffer = CreateRef<QuadBuffer>();
        _buffer->InitStaticQuad(true);
    }

    QuadBuffer& QuadComponent::Get()
    {
        return *_buffer;
    }
}
