#include "External/OpenglBind.h"
#include "EngineCore/Buffer.h"
vertexArray::vertexArray()
{
	glGenVertexArrays(1, &varray);
}

void vertexArray::Bind()
{
	glBindVertexArray(varray);
}

void vertexArray::unBind()
{
	glBindVertexArray(0);
}

void vertexArray::Push(int index, int size, int stride, const void* pointer)
{
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
	glEnableVertexAttribArray(index);
}

void vertexArray::Divisor(int index)
{
	glVertexAttribDivisor(index, 1);
}

vertexArray::~vertexArray()
{
	glDeleteVertexArrays(1, &varray);
}

vertexBuffer::vertexBuffer()
{
	glGenBuffers(1, &vobject);
}

void vertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vobject);
}

void vertexBuffer::unBind()
{
	glBindBuffer(0, vobject);
}

void vertexBuffer::Push(vec<float>& data, usageDraw usage)
{
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), usage);
}

void vertexBuffer::Push(vec<Instance>& data, usageDraw usage)
{
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Instance), data.data(), usage);
}

vertexBuffer::~vertexBuffer()
{
	glDeleteBuffers(1, &vobject);
}

void BufferRenderCall::DrawDyamic(size_t count) {
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, count);
}

void BufferRenderCall::DrawStatic() {
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
