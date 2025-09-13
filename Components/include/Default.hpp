#pragma once

using cstr = const char*;
namespace DefaultShader {
    inline constexpr cstr SolidVertex = R"(
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
    float pixelSize = 512.0;
    vec2 pixelatedUV = floor(uv * pixelSize) / pixelSize;
    
    vec4 texColor = texture(uTexture, pixelatedUV); 
    FragColor = vec4(texColor.rgb, texColor.a * uAlpha);
}
    )";


inline constexpr cstr PostVert = R"(
#version 330 core
layout (location = 0) in vec2 aPos; // quad positions in [0,1] space
layout (location = 1) in vec2 aUV;  // texture UVs

out vec2 vUV;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main()
{
    vUV = vec2(aUV.x, 1.0 - aUV.y);
    gl_Position = uProjection * uView * uModel * vec4(aPos, 0.0, 1.0);
}
)";
inline constexpr cstr PostFrag = R"(
#version 330 core
in vec2 vUV;
out vec4 FragColor;

uniform sampler2D uSceneTex;
uniform float uTime; 

void main()
{
    // --- Chromatic aberration ---
    float offset = 0.0025; // how much to shift colors
    vec2 uv = vUV;

    float r = texture(uSceneTex, uv + vec2(offset, 0.0)).r;
    float g = texture(uSceneTex, uv).g;
    float b = texture(uSceneTex, uv - vec2(offset, 0.0)).b;
    vec3 color = vec3(r, g, b);

    // --- Vignette ---
    vec2 pos = uv - 0.5; 
    float dist = length(pos) * 1.4;
    float vignette = smoothstep(1.0, 0.5, dist);
    color *= vignette;

    // --- Subtle wave distortion for fun ---
    uv.x += 0.005 * sin(uv.y * 20.0 + uTime * 2.0);
    uv.y += 0.005 * cos(uv.x * 20.0 + uTime * 2.0);

    vec3 finalColor = mix(color, texture(uSceneTex, uv).rgb, 0.2);

    FragColor = vec4(finalColor, 1.0);
}
)";

}

