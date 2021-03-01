#include <Pixel_PixelLoop.h>
#include <iostream>

void PixelLoop::Run()
{
    Setup();

    while(window->IsRunning())
    {
        //Input
        SDL_Event event;
        while(SDL_PollEvent(&event))
            ProcessInput(event);
        if(!window->IsRunning())
            break;

        //Update
        pixel::Time::ComputeDeltaTime();
        Update();

        //Render
        Render();
    }
}