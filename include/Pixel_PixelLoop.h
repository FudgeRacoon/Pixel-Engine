#ifndef PIXEL_PIXELLOOP_H
#define PIXEL_PIXELLOOP_H

#include <SDL2/SDL.h>
#include <Pixel_Window.h>
#include <Pixel_Time.h>

//Base class to create a pixel program
class PixelLoop 
{
public:
    pixel::Window* window;

public:
    void Run();

public:
    virtual void Setup() = 0;
    virtual void ProcessInput(SDL_Event event) = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
};

#endif