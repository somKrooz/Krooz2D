#pragma once

#include "Types.h"

namespace Krooz2D
{
	class Shader
	{
		private:
		uint32 _ShaderProgram = 0;

		public:
		Shader() {}
		~Shader();
		void CompileShader(ShaderDesciption& desc);

		void LoadShaderFromFile(ShaderDesciption& desc);
		void LoadFromString(ShaderDesciption& desc);
		std::string ReadFile(string file);
		uint32 Get();
	};

}
