#include <Pixel_Time.h>
#include <iostream>

float pixel::Time::deltaTime = 0.0;
float pixel::Time::previousTime = 0.0;

void pixel::Time::ComputeDeltaTime()
{
    SDL_Delay(4);

    deltaTime = (SDL_GetTicks() - previousTime) / 1000.0f;
    previousTime = SDL_GetTicks();
}

float pixel::Time::DeltaTime()
{
    return deltaTime;
}

float pixel::Time::CurrentTime()
{
    return SDL_GetTicks() / 1000.0;
}

float pixel::Time::FrameRate()
{
    return 1.0 / deltaTime;
}