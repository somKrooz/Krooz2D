#include "glad/glad.h"
#include "Core/Buffer.h"

/// @brief  Vertex Array
vertexArray::vertexArray(){
	glGenVertexArrays(1, &_vao);
}

void vertexArray::init(){
	glGenVertexArrays(1, &_vao);

}
vertexArray::~vertexArray(){
	glDeleteVertexArrays(1, &_vao);
}
void vertexArray::bind(){
	glBindVertexArray(_vao);
}

void vertexArray::unbind(){
	glBindVertexArray(0);
}

void vertexArray::push(int index , int size, int stride , const void* pointer){
	glVertexAttribPointer(index , size , GL_FLOAT , GL_FALSE, stride , pointer);
	glEnableVertexAttribArray(index);
}

void vertexArray::divisor(int index){
	glVertexAttribDivisor(index , 1);
}



/// @brief Vertex Buffer 
vertexBuffer::vertexBuffer(){
	glGenBuffers(1, &_vbo);
}
vertexBuffer::~vertexBuffer(){
	glDeleteBuffers(1,&_vbo);
}
void vertexBuffer::init(){
	glGenBuffers(1, &_vbo);

}

void vertexBuffer::bind(){
	glBindBuffer(GL_ARRAY_BUFFER , _vbo);
}

void vertexBuffer::unbind(){
	glBindBuffer(GL_ARRAY_BUFFER , 0);
}

template<typename T>
void vertexBuffer::push(Array<T>& arr , DrawMode mode){
	assert(arr.size() > 0 && "Vector size must be greater than 0");
	glBufferData(GL_ARRAY_BUFFER , arr.size() * sizeof(T), arr.data() , mode);
}

template void vertexBuffer::push<float>(Array<float>&, DrawMode);
template void vertexBuffer::push<Instance>(Array<Instance>&, DrawMode);



/// @brief Buffer Draw Calls
void DrawBuffer::DrawInstance(size_t count){
	glDrawArraysInstanced(GL_TRIANGLES , 0 , 6 , count);
}

void DrawBuffer::DrawSingle(){
	glDrawArrays(GL_TRIANGLES , 0 , 6);
}
