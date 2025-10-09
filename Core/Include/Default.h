#pragma once
#include "Types.h"

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
		void main() 
		{
			FragColor = texture(u_Texture, TexCoord);
		}
	)";

	inline ShaderDesciption DeafultShader = {defultVertexShader , defaultFragmentShader , false};


} 
