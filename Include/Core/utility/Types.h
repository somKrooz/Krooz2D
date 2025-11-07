#pragma once
#include "string"
#include "stdexcept"
#include "typeindex"
#include "memory"
#include "vector"

// Basic Types
using string = std::string;
using cstring = char*;
using uint32 = uint32_t;
using int32 = int32_t;
using runtime_index = std::type_index;
using uint8 = uint8_t;

//Memory Management
template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename... Args>
Ref<T> createRef(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T, typename... Args>
Scope<T> createScope(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}



// Internal Types
struct Ent{
	size_t id;
};

template<typename T>
using Array = std::vector<T>; 


struct RawImage
{
	Array<uint8> data;
	int width;
	uint32 id;
	int height;
	int channel;

	uint8* Get(){return data.data();}
};

struct ShaderDescription{
	string _vertex;
	string _fragment;
};

struct Instance
{
	float x,y;
	float sx,sy;
	int id;
};
