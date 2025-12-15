#include "External/OpenglBind.h"
#include "EngineCore/TextureManager.h"
#include "EngineCore/Shader.h"
#include "Pipeline/Loader.h"


void ApplyFilters(ImageResource* img) {

    glTextureParameteri(img->id, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
    glTextureParameteri(img->id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
    glTextureParameteri(img->id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(img->id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}


u64 TextureManager::createBindlessHandle(ImageResource* image, Texture* tex)
{
	glCreateTextures(GL_TEXTURE_2D, 1, &image->id);
	glTextureStorage2D(image->id, 1, GL_RGBA8, tex->width, tex->height);

	glTextureSubImage2D(
		image->id, 0, 0, 0,
		tex->width, tex->height,
		GL_RGBA, GL_UNSIGNED_BYTE,
		image->Get()
	);

	ApplyFilters(image);
	
	u64 handle = glGetTextureHandleARB(image->id);
	glMakeTextureHandleResidentARB(handle);
	tex->texid = image->id;
	tex->handle = handle;
	image->Free();

	return handle;
}

void TextureManager::RemoveBindless(u64 handle , u32 id)
{


    GLsync fence = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
    deleteQueue.push({ id, handle, fence });

}
void TextureManager::processDelete()
{
    if (deleteQueue.empty())
        return;

    DeleteTex& data = deleteQueue.front();

    GLenum result = glClientWaitSync(
        data.fence,
        0,
        0
    );

    if (result == GL_ALREADY_SIGNALED ||
        result == GL_CONDITION_SATISFIED)
    {
        glDeleteSync(data.fence);

        // 1. Kill bindless access
        glMakeTextureHandleNonResidentARB(data.handle);

        // 2. Delete the texture object
        glDeleteTextures(1, &data.id);

        // 3. REAL confirmation (this is the only valid place)
        if (!glIsTexture(data.id))
        {
            printf("Texture %u is GONE (object deleted, memory freed)\n",
                   data.id);
        }
        else
        {
            printf("Texture %u delete FAILED (still exists)\n",
                   data.id);
        }

        deleteQueue.pop();
    }
}

u32 TextureManager::createSamplerHandle(ImageResource* image)
{
	static u32 gTextureCounter = 0;
	
	GLuint id;
    glGenTextures(1, &id);
	int index = gTextureCounter++;

	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(
		image->id, 0, 0, 0,
		image->width, image->height,
		GL_RGBA, GL_UNSIGNED_BYTE,
		image->Get()
	);
	ApplyFilters(image);
	std::string name = "tex[" + std::to_string(index) + "]";
	GLint loc = glGetUniformLocation(Shader::Get(), name.c_str());
	glUniform1i(loc, index);

	return index;
}

void TextureManager::createDefaultTexture()
{
	ImageLoader loader("Assets/Default.png");
	auto imgScope = loader.Get(); 
	
    GLuint tex;
    glCreateTextures(GL_TEXTURE_2D, 1, &tex);
    glTextureStorage2D(tex, 1, GL_RGBA8, imgScope->width, imgScope->height); 

    glTextureSubImage2D(tex, 0, 0, 0,
        imgScope->width, imgScope->height,
        GL_RGBA, GL_UNSIGNED_BYTE,
        imgScope->Get()
    );

    imgScope->Free();

    GLuint64 defaultHandle = glGetTextureHandleARB(tex);
    glMakeTextureHandleResidentARB(defaultHandle);

    DefaultTexture = defaultHandle;
}

u64& TextureManager::GetDefaultHandle()
{
	return DefaultTexture;
}
