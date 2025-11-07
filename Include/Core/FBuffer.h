#pragma once
#include "utility/Types.h"

struct FBuffer
{
	static inline uint32 FBO = -1;
    static inline uint32 TEX = -1;

	static void Init(); 
	static void CaptureStart();
	static void CaptureEnd();

	static uint32& GetFBOTexture();
	static  uint32& GetFBO();
};

