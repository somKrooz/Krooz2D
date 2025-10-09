
#include "World.h"
#include "Debug.h"
namespace Krooz2D
{

	class RenderSystem 
	{
		private:
		inline static Ref<World> _currentWorld = nullptr;
		inline static Ref<Debug> _debug = nullptr;
		
		public:
		static void SetWorld(World& word);
		void Update(uint32 shader);
	};

}
