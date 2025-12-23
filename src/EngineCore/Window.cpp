#include "EngineCore/Window.h"

#define RGFW_IMPLEMENTATION
#define RGFW_OPENGL
#include "External/WindowBind.h"
#include "External/OpenglBind.h"

#include "EngineCore/Input.h"
#include "Pipeline/Loader.h"

static RGFW_event spareEvent;
namespace KroozWindow
{
    RGFW_window* createWindow(int width, int height, str title)
    {
        RGFW_window *window = RGFW_createWindow(title.c_str(), 0, 0, width, height, RGFW_windowOpenGL);

        main_window = window;
        main_event = &spareEvent;

        if(gladLoadGLLoader((GLADloadproc)RGFW_getProcAddress_OpenGL)){
            printf("Opengl Context Is Initialized\n");
        }

        return main_window;
    }

    RGFW_window* getWindow(){
        return main_window;
    }

    bool isWindowValid()
    {
        return RGFW_window_shouldClose(main_window);
    }

    void PoolEvent()
    {
        RGFW_pollEvents();
        if(RGFW_window_checkEvent(main_window, main_event))
        {
            Input::Update(*main_event);
        }
    }
    void swapBuffers()
    {
        RGFW_window_swapBuffers_OpenGL(main_window);
    }

    void defineWindowAttr(WindowAttributes attr)
    {
        RGFW_window_setFlagsInternal(main_window, static_cast<RGFW_windowFlags>(attr), 0);
        
    }

    void destroyWindow()
    {
        AsyncTexture::Shutdown();
        RGFW_window_close(main_window);
    }
}