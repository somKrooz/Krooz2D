
#include "World.h"
#include "Debug.h"
namespace Krooz2D
{

	class RenderSystem 
	{
		private:
		inline static World* _currentWorld = nullptr;
		Ref<Debug> _debug = nullptr;
		int IsChanged = 0;

		public:
		void SetWorld(World& word);
		void Update(float d);
		~RenderSystem(){_currentWorld = nullptr;}
	};

}
