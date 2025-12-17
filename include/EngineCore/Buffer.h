#pragma once
#include "Utility/Types.h"

enum usageDraw
{
	staticDraw = 0x88E4,
	dynamicDraw = 0x88E8
};

class vertexBuffer
{
private:
	u32 vobject;

public:
	vertexBuffer();
	void Bind();
	void unBind();
	void Push(vec<float>& data, usageDraw usage);
	void Push(vec<Instance>& data, usageDraw usage);
	void Push(vec<BindlessInstance> &data, usageDraw usage);
	~vertexBuffer();
};

class vertexArray
{
private:
	u32 varray;

public:
	vertexArray();
	void Bind();
	void unBind();
	void Push(int index, int size, int stride, const void* pointer);
	void PushInt(int index, int size, int stride, const void *pointer);
	void Divisor(int index);
	~vertexArray();
};

struct BufferRenderCall
{
	static void DrawStatic();
	static void DrawDyamic(size_t count);
};
