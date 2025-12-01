#pragma once
#include "Core/utility/Types.h"
#include "cassert"

enum DrawMode
{
	STATIC = 0x88E4,
	DYNAMIC = 0x88E8,
	STREAM = 0x88E0,
};


struct vertexArray
{
	private:
	uint32 _vao;

	public:
	vertexArray();
	~vertexArray();
	void init();
	void bind();
	void unbind();
	void push(int index , int size, int stride , const void* pointer);
	void divisor(int index);

};

struct vertexBuffer
{
	private:
	uint32 _vbo;

	public:
	vertexBuffer();
	~vertexBuffer();
	
	void init();
	void bind();
	void unbind();

	template<typename T>
	void push(Array<T>& arr , DrawMode mode);
};


struct DrawBuffer
{
	static void DrawInstance(size_t count);
	static void DrawSingle();
};
