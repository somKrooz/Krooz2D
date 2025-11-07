#include "glad/glad.h"
#include "Core/Buffer.h"

Buffer::Buffer()
{
	glGenBuffers(1,&_VBO);
	glGenBuffers(1,&_INS);
	glGenVertexArrays(1,&_VAO);
}
Buffer::~Buffer()
{
	glDeleteBuffers(1,&_VBO);
	glDeleteBuffers(1,&_INS);
	glDeleteVertexArrays(1,&_VAO);
}

void Buffer::InitStatic()
{
	glBindVertexArray(_VAO);

	Array<float> vertex = {
		0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f,

		0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f
	};
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(float), vertex.data(), GL_STATIC_DRAW);

	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glBindVertexArray(0);   
}



void Buffer::InitInstance(Array<Instance>& instance)
{
	
    count = instance.size();
    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _INS);
    glBufferData(GL_ARRAY_BUFFER, instance.size() * sizeof(Instance), instance.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Instance), (void*)0);
    glEnableVertexAttribArray(2);
    glVertexAttribDivisor(2, 1); 

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE,sizeof(Instance), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(3);
    glVertexAttribDivisor(3, 1);
	
	glVertexAttribIPointer(4, 1, GL_INT, sizeof(Instance), (void*)offsetof(Instance, id));
	glEnableVertexAttribArray(4);
	glVertexAttribDivisor(4, 1);

    glBindVertexArray(0);
}

void Buffer::UpdateInstance(Array<Instance>& inst) {
    glBindBuffer(GL_ARRAY_BUFFER, _INS);
    glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(Instance), inst.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffer::Draw()
{
    glBindVertexArray(_VAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, count);
}

int Buffer::GetSize(){
	return count;
}
