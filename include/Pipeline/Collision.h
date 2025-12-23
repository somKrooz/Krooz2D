#pragma once
#include  "Utility/Types.h"
#include  "Utility/Maths.h"
#include  "EngineCore/Scene.h"

struct NativeCollision
{
    u32 _id;
    Vec2 _Position;
    Vec2 _Scale;
};

class Collision
{
    private:
        vec<NativeCollision> CollisionData;
        vec<NativeCollision> Dynamic;
        vec<NativeCollision> Static;
        Scene *CurrentScene = nullptr;
        inline static bool hasCollided = false;

    public:
        Collision(Scene& scene);
        void Update(float delta);
        static bool GetCollisionEvent();
};