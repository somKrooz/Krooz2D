#include "EngineCore/TextureManager.h"
#include "External/OpenglBind.h"
#include "EngineCore/Shader.h"

static int index = 0;
int TextureManager::CreateTextureHandle(ImageResource *image) {
    u32 id = 0;
    int currentIndex = index;
    glGenTextures(1, &id);

    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, id);
    
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 
                 image->width, image->height, 
                 0, GL_RGBA, GL_UNSIGNED_BYTE, 
    image->Get());
    
    image->id = id;
    
    std::string tex = "tex[" + std::to_string(index) + "]";
    int location = glGetUniformLocation(Shader::Get(), tex.c_str());
    glUniform1i(location, currentIndex);
    
    index++;
    return currentIndex;
}

void TextureManager::Push(u32 Ent , u64 Handle)
{
    Ent_Texture_Handle[Ent] = Handle;
}

u64 TextureManager::CreateBindLess(ImageResource* image)
{
    if (!image || image->pixels.empty()) {
        printf("ERROR: Invalid image data\n");
        return 0;
    }
    
    
    u32 id = 0;
    glCreateTextures(GL_TEXTURE_2D, 1, &id);
    
    glTextureStorage2D(id, 1, GL_RGBA8, image->width, image->height);
    glTextureSubImage2D(id, 0, 0, 0, 
                        image->width, image->height, 
                        GL_RGBA, GL_UNSIGNED_BYTE, 
                        image->Get());
    
    glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    u64 handle = glGetTextureHandleARB(id);
    image->Free();

    glMakeTextureHandleResidentARB(handle);
        
    image->id = id;
    return handle;
}

u64 TextureManager::Get(u32 id)
{
    auto it = Ent_Texture_Handle.find(id);
    if(it != Ent_Texture_Handle.end()){
        return  it->second;
    }

    return 0;
}
size_t TextureManager::GetSize()
{
    return Ent_Texture_Handle.size();
}



