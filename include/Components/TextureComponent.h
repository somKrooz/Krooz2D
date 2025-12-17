#pragma once
#include "Utility/Types.h"
#include "Utility/Maths.h"


struct TextureComponent {
private:
    u64 handle = 0; 
public:
    void ReplaceData(u64 h) {
        handle = h;
    }
    
    u64 GetHandle() const { return handle; }
};
