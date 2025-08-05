#include "Quad.h"
#include "Buffer.h"
#include "Shader.h"
#include "Texture.h"
#include "vector"
#include "Default.hpp"
#include "glad/glad.h"
#include "Engine.h"
#include "StateManger.h"


Quad::Quad(Vec2 pos , Vec2 scale , Texture* tex){
    
    uvScale = Vec2(1,1);
    uvOffset = Vec2(0,0);
    std::vector<float> vertices = {
        0.0f, 0.0f, 0.0f, 0.0f,  
        1.0f, 0.0f, 1.0f, 0.0f, 
        1.0f, 1.0f, 1.0f, 1.0f,  

        0.0f, 0.0f, 0.0f, 0.0f, 
        1.0f, 1.0f, 1.0f, 1.0f,  
        0.0f, 1.0f, 0.0f, 1.0f  
    };

    mBuffer = new Buffer();
    mBuffer->UploadData(vertices , 4 , GL_TRIANGLES);
    mTexture  = tex;
    m_pos = pos;
    m_scale = scale;

    mShader = new Shader(DefaultShader::SolidVertex , DefaultShader::SolidFragment);
    m_model = Mat4::identity();
    m_model = m_model * Mat4::translate(pos);
    m_model = m_model * Mat4::scale(scale);
}

void Quad::SetScaleOffset(Vec2 scale , Vec2 offset){
    uvScale  = scale;
    uvOffset  = offset;
}


Quad::Quad(Vec2 pos, Vec2 scale , unsigned int mid){
    uvScale = Vec2(1,1);
    uvOffset = Vec2(0,0);
    std::vector<float> vertices = {
        0.0f, 0.0f, 0.0f, 0.0f,  
        1.0f, 0.0f, 1.0f, 0.0f, 
        1.0f, 1.0f, 1.0f, 1.0f,  

        0.0f, 0.0f, 0.0f, 0.0f, 
        1.0f, 1.0f, 1.0f, 1.0f,  
        0.0f, 1.0f, 0.0f, 1.0f  
    };

    mBuffer = new Buffer();
    mBuffer->UploadData(vertices , 4 , GL_TRIANGLES);
    mTexture = new Texture("");
    mTexture->SetId(mid);
    m_pos = pos;
    m_scale = scale;

    mShader = new Shader(DefaultShader::SolidVertex , DefaultShader::SolidFragment);
    m_model = Mat4::identity();
    m_model = m_model * Mat4::translate(pos);
    m_model = m_model * Mat4::scale(scale);
}

void Quad::Draw()
{
    mShader->Use();
    mShader->SetMat4("uModel" , m_model);
    mShader->SetMat4("uView",StateManger::GetView());
    mShader->SetMat4("uProjection", Mat4::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f));

    mShader->SetV3("uColor" , Vec3(1,0,0));
    mShader->SetFloat("uAlpha" , 1.0f);
    mShader->SetInt("uTexture", 0);
    mShader->SetFloat("uTime"  , Engine::GetDeltaTime());
    mShader->SetV2("uvScale" , uvScale);
    mShader->SetV2("uvOffset" , uvOffset);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTexture->GetTextureID());

    mBuffer->Bind();
    mBuffer->Draw();
}

void Quad::SetPosition(Vec2 Pos){
    m_pos = Pos;

    m_model = Mat4::identity();
    m_model = m_model * Mat4::translate(m_pos);
    m_model = m_model * Mat4::scale(m_scale);
}


Quad::~Quad(){
    delete mBuffer;
    delete mShader;
}

void Quad::setTex(Texture* tex){
    mTexture = tex;
}
