#pragma once
#include "utility/Types.h"

namespace Defaults
{
	inline string vertexshader = R"(
	#version 330 core
	layout(location = 0) in vec2 mPosition;
	layout(location = 1) in vec2 mUV;
	layout(location = 2) in vec2 aInstancePosition;
	layout(location = 3) in vec2 aInstanceScale;
	layout(location = 4) in int aTextureID;

	uniform mat4 uProjection;
	uniform mat4 uView;

	out vec2 vertexUV;
	flat out int TextureID;

	void main()
	{
		vec2 worldPos = (mPosition * aInstanceScale) + aInstancePosition;
		gl_Position = uProjection * uView * vec4(worldPos, 0.0, 1.0);

		TextureID = aTextureID;
		vertexUV = mUV;
	}

	)"; 

	inline string fragmentshader = R"(
	#version 330 core
	out vec4 FragColor;
	in vec2 vertexUV;
	flat in int TextureID;

	uniform sampler2D tex[30];

	void main()
	{
		FragColor = texture(tex[TextureID], vertexUV);
	}

	)";

	inline string PostProcessVertex = R"(
	#version 330 core
	layout (location = 0) in vec2 aPos;
	layout (location = 1) in vec2 aTexCoord;

	out vec2 TexCoord;

	void main() {
		TexCoord = aTexCoord;
		gl_Position = vec4(aPos, 0.0, 1.0);
	}

	)";

	inline string PostProcessFrag = R"(
	#version 330 core
	out vec4 FragColor;

	in vec2 TexCoord;
	uniform sampler2D screenTexture;
	uniform float uTime; // pass time for subtle flicker

	// Helper: vignette
	float vignette(vec2 uv) {
		float r = length(uv - 0.5);
		return smoothstep(0.8, 0.4, r);
	}

	void main()
	{
		vec2 uv = TexCoord;

		// --- CRT Curvature ---
		uv = uv * 2.0 - 1.0;         // to -1..1 range
		uv.x *= 1.0 + 0.1 * pow(uv.y, 2.0);
		uv.y *= 1.0 + 0.1 * pow(uv.x, 2.0);
		uv = uv * 0.5 + 0.5;         // back to 0..1 range

		// --- RGB Color Offsets ---
		float offset = 0.002;
		float flicker = 0.98 + 0.02 * sin(uTime * 50.0);
		vec3 col;
		col.r = texture(screenTexture, uv + vec2(offset, 0.0)).r;
		col.g = texture(screenTexture, uv).g;
		col.b = texture(screenTexture, uv - vec2(offset, 0.0)).b;

		// --- Scanlines ---
		float scan = sin(uv.y * 720.0) * 0.04;  // fine lines
		col -= scan;

		// --- Vignette ---
		col *= vignette(uv);

		// --- Slight flicker ---
		col *= flicker;

		FragColor = vec4(col, 1.0);
	}
	)";




	inline ShaderDescription DefaultShader = {vertexshader , fragmentshader};
	inline ShaderDescription PostShader = {PostProcessVertex , PostProcessFrag};
}
