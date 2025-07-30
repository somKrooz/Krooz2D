#pragma once
#include "vector"

class NetworkHandler{
    private:
    void* mHttpHandle;
    std::vector<unsigned char> buffer;
    
    public:
    NetworkHandler();
    ~NetworkHandler();
    bool GetRequest(const char* url);
    std::vector<unsigned char>& GetBuffer(){ return buffer; }
};
