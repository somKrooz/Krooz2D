#pragma once

#include "Buffer.h"
#include "Shader.h"
#include "Maths.h"

struct ColorTarget;
class PostProcess
{
    private:
    Buffer* buffer = nullptr;
    inline static Shader* mshader = nullptr;
    Mat4 model = Mat4::identity();

    public:
    PostProcess();
    void Draw(unsigned int mtex);

    static void UploadPostProcessShader(const char* ver , const char* frg);
};
