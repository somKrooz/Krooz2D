#include "Tiled.h"
#include <json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

struct TiledImpl {
    json mjson;
    int mwid, mhid, mtsize;
    std::vector<AABB_RDY> collection;
    std::unordered_map<std::string, std::vector<AABB_RDY>> CollisionData;

    void loadFromFile(const char* path) {
        std::ifstream file(path);
        file >> mjson;

        if (mjson.empty())
            std::cerr << "TiledImpl: Failed to load JSON from file\n";

        mwid = mjson["width"];
        mhid = mjson["height"];
        mtsize = mjson["tilewidth"];
    }
    void Mult(int scale){
        mtsize *= scale;
    }

    void getElementPosition(const std::string& Name) {
        collection.clear();
        for (const auto& el : mjson["layers"]) {
            if (el["name"] == Name) {
                const auto& data = el["data"];
                for (int y = 0; y < mhid; y++) {
                    for (int x = 0; x < mwid; x++) {
                        int index = y * mwid + x;
                        int tileID = data[index];
                        if (tileID != 0) {
                            Vec2 position(x * mtsize, y * mtsize);
                            Vec2 scale(mtsize, mtsize);
                            collection.push_back({position, scale});
                        }
                    }
                }
                CollisionData[Name] = collection;
                return;
            }
        }
    }

    std::unordered_map<std::string, std::vector<AABB_RDY>> GetData(){
        return CollisionData;
    }
};


Tiled::Tiled(const char* path) {
    impl = new TiledImpl();
    impl->loadFromFile(path);
}

Tiled::~Tiled() {
    delete impl;
}

void Tiled::GetElementPosition(const std::string& Name) {
    impl->getElementPosition(Name);
}

std::vector<Vec2> Tiled::GetData(){
    for(auto &layer : impl->CollisionData){
        for (auto &aabb : layer.second) {
            mPositions.push_back({ Vec2(aabb.Position.x, aabb.Position.y) });
        }
    }
    return mPositions;
}
void Tiled::multScale(int scale){
    impl->Mult(scale);
}
int Tiled::GetScale(){
    return impl->mtsize;
}
