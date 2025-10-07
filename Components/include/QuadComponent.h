#pragma once

#include "Buffer.h"

namespace Krooz2D
{
    struct QuadComponent
    {
        private:
        Ref<QuadBuffer> _buffer;

        public:
        QuadComponent(bool hasTexture = true);
        QuadBuffer& Get();
    };
}
