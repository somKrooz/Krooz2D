#pragma once
#include "Utility/Types.h"


struct CollisionComponent
{
    private:
        CollisonType _type;
    public:
    CollisionComponent(CollisonType type)
    {
        _type = type;
    }
    CollisonType& Get()
    {
        return _type;
    }
};