
#include "World.h"
#include "Debug.h"
namespace Krooz2D
{

	class RenderSystem 
	{
		private:
		inline static Ref<World> _currentWorld = nullptr;
		inline static Ref<Debug> _debug = nullptr;
		int IsChanged = 0;

		public:
		static void SetWorld(World& word);
		void Update(float d);
	};

}
