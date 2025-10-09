#pragma once

#include "Types.h"

struct bufferDescription
{
	uint32 _VAO = 0;
	uint32 _VBO = 0;
	uint32 _insVBO = 0;
};



namespace Krooz2D
{
	class QuadBuffer
	{
		private:
		bufferDescription desciption;

		public:
		QuadBuffer();
		~QuadBuffer();
		void InitStaticQuad(bool hasTexture);
		void Draw();
	};
} 
