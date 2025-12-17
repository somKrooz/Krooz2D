#pragma once
#include "EngineCore/Scene.h"
#include "EngineCore/Buffer.h"
#include "Utility/Types.h"
#include "EngineCore/Shader.h"

struct GpuLayout
{
	vertexArray vao;
	vertexBuffer vbo;
	vertexBuffer ins;
	GpuLayout() : vao(), vbo(), ins() {}
};

class Renderer
{
private:
	Scene* CurrentWorld;
	vec<Instance> Objects;
	vec<BindlessInstance> BindlessObjects;
	scope<GpuLayout> buffer = nullptr;

public:
	Renderer(Scene& scene);
	void Update(Shader* shader, float delta);
	void BuildMeshData();
};
