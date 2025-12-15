#pragma once
#include "Utility/Types.h"


namespace LegacyDefault
{
    inline str vertexshader = R"(
	#version 460 core

	layout(location = 0) in vec2 mPosition;
	layout(location = 1) in vec2 mUV;
	layout(location = 2) in vec2 aInstancePosition;
	layout(location = 3) in vec2 aInstanceScale;
	layout(location = 4) in float ahandle;

	uniform mat4 uProjection;
	uniform mat4 uView;

	out vec2 vertexUV;
	flat out int texHandle;

	void main() {
		vec2 worldPos = (mPosition * aInstanceScale) + aInstancePosition;
		gl_Position = uProjection * uView * vec4(worldPos, 0.0, 1.0);
		texHandle = int(ahandle);
		vertexUV = mUV;
	}
)";

    inline str fragmentshader = R"(
	#version 460 core
	out vec4 FragColor;

	in vec2 vertexUV;
	flat in int texHandle;

	uniform sampler2D tex[30];

	void main() {
		FragColor = texture(tex[texHandle], vertexUV);
	}

)";
}


namespace Default {
	inline str vertexshader = R"(
		#version 460 core
		#extension GL_ARB_bindless_texture : require

		layout(location = 0) in vec2 mPosition;
		layout(location = 1) in vec2 mUV;
		layout(location = 2) in vec2 aInstancePosition;
		layout(location = 3) in vec2 aInstanceScale;
		layout(location = 4) in uint aHandleLow;
		layout(location = 5) in uint aHandleHigh;
		
		layout(location = 6) in vec2  uvoffset;
		layout(location = 7) in vec2  uvscale;
		
		uniform mat4 uProjection;
		uniform mat4 uView;

		out vec2 vertexUV;
		flat out uvec2 texHandle;

		void main() {
			vec2 worldPos = (mPosition * aInstanceScale) + aInstancePosition;
			gl_Position = uProjection * uView * vec4(worldPos, 0.0, 1.0);
			texHandle = uvec2(aHandleLow, aHandleHigh);

			vertexUV = (mUV* uvscale) + uvoffset;
		}
	)";

	inline str fragmentshader = R"(
		#version 460 core
		#extension GL_ARB_bindless_texture : require

		out vec4 FragColor;
		in vec2 vertexUV;
		
		flat in uvec2 texHandle; 
		void main() {
			sampler2D tex = sampler2D(texHandle);
			FragColor = texture(tex, vertexUV);
		}
	)";

}
