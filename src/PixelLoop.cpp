#include <Pixel_PixelLoop.h>
#include <iostream>

void pixel::PixelLoop::Run()
{
    Setup();

    while(window->IsRunning())
    {
        //Input
        SDL_PollEvent(&pixel::Input::event);
            
        if(!window->IsRunning())
            break;

        //Update
        pixel::Time::ComputeDeltaTime();
        Update();

        //Render
        Render();
    }
}