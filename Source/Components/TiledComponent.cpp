#include "Components/TiledComponent.h"
#include "utility/Logs.h"
#include "fstream"
#include "json.hpp"


struct JsonDataImp {
    nlohmann::json JsonCache;
	int _width;
	int _height;
	int _Tilesize;
};

void TiledComponent::LoadTiled(string path)
{
	if(Json == nullptr) Json = new JsonDataImp();
	
	std::ifstream file(path);
	if(!file){
		Error("Path {} is not valid..." , path);
		exit(0);
	}
	file >> Json->JsonCache;

	if (Json->JsonCache.empty()){
		Error("Unable to Process Json...");
	}

	Json->_width= Json->JsonCache["width"];
	Json->_height = Json->JsonCache["height"];
	Json->_Tilesize = Json->JsonCache["tilewidth"];


	GetElement("Collision");

}

void TiledComponent::GetElement(string name){
	for(auto& el : Json->JsonCache["layers"]){
		if(el["name"] == name){
			const auto& Data = el["data"];
			 for (int y = 0; y < Json->_height; y++)
			{
				for (int x = 0; x < Json->_width; x++)
				{
					int index = y * Json->_width + x;
					auto tileid = Data[index];

					if(tileid != 0){
						Vec2 position(x * Json->_Tilesize, y * Json->_Tilesize);
						Vec2 Scale(Json->_Tilesize , Json->_Tilesize);
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



Array<ColData> TiledComponent::GetInstanceData(string name)
{
	Array<ColData> local;
	for(auto& el : Json->JsonCache["layers"]){
		if(el["name"] == name){
			const auto& Data = el["data"];
			 for (int y = 0; y < Json->_height; y++)
			{
				for (int x = 0; x < Json->_width; x++)
				{
					int index = y * Json->_width + x;
					auto tileid = Data[index];

					if(tileid != 0){
						Vec2 position(x * Json->_Tilesize, y * Json->_Tilesize);
						Vec2 Scale(Json->_Tilesize , Json->_Tilesize);
						local.push_back({position , Scale});
					}
				}
			}
			
		}
	}

	return local;
}
