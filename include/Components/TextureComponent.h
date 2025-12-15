#pragma once
#include "Utility/Types.h"
#include "Utility/Maths.h"


struct TextureComponent {
private:
    u64 handle = 0;
	u32 Id = 0; 
public:
    void ReplaceData(u64 h) {
        handle = h;
    }
	void setId(u32 id) {
		this->Id = id;
	}
    
    u64 GetHandle() const { return handle; }
	u32 GetId() const {return Id; }
};
