#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <Maths.h>

struct AABB_RDY {
    Vec2 Position;
    Vec2 Scale;
};

struct TiledImpl; 

class Tiled {
    TiledImpl* impl; 
    std::vector<Vec2> mPositions; 
public:
    Tiled(const char* path);
    ~Tiled();
    void GetElementPosition(const std::string& Name);
    void multScale(int Scale);
    std::vector<Vec2> GetData();
    int GetScale();
    std::vector<Vec2> GetInstantData(std::string name);
    
};
