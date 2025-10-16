#include "Types.h"
#include <mutex>
#include <optional>

namespace Krooz2D
{
	class KroozHttp {
	private:
		std::optional<std::string> g_httpResponse;
		std::mutex g_mutex;  
		
	public:
		void SendHttpGetRequest(string url);
		std::optional<std::string> Get(); 
		void Clear();
	};	
}
