
#include "RenderSystem.h"
#include "iostream"

namespace Krooz2D
{
    void RenderSystem::SetWorld(World& world){
        _currentWorld = CreateRef<World>(world);
    }

    void RenderSystem::Update(float deltaTime){
        if(_currentWorld->HasComponent<QuadComponent>()){
            std::cout<<"Quads: " << _currentWorld->GetAllComponentsOfType<QuadComponent>().size() << "\n";
        }
    }

    void RenderSystem::SendTextureData(const Texture& texture){
        
    }
}
