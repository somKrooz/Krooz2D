#pragma once
#include "utility/Types.h"

class Buffer
{
	private:
	uint32 _VAO;
	uint32 _VBO;
	uint32 _INS;
	Instance* _mappedPtr = nullptr;
	size_t _instanceSize = 0;
	size_t maxCapacity;
	static inline size_t count = 0;

	public:
	Buffer();
	~Buffer();
	void InitStatic();
	void UpdateInstance(Array<Instance>& inst);
	void InitInstance(Array<Instance>& instance);
	static int GetSize();
	void Draw();
};
