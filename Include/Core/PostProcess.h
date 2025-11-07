#pragma once
#include "Core/Shader.h"

struct PostProcess
{
	static inline Ref<Shader> shader;
	static inline unsigned int VAO = 0;
    static inline unsigned int VBO = 0;
	static void BuildPostQuad();
	static void Draw();
	static Ref<Shader>& GetShader();
};
