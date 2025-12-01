#pragma once

#include "Core/World.h"
#include "Core/Buffer.h"
#include "utility/Types.h"
#include "Core/Shader.h"
#include "Systems/System.h"


struct GPU_LAYOUT{
	Scope<vertexArray> array;
	Scope<vertexBuffer> buf;
	Scope<vertexBuffer> ins;
	
	GPU_LAYOUT() = default; 

};


class RenderSystem : public System
{
	private:
	Scope<GPU_LAYOUT> buffer = nullptr;
	Scope<Shader> globalShader = nullptr;

	Array<Instance> ObjectPool;	

	static inline bool _isPostProcess = false;	
	
	public:
	RenderSystem();
	void BuildInstanceData();
	void Update(float dt) override;
	static void EnablePostProcess(bool val);
};
