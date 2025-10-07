
#include "World.h"

namespace Krooz2D
{

    class RenderSystem 
    {
        private:
        inline static Ref<World> _currentWorld = nullptr;
        
        public:
        static void SetWorld(World& word);
        void Update(uint32 shader);
    };

}
