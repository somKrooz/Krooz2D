#include "Pipeline/Loader.h"
#include "EngineCore/Shader.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "External/STB.h"

ImageLoader::ImageLoader(str path)
{
	image = createScope<ImageResource>();
	LoadFromPath(path, image.get());
}

ImageLoader::ImageLoader(vec<u8>& data)
{
	image = createScope<ImageResource>();
	LoadFromMemory(data, image.get());
}

void ImageLoader::LoadFromPath(str path, ImageResource* img)
{
    int channels = 0;

    u8* raw = stbi_load(path.c_str(), &img->width, &img->height, &channels, 4);
    if (!raw) {
        img->pixels.clear();
        img->width = img->height = 0;
        return;
    }

    int resizedW = std::max(1, img->width);
    int resizedH = std::max(1, img->height);

    std::vector<u8> resized(resizedW * resizedH * 4); 


    stbir_resize_uint8_srgb(
        raw, img->width, img->height, 0,
        resized.data(), resizedW, resizedH, 0,
        STBIR_RGBA_NO_AW
    );

    stbi_image_free(raw);

    img->pixels = std::move(resized);
    img->width  = resizedW;
    img->height = resizedH;
}

void ImageLoader::LoadFromMemory(vec<u8>& buffer, ImageResource* img)
{
	int channels = 0;
	u8* raw = stbi_load_from_memory(buffer.data(), (int)buffer.size(), &img->width, &img->height, &channels, 4);

	size_t size = img->width * img->height * 4;
	img->pixels.assign(raw, raw + size);

	stbi_image_free(raw);
}

scope<ImageResource> ImageLoader::Get(){
	return std::move(image);
}


void AsyncTexture::ThreadFunction()
{
	while (true) {
		Job job;
		{
			std::unique_lock<std::mutex> lock(mtx);
			cv.wait(lock, [] { return !jobs.empty() || !running; });

			if (!running && jobs.empty()) break;

			job = std::move(jobs.front());
			jobs.pop();
		}

		ImageLoader loader(job.path);
		auto imgScope = loader.Get(); 

		if (imgScope) {
			job.image->pixels = std::move(imgScope->pixels);
			job.image->id = 0;

			job.tex->handle = 0;
			job.tex->entid = job.ID;
			job.tex->handle = 0;
			job.tex->entid = job.ID;

		}
		{
			std::lock_guard<std::mutex> lock(mtx);
			completed.push( { std::move(job.image),job.tex } );
		}
	}
}

void AsyncTexture::ReStateWorker()
{
	if (started)
		return;
	running = true;
	started = true;
	worker = std::thread(ThreadFunction);
}

std::pair<int , int> AsyncTexture::Enqueue_texture(const std::string& path , Texture* tex , u32 ent)
{
	int w,h;
	stbi_info(path.c_str() ,&w,&h,NULL);

	ReStateWorker();
	scope<ImageResource> image = createScope<ImageResource>();
	{
		std::lock_guard<std::mutex> lock(mtx);
		jobs.push({path, std::move(image),tex, ent});
	}

	cv.notify_one();

	return{w,h};
}

bool AsyncTexture::HasCompleted()
{
	std::lock_guard<std::mutex> lock(mtx);
	return !completed.empty();	
}

FinishedJob AsyncTexture::GetResults()
{
	std::lock_guard<std::mutex> lock(mtx);
	if(completed.empty()){
		return {};
	}
	auto e = std::move(completed.front());
	completed.pop();
	return e;
}

void AsyncTexture::Shutdown()
{
	if (!started) return;
	{
		std::lock_guard<std::mutex> lock(mtx);
		running = false;
	}
	cv.notify_all();
	if (worker.joinable())
		worker.join();
	started = false;
}
