#pragma once

#include "Maths.h"

class Buffer; 
class Shader;
class Texture;

class Quad {
private:
    Mat4 m_model = Mat4::identity();
    Vec2 m_pos;
    Vec2 m_scale;
    Vec2 uvScale , uvOffset;
    Buffer* mBuffer = nullptr;
    Shader* mShader = nullptr;
    Texture* mTexture = nullptr;

public:
    Quad(Vec2 pos, Vec2 scale , Texture* tex);
    Quad(Vec2 pos, Vec2 scale , unsigned int mid);
    void Draw();
    void SetPosition(Vec2 Pos);
    void SetScale(Vec2 Scale){m_scale  = Scale;}
    void setTex(Texture* tex);
    void SetScaleOffset(Vec2 scale , Vec2 offset);
    
    Vec2 GetPos(){return m_pos;}
    Vec2 GetScale(){return m_scale;}

    ~Quad();
};
