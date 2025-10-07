#include "Systems.h"
#include "QuadComponent.h"
#include "World.h"

namespace Krooz2D
{

    class RenderSystem : public Systems 
    {
        private:
        inline static Ref<World> _currentWorld = nullptr;
        
        public:
        static void SetWorld(World& word);
        void SendTextureData(const Texture& texture);
        void Update(float deltaTime) override;
    };

}
