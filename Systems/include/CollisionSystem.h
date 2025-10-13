#include "Maths.h"
#include "Types.h"
#include "World.h"
#include "TransformComponent.h"

namespace Krooz2D
{	
	class CollisionSystem{
		private:
		World* _currentWorld = nullptr;
		std::vector<Ref<TransformComponent>> _Colliders;
		public:
		CollisionSystem(World& world);
		void Update(float dt);
	};
} 
