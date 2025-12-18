#pragma once
#include  "Utility/Types.h"
#include  "Utility/Maths.h"
#include  "EngineCore/Scene.h"

struct NativeCollision
{
    Vec2 _Position;
    Vec2 _Scale;
};

class Collision
{
    private:
        vec<NativeCollision> CollisionData;
        vec<NativeCollision> Static;
        Scene *CurrentScene = nullptr;

    public:
        Collision(Scene& scene);
        void Update(float delta);
};