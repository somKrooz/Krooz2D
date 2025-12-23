#pragma once
#include "Utility/Types.h"


struct RGFW_window;
union RGFW_event;

enum class WindowAttributes : u32
{
    ClearBorder = KROOZ_BIT(0),
    Transparent = KROOZ_BIT(5),
    Centered    = KROOZ_BIT(6),
    OpenGL      = KROOZ_BIT(17),
};

inline WindowAttributes operator|(WindowAttributes a, WindowAttributes b)
{
     return static_cast<WindowAttributes>(
        static_cast<u32>(a) | static_cast<u32>(b)
    );
}

namespace KroozWindow
{ 
    static inline RGFW_window *main_window = nullptr;
    static inline RGFW_event* main_event = nullptr;

    RGFW_window *createWindow(int width, int height, str title);
    void defineWindowAttr(WindowAttributes attr);
    RGFW_window *getWindow();
    bool isWindowValid();
    
    void PoolEvent();
    void swapBuffers();
    void destroyWindow();
} 
