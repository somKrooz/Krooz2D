#include "Components/TiledComponent.h"
#include "utility/Logs.h"
#include "fstream"

TiledComponent::TiledComponent(string path)
{
	std::ifstream file(path);
	file >> JsonCache;

	if (JsonCache.empty())
		Error("Unable to Process Json...");

	_width= JsonCache["width"];
	_height = JsonCache["height"];
	_Tilesize = JsonCache["tilewidth"];

	Log("Width: {}" , _width);
	Log("Height: {}" , _height);
	Log("TileSize: {}" , _Tilesize);

	GetElement("Tile Layer 1");

}

void TiledComponent::GetElement(string name){
	for(auto& el : JsonCache["layers"]){
		if(el["name"] == name){
			const auto& Data = el["data"];
			 for (int y = 0; y < _height; y++)
			{
				for (int x = 0; x < _width; x++)
				{
					int index = y * _width + x;
					auto tileid = Data[index];

					if(tileid != 0){
						Vec2 position(x * _Tilesize, y * _Tilesize);
						Vec2 Scale(_Tilesize , _Tilesize);
						_dat.push_back({position , Scale});
					}
				}
			}
			
		}
	}
}

std::vector<ColData>& TiledComponent::GetData()
{
	return _dat;
}
