#ifndef PIXEL_TIME_H
#define PIXEL_TIME_H

#include <SDL2/SDL.h>

namespace pixel
{
    class Time
    {
    private:
        static float deltaTime;
        static float previousTime;

    private:
        Time() {}

    public:
        //Computes the deltatime
        static void ComputeDeltaTime();
        
        //Returns the completion time in seconds since the last frame
        static float DeltaTime();
        
        //Returns the time in seconds since the start of the engine
        static float CurrentTime();

        //Returns how many frame per seconds are rendered
        static float FrameRate();
    };
};

#endif