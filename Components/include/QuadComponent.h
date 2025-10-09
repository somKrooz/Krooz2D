#pragma once

#include "Buffer.h"
#include "Shader.h"
#include "Default.h"

namespace Krooz2D
{
	struct QuadComponent
	{
		private:
		Ref<QuadBuffer> _buffer;
		Ref<Shader> _Shader;

		public:
		QuadComponent(bool hasTexture , ShaderDesciption desc);
		QuadBuffer& Get();
		uint32 GetShader();

	};
}
