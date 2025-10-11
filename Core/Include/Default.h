#pragma once
#include "Types.h"


namespace Krooz2D::Color
{
	constexpr inline Vec3 RED {1.0f, 0.0f, 0.0f};
	constexpr inline Vec3 DARKGREY {0.4f, 0.4f, 0.4f};
	constexpr inline Vec3 KROOZ {0.1f, 0.1f, 0.1f};
}

namespace Krooz2D::Defaults
{
	inline string defultVertexShader = R"(
		#version 330 core
		layout(location = 0) in vec2 aPos;
		layout(location = 1) in vec2 aTex;
		uniform mat4 u_Projection;
		uniform mat4 u_View;
		uniform mat4 u_Model;
		out vec2 TexCoord;

		void main() 
		{
			TexCoord = aTex;
			gl_Position = u_Projection * u_View * u_Model * vec4(aPos, 0.0, 1.0);
		}
	)";

	inline string defaultFragmentShader = R"(
		#version 330 core
		in vec2 TexCoord; 
		out vec4 FragColor;
		uniform sampler2D u_Texture;
		uniform float u_alpha;
		void main() 
		{
			vec4 texColor = texture(u_Texture, TexCoord); 
			FragColor = vec4(texColor.rgb, texColor.a * u_alpha); 
		}
	)";

	inline ShaderDesciption DeafultShader = {defultVertexShader , defaultFragmentShader , false};


} 
