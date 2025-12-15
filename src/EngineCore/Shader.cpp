#include "External/OpenglBind.h"
#include "EngineCore/Shader.h"

Shader::Shader(str vertex, str fragment)
{
	auto vertexShader = CompileShader(GL_VERTEX_SHADER, vertex.c_str());
	auto fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragment.c_str());

	u32 program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		printf("Shader linking error:\n", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	shaderProgram = program;
}

u32 Shader::CompileShader(u32 type, cstr* source)
{
	uint32_t shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char buffer[512];
		glGetShaderInfoLog(shader, sizeof(buffer), nullptr, buffer);
		printf("Shader Compile Error: %s\n", buffer);
	}

	return shader;
};

void Shader::Use() {
	glUseProgram(shaderProgram);
}

Shader::~Shader() {
	glDeleteProgram(shaderProgram);
}


void Shader::setMat4(str location, Mat4& value)
{
	int Loc = glGetUniformLocation(shaderProgram, location.c_str());
	glUniformMatrix4fv(Loc, 1, GL_FALSE, value.value_ptr());
}

void Shader::setVec2(str location, Vec2 value)
{
	int Loc = glGetUniformLocation(shaderProgram, location.c_str());
	glUniform2f(Loc, value.x , value.y);
}

u32 Shader::Get() {
	return shaderProgram;
}
