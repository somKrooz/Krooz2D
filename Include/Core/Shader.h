#pragma once

#include "utility/Types.h"
#include "utility/Maths.h"

class Shader{
	private:
	uint32 _shader;

	public:
	Shader(ShaderDescription desc);
	bool CompileShader(const char* vertex , const char* fragment); 
	uint32 GetShader();

	void setMat4(string location , Mat4& value);
	void setTex32(string location , int value[30]);
	void setInt(string location ,int value);

	void setFloat(string location ,float value);
	void use();
};
