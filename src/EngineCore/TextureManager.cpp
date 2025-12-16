#include "EngineCore/TextureManager.h"
#include "External/OpenglBind.h"
#include "EngineCore/Shader.h"

int TextureManager::CreateTextureHandle(ImageResource *image) {
    static int index = 0;
    u32 id = 0;
    glGenTextures(1, &id);
    index++;

    glTexImage2D(GL_TEXTURE_2D , 0,GL_RGBA , image->width , image->height , 0,GL_RGBA ,GL_UNSIGNED_BYTE , image->Get());

    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE0, id);

    std::string tex_index = "tex[" + std::to_string(index) + "]";
    int location = glGetUniformLocation(Shader::Get(), tex_index.c_str());
    glUniform1i(location, index);

    return index;
}