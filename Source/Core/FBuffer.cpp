#include "Core/FBuffer.h"
#include "Core/Window.h"
#include "utility/Logs.h"
#include "glad/glad.h"

void FBuffer::Init()
{
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	glGenTextures(1, &TEX);
	glBindTexture(GL_TEXTURE_2D, TEX);
	
	glTexImage2D(
    GL_TEXTURE_2D,
    0,
    GL_RGBA8,
    getWindowSize().x,
    getWindowSize().y,
    0,
    GL_RGBA,
    GL_UNSIGNED_BYTE,
    nullptr
	);

	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, getWindowSize().x, getWindowSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TEX, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBuffer::CaptureStart(){	
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void FBuffer::CaptureEnd(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0); 
}

uint32& FBuffer::GetFBOTexture(){
	return TEX;
}
uint32& FBuffer::GetFBO(){
	return FBO;
}

