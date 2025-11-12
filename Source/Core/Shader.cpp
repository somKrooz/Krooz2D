#include "glad/glad.h"
#include "Core/Shader.h"
#include "utility/Logs.h"

Shader::Shader(ShaderDescription desc){
	const char* vertex = desc._vertex.c_str();
	const char* fragment = desc._fragment.c_str();
	CompileShader(vertex , fragment);
}

bool Shader::CompileShader(const char* vs , const char* fr)
{
	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vs, nullptr);
	glCompileShader(vertex);

	int success;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
		char log[512];
        glGetShaderInfoLog(vertex, 512, nullptr, log);
		Error("Failed To Compile Vertex Shader: {}" , log);
        return false;
	}

	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fr, nullptr);
	glCompileShader(fragment);

	glGetShaderiv(fragment , GL_COMPILE_STATUS , &success);
	if(!success){
		char log[512];
		glGetShaderInfoLog(fragment , 512 , nullptr , log);
		Error("Failed To Compile Fragment Shader: {}" , log);
		return false;
	}

	GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

	glDeleteShader(vertex);
    glDeleteShader(fragment);
	_shader = program;
	
	return true;
}

uint32 Shader::GetShader(){
	return _shader;
}


void Shader::setMat4(string location , Mat4& value)
{
	int Loc = glGetUniformLocation(GetShader() , location.c_str());
	if (Loc == -1) {
    	Error("Invalid Location {}", location);
    	return;
	}
	glUniformMatrix4fv(Loc, 1, GL_FALSE, value.value_ptr());
}

void Shader::setTex32(string location , int value[32])
{
	int Loc = glGetUniformLocation(GetShader(), "tex");
	if (Loc == -1) {
    	Error("Invalid Location {}", location);
    	return;
	}
	glUniform1iv(Loc, 32, value);
}

void Shader::setInt(string location , int value)
{
	int Loc = glGetUniformLocation( GetShader(), location.c_str());
	if (Loc == -1) {
    	Error("Invalid Location {}", location);
    	return;
	}
	glUniform1i(Loc,  value);
}
void Shader::setFloat(string location ,float value){
	int Loc = glGetUniformLocation( GetShader(), location.c_str());
	if (Loc == -1) {
    	Error("Invalid Location {}", location);
    	return;
	}
	glUniform1f(Loc,  value);
}

void Shader::use(){
	glUseProgram(GetShader());
}
