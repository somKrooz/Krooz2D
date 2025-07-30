#include "glad/glad.h"
#include "Shader.h"

Shader::Shader(cstr vertex , cstr fragment){
    
    uint vertexShader = CompileShader(vertex , GL_VERTEX_SHADER); 
    uint fragShader = CompileShader(fragment , GL_FRAGMENT_SHADER);
    
    if(vertexShader && fragShader){
        CreateShader(vertexShader , fragShader);
    }
}

Shader::~Shader(){
    glDeleteProgram(m_ShaderProgram);
}

uint Shader::CompileShader(cstr src , uint ShaderType){
    uint Shader = glCreateShader(ShaderType);
    glShaderSource(Shader , 1 , &src , nullptr);
    glCompileShader(Shader);
    return Shader;
}

void Shader::CreateShader(uint& vertex , uint& fragment)
{
   uint program = glCreateProgram();
   if(vertex && fragment){
        glAttachShader(program , vertex);
        glAttachShader(program , fragment);
   }
    glLinkProgram(program);
    this->m_ShaderProgram = program;
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Use(){
    glUseProgram(m_ShaderProgram);
}

uint Shader::GetShaderProgram(){
    return m_ShaderProgram;
}

void Shader::SetMat4(cstr uniform, Mat4 val)
{
    uint location = glGetUniformLocation(m_ShaderProgram , uniform);
    glUniformMatrix4fv(location , 1 , false  , val.value_ptr()); 
}

void Shader::SetInt(cstr uniform, int val)
{
    uint location = glGetUniformLocation(m_ShaderProgram , uniform);
    glUniform1i(location , val); 
}

void Shader::SetFloat(cstr uniform, float val)
{
    uint location = glGetUniformLocation(m_ShaderProgram , uniform);
    glUniform1f(location , val); 
}

void Shader::SetV2(cstr uniform, Vec2 val)
{
    uint location = glGetUniformLocation(m_ShaderProgram , uniform);
    glUniform2f(location , val.x,val.y); 
}

void Shader::SetV3(cstr uniform, Vec3 val)
{
    uint location = glGetUniformLocation(m_ShaderProgram , uniform);
    glUniform3f(location , val.x,val.y ,val.z); 
}

void Shader::SetBool(cstr uniform , bool val){
    uint location = glGetUniformLocation(m_ShaderProgram , uniform);
    glUniform1i(location , (int)val);
}
