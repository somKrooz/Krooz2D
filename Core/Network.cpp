#include "Network.h"
#define CURL_STATICLIB
#include "curl/curl.h"
#include <iostream>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    std::vector<unsigned char>* buffer = static_cast<std::vector<unsigned char>*>(userp);
    buffer->insert(buffer->end(), static_cast<unsigned char*>(contents), static_cast<unsigned char*>(contents) + totalSize);
    return totalSize;
}

NetworkHandler::NetworkHandler() {
    curl_global_init(CURL_GLOBAL_DEFAULT);  
    mHttpHandle = curl_easy_init();
}

bool NetworkHandler::GetRequest(const char* url) {
    if (!mHttpHandle) return false;

    buffer.clear(); 

    curl_easy_setopt(mHttpHandle, CURLOPT_URL, url);
    curl_easy_setopt(mHttpHandle, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(mHttpHandle, CURLOPT_WRITEDATA, &buffer);
    curl_easy_setopt(mHttpHandle, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode res = curl_easy_perform(mHttpHandle);

    if (res != CURLE_OK) {
        std::cerr << "[Error] curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
        return false;
    }

    return true;
}

NetworkHandler::~NetworkHandler() {
    if (mHttpHandle) {
        curl_easy_cleanup(mHttpHandle);
        mHttpHandle = nullptr;
    }
    curl_global_cleanup();
}
