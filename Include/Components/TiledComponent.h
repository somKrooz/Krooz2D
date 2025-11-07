#pragma once
#include "utility/Types.h"
#include "Components/TransformComponent.h"
#include "json.hpp"


struct ColData{
	Vec2 Pos;
	Vec2 Scale;
};

using nlohmann::json;

struct TiledComponent
{
	private:
	json JsonCache;

	int _width;
	int _height;
	int _Tilesize;
	std::vector<ColData> _dat;
	
	public:
	TiledComponent(string path);
	void GetElement(string name);
	std::vector<ColData>& GetData();
};
