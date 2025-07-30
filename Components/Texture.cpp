#include "Texture.h"
#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

Texture::Texture(const char* path)
{
    m_data = stbi_load(path, &mwidth, &mheight, &mchannels, 4);
    if (!m_data) return;
    BindTexture();
}

void SetTextureParameters() {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture::BindTexture() {
    if (!m_data) return;

    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_2D, mId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mwidth, mheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
    SetTextureParameters();

    stbi_image_free(m_data);
    m_data = nullptr;
}

unsigned int Texture::GetTextureID() {
    return mId;
}

void Texture::ReplaceTextureData(const char* path) {
    int newW, newH, newC;
    unsigned char* newData = stbi_load(path, &newW, &newH, &newC, 4);
    if (!newData) return;

    mwidth = newW;
    mheight = newH;
    mchannels = newC;

    glBindTexture(GL_TEXTURE_2D, mId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mwidth, mheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, newData);
    SetTextureParameters();
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(newData);
}

void Texture::ReplaceAsync(std::vector<unsigned char> buffer) {
    std::thread([this, buffer = std::move(buffer)]() {
        int w, h, c;
        unsigned char* data = stbi_load_from_memory(buffer.data(), static_cast<int>(buffer.size()), &w, &h, &c, 4);
        if (!data) return;

        {
            std::lock_guard<std::mutex> lock(updateMutex);
            stagedBuffer.assign(data, data + (w * h * 4));
            stagedWidth = w;
            stagedHeight = h;
            pendingUpload = true;
        }

        stbi_image_free(data);
    }).detach();
}

void Texture::CommitUpload() {
    if (!pendingUpload) return;

    std::lock_guard<std::mutex> lock(updateMutex);
    if (stagedBuffer.empty()) return;

    glBindTexture(GL_TEXTURE_2D, mId);
    
    mwidth = stagedWidth;
    mheight = stagedHeight;
    mchannels = 4;
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA,
        mwidth, mheight, 0,
        GL_RGBA, GL_UNSIGNED_BYTE,
        stagedBuffer.data()
    );

    SetTextureParameters();

    glBindTexture(GL_TEXTURE_2D, 0);

    stagedBuffer.clear();
    pendingUpload = false;
}
