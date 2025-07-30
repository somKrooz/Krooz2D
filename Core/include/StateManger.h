#pragma once
#include "Maths.h"

struct StateManger
{
    inline static Mat4  uView = Mat4::identity();
    static void SetView(Mat4 view){
        uView = view;
    }  
    static Mat4 GetView(){
        return uView;
    }
};
