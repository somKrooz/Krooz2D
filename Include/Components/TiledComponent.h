#pragma once
#include "utility/Types.h"
#include "Components/TransformComponent.h"

struct JsonDataImp;
struct ColData
{
	Vec2 Pos;
	Vec2 Scale;
};

struct TiledComponent
{
	private:
	static inline JsonDataImp* Json = nullptr;
	static inline Array<ColData> _dat = {};
	
	public:
	static void LoadTiled(string path);
	static void GetElement(string name);
	static Array<ColData>& GetData();
	static Array<ColData> GetInstanceData(string name);
};
