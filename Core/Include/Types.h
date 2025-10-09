#pragma once

#include "vector"
#include "Maths.h"
#include "typeindex"
#include <stdexcept>
#include "cmath"
#include "string"

using uint32 = uint32_t; 
using uint8 = uint8_t;
using runtime_index = std::type_index; 

using string = std::string;
using cname = char*;

struct Ent{
	uint32 _ID;
};

struct TextureDescription{
	std::vector<uint8> _pixels;
	uint32 _id = 0;
	int _width = 128;
	int _height = 128;
	int _channels = 4;
};


struct ShaderDesciption
{
	string _vertex;
	string _fragment;
	bool _isPath = false;
};

#include "memory"
template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T , typename... Args>
Ref<T> CreateRef(Args&&... args){
	return std::make_shared<T>(std::forward<Args>(args)...);
}
