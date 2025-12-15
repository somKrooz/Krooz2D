#pragma once
#include "Utility/Types.h"
#include "Utility/Maths.h"

class Shader
{
private:
	inline static u32 shaderProgram = -1;

public:
	Shader(str vertex, str fragment);
	u32 CompileShader(u32 type, cstr* source);
	static u32 Get();
	void Use();
	void setMat4(str location, Mat4& value);
	void setVec2(str location, Vec2 value);
	~Shader();
};
