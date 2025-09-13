#include "PostProcess.h"
#include "glad/glad.h"
#include "Default.hpp"
#include "Engine.h"
PostProcess::PostProcess()
{
    std::vector<float> vertices = {
        // pos      // uv
        0.0f, 0.0f, 0.0f, 0.0f,  
        1.0f, 0.0f, 1.0f, 0.0f, 
        1.0f, 1.0f, 1.0f, 1.0f,  

        0.0f, 0.0f, 0.0f, 0.0f, 
        1.0f, 1.0f, 1.0f, 1.0f,  
        0.0f, 1.0f, 0.0f, 1.0f  
    };

    buffer = new Buffer();
    buffer->UploadData(vertices , 4 , GL_TRIANGLES);

    // Default shader (can be replaced later)
    mshader = new Shader(DefaultShader::PostVert , DefaultShader::PostFrag);

    // fullscreen model matrix
    model = Mat4::identity();
    model = model * Mat4::translate(Vec2(0,0));
    model = model * Mat4::scale(Vec2(1280,720));
}

void PostProcess::Draw(unsigned int tex)
{

    mshader->Use();
    mshader->SetMat4("uModel" , model);
    mshader->SetMat4("uProjection", Mat4::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f));
    mshader->SetMat4("uView", Mat4::identity());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    mshader->SetInt("uSceneTex", 0); 
    mshader->SetFloat("uTime", Engine::GetDeltaTime()); 

    buffer->Bind();
    buffer->Draw();
}

void PostProcess::UploadPostProcessShader(const char* ver , const char* frg)
{
    if (mshader)
        delete mshader;
    
    const char* VertexShader = Shader::LoadShaderFromFile(ver).c_str();
    const char* FragmentShader = Shader::LoadShaderFromFile(frg).c_str();

    mshader = new Shader(VertexShader,FragmentShader);
}
