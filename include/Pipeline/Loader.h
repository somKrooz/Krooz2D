#pragma once
#include "Utility/Types.h"

struct ImageLoader
{
private:
	scope<ImageResource> image;

public:
	ImageLoader(str path);
	ImageLoader(vec<u8>& data);

	void LoadFromPath(str path, ImageResource* img);
	void LoadFromMemory(vec<u8>& data, ImageResource* img);

	scope<ImageResource> Get();
};

struct Job {
	std::string path;
	u32 Ent;
	scope<ImageResource> image;
};

struct FinishedJob{
	scope<ImageResource> image;
	u32 Ent;
};

struct ImageDimension 
{
	int _width;
	int _height;
};

struct AsyncTexture 
{
	private:
	inline static std::thread worker;
	inline static std::mutex mtx;
	inline static std::queue<FinishedJob> completed;
	inline static std::queue<Job> jobs;
	inline static std::condition_variable cv;
	inline static std::atomic<bool> running = false;
	inline static bool started = false;

	public:
	static void ThreadFunction();
	static ImageDimension Enqueue_texture(const std::string& path ,u32 ent);

	static bool HasCompleted();
	static FinishedJob GetResults();

	static void ReStateWorker();
	static void Shutdown();
};
