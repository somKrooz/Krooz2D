#pragma once
#include "vector"
#include "utility"
#include <mutex>
#include <atomic>

class Texture {
    private:
    unsigned int mId;
    unsigned char* m_data;
    int mheight , mwidth , mchannels;

    std::mutex updateMutex;
    std::vector<unsigned char> stagedBuffer;
    int stagedWidth = 0, stagedHeight = 0;
    std::atomic<bool> pendingUpload = false;
    
    public:
    Texture(const char* path);
    void ReplaceTextureData(const char* path);
    void BindTexture();
    unsigned int GetTextureID();
    bool SetId(unsigned int id) {return mId = id;}


    void ReplaceAsync(std::vector<unsigned char> buffer);
    void CommitUpload();  

    bool IsPending() const { return pendingUpload; }

   std::pair<int  , int> GetDim(){return {mwidth , mheight};}
};
