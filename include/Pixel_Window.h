#ifndef PIXEL_WINDOW_H
#define PIXEL_WINDOW_H

#include <SDL2/SDL.h>
#include <iostream>

namespace pixel
{
    struct FrameBuffer;
    
    class Window 
    {
    private:
        char* name;
        uint16_t width;
        uint16_t height;

    private:
        bool isRunning;
        bool isFullscreen;

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        FrameBuffer* frameBuffer;

    public:
        Window(char* name, uint16_t width, uint16_t height, uint32_t windowFlag, uint32_t rendererFlag, bool isFullscreen);
        ~Window();

    public:
        char* GetName();
        uint16_t GetWidth();
        uint16_t GetHeight();

    public:
        bool IsRunning();

    public:
        SDL_Window* GetWindow();
        SDL_Renderer* GetRenderer();
        FrameBuffer* GetFrameBuffer();
    };
};

#endif