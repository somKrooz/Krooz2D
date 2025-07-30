#pragma once
#include "Maths.h"

using uint = unsigned int;
using cstr = const char* ;

class Shader
{
    private:
    uint m_ShaderProgram;

    public:
    Shader(cstr vertex , cstr fragment);
    ~Shader();
    uint CompileShader(cstr src , uint ShaderType);
    uint GetShaderProgram();
    void CreateShader(uint& vertex , uint& fragment);
    void Use();

    //Access Functions
    void SetMat4(cstr uniform, Mat4 val);
    void SetInt(cstr uniform , int val);
    void SetFloat(cstr uniform , float val);
    void SetV2(cstr uniform , Vec2 val);
    void SetV3(cstr uniform , Vec3 val);
    void SetBool(cstr unifrom , bool val);
};
