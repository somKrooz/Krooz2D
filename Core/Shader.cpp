#include "Shader.h"
#include "glad/glad.h"
#include <fstream>
#include <sstream>


namespace Krooz2D
{
	void Shader::CompileShader(ShaderDesciption& desc)
	{
		if (_ShaderProgram != 0) glDeleteProgram(_ShaderProgram);
		auto vertexsrc = desc._vertex.c_str();

		uint32 vert = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vert, 1, &vertexsrc, nullptr);
		glCompileShader(vert);

		auto fragmentsrc = desc._fragment.c_str();
		uint32 frag = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(frag, 1, &fragmentsrc, nullptr);
		glCompileShader(frag);

		uint32 program = glCreateProgram();
		glAttachShader(program, vert);
		glAttachShader(program, frag);
		glLinkProgram(program);

		glDeleteShader(vert);
		glDeleteShader(frag);

		_ShaderProgram = program;
	}

	void Shader::LoadShaderFromFile(ShaderDesciption& desc)
	{
		string _vertexSrc = ReadFile(desc._vertex);
		string _FragmentSrc = ReadFile(desc._fragment);
		auto Compshader = ShaderDesciption({_vertexSrc , _FragmentSrc , false});

		Shader::CompileShader(Compshader);	
	}

	string Shader::ReadFile(string File)
	{
		std::ifstream file(File);
		std::stringstream buffer;
		buffer << file.rdbuf();
		
		return buffer.str();
	}

	uint32 Shader::Get(){
		return _ShaderProgram;
	}

	void Shader::LoadFromString(ShaderDesciption& desc)
	{
		Shader::CompileShader(desc);
	}


	Shader::~Shader(){
		if(_ShaderProgram)
			glDeleteProgram(_ShaderProgram);
	}
}
