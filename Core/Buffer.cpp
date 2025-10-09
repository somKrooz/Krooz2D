#include "Buffer.h"
#include "glad/glad.h"

namespace Krooz2D
{
	QuadBuffer::QuadBuffer()
	{
		glGenBuffers(1 , &desciption._VBO);
		glGenVertexArrays(1 , &desciption._VAO);
		glGenBuffers(1, &desciption._insVBO);
	}

	QuadBuffer::~QuadBuffer()
	{
		glDeleteBuffers(1, &desciption._VBO);
		glDeleteBuffers(1, &desciption._insVBO);
		glDeleteVertexArrays(1, &desciption._VAO);
	}

	void QuadBuffer::InitStaticQuad(bool hasTexture)
	{
		glBindVertexArray(desciption._VAO);

		float quadVertices[] = {
				0.0f, 0.0f, 0.0f, 0.0f,
				1.0f, 0.0f, 1.0f, 0.0f,
				1.0f, 1.0f, 1.0f, 1.0f,

				0.0f, 0.0f, 0.0f, 0.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0.0f, 1.0f, 0.0f, 1.0f
		};

		glBindBuffer(GL_ARRAY_BUFFER, desciption._VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		
		if(hasTexture)
		{
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
				glEnableVertexAttribArray(1);
		}
		
		glBindVertexArray(0);   
	}
	
	void QuadBuffer::Draw()
	{
		glBindVertexArray(desciption._VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

} 
