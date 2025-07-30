#pragma once

using cstr = const char*;
namespace DefaultShader {
    inline constexpr cstr SolidVertex =  R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;

uniform vec2 uvScale;
uniform vec2 uvOffset;

uniform mat4 uProjection;
uniform mat4 uModel;
uniform mat4 uView;

out vec2 vUV;

void main() {
    vUV = aUV * uvScale + uvOffset; 
    gl_Position = uProjection * uView * uModel * vec4(aPos, 0.0, 1.0);
}
    )";

inline constexpr cstr SolidFragment = R"(
#version 330 core
in vec2 vUV;
out vec4 FragColor;

uniform vec3 uColor;
uniform float uAlpha;
uniform sampler2D uTexture;
uniform float uTime;

void main() {
    vec2 uv = vUV;
    
    // Pixelation effect
    float pixelSize = 512.0; // High resolution pixelation
    vec2 pixelatedUV = floor(uv * pixelSize) / pixelSize;
    
    // Sample the texture with pixelated coordinates - GET THE FULL RGBA!
    vec4 texColor = texture(uTexture, pixelatedUV); // Changed from .rgb to full vec4
    
    // Option 1: Keep original PNG colors with transparency
    FragColor = vec4(texColor.rgb, texColor.a * uAlpha);
    
    // Option 2: If you want to apply color tinting but keep transparency:
    // FragColor = vec4(texColor.rgb * uColor, texColor.a * uAlpha);
    
    // Option 3: Discard fully transparent pixels (optional optimization):
    // if(texColor.a < 0.01) discard;
    // FragColor = vec4(texColor.rgb * uColor, texColor.a * uAlpha);
}
)";
}
