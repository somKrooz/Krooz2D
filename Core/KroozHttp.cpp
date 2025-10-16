#include "KroozHttp.h"
#include "winrt/Windows.Foundation.h"
#include <winrt/Windows.Web.Http.h>
#include <winrt/Windows.Storage.Streams.h>
#include <iostream>
#include <thread>

using namespace winrt;
using namespace Windows::Web::Http;
using namespace Windows::Foundation;

namespace Krooz2D
{
	void KroozHttp::SendHttpGetRequest(std::string Url)
	{
		std::thread([Url, this]()
		{
			winrt::init_apartment();
			
			Windows::Web::Http::HttpClient client;
			Windows::Foundation::Uri uri(winrt::to_hstring(Url));
			auto response = client.GetAsync(uri).get();

			if (response.IsSuccessStatusCode())
			{
				auto content = response.Content().ReadAsStringAsync().get();
				std::string utf8 = winrt::to_string(content);
	
				std::lock_guard<std::mutex> lock(g_mutex);
				this->g_httpResponse = utf8;
			}
		
		}).detach(); 
	}

	std::optional<std::string> KroozHttp::Get() {
		std::lock_guard<std::mutex> lock(g_mutex);
		return g_httpResponse;
	}
	
	void KroozHttp::Clear() {
		std::lock_guard<std::mutex> lock(g_mutex);
		g_httpResponse = std::nullopt;
	}
}
