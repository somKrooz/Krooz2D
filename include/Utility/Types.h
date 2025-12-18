#pragma once
#include <vector>
#include <string>
#include <mutex>
#include <queue>
#include <memory>
#include <thread>
#include <future>
#include <stdint.h>
#include <typeindex>
#include <unordered_set>
#include <unordered_map>
#include <condition_variable>

using str = std::string;
using cstr = const char;
using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;
using runtime_index = std::type_index;
using ent = u32;

template <typename T>
using vec = std::vector<T>;

template <typename A, typename B>
using umap = std::unordered_map<A, B>;


template <typename T>
using uset = std::unordered_set<T>;

using thread = std::thread;

template <typename T>
using fut = std::future<T>;

template <typename T>
using scope = std::unique_ptr<T>;

template <typename T, typename... Args>
scope<T> createScope(Args &&...args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using ref = std::shared_ptr<T>;

template <typename T, typename... Args>
ref<T> createRef(Args&&... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

struct ImageResource {
    vec<u8> pixels;
    int width;
    int height;
    u32 id;

    const u8* Get() const
    {
        return pixels.data();
    }

    void Free() {
       	pixels.clear();
		pixels.shrink_to_fit();
    }
	~ImageResource()= default;
};

struct Texture
{
	int width;
	int height;
	int texid;
	u32 entid;
	u64 handle;
};

enum CollisonType
{
	COLLIDABLE,
	COLLISION
};

struct BBox
{
	float minX;
	float maxX;
	float minY;
	float maxY;
};

struct Instance
{
	float x;
	float y;
	float sx;
	float sy;
	float id;

};

struct BindlessInstance
{
	float x;
	float y;
	float sx;
	float sy;
	uint32_t low;   
    uint32_t high; 
};


inline static std::vector<float> quad = {
	0.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f, 1.0f,

	0.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f
};
