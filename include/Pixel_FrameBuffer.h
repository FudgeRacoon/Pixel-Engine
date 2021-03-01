#ifndef PIXEL_FRAMEBUFFER_H
#define PIXEL_FRAMEBUFFER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Pixel_Window.h>
#include <Pixel_Math.h>
#include <iostream>

#include <SDL2/SDL_image.h>

namespace pixel
{   
    //A data structure that holds data about pixels in a window
    struct FrameBuffer 
    {
        uint32_t* data;
        SDL_Texture* frameBuffer_texture;

        FrameBuffer(Window* window)
        {
            //Create a texture where pixel data in framebuffer will be drawn on
            frameBuffer_texture = SDL_CreateTexture
            (
                window->GetRenderer(), 
                SDL_PIXELFORMAT_ARGB8888, 
                SDL_TEXTUREACCESS_STREAMING, 
                window->GetWidth(), 
                window->GetHeight()
            );

            //Initialize an array holding pixel data
            data = new uint32_t[window->GetWidth() * window->GetHeight()];
        }
        ~FrameBuffer()
        {
            delete[] data;
            SDL_DestroyTexture(frameBuffer_texture);
        }
        
        //Renders all pixels contained in the framebuffer
        void RenderBuffer(Window* window)
        {
            //Update the framebuffer texture with the pixel data stored
            SDL_UpdateTexture(frameBuffer_texture, NULL, data, window->GetWidth() * sizeof(uint32_t));

            //Render the texture using renderer passed and present it to the front buffer
            SDL_RenderCopy(window->GetRenderer(), frameBuffer_texture, NULL, NULL);
        
            SDL_RenderPresent(window->GetRenderer());
        }

        //Draws a pixel on the window respecting cartesian coordinates
        void DrawPixel(Window* window, float x, float y, uint32_t color)
        {
            int xOrigin = window->GetWidth() / 2;
            int yOrigin = window->GetHeight() / 2;

            int _x = xOrigin + Math::Round(x);
            int _y = yOrigin - Math::Round(y);

            bool withinBoundries = (_x >= 0 && _x < window->GetWidth()) && (_y >= 0 && _y < window->GetHeight());

            if(withinBoundries)
                data[(window->GetWidth() * _y) + _x] = color;      
        }

        //Draws a line on the on the window respecting cartesian coordinates
        void DrawLine(Window* window, float x1, float y1, float x2, float y2, uint32_t color)
        {   
            float dX = x2 - x1;
            float dY = y2 - y1;

            //If slope is less than 1 take dX, if slope is larger than 1 take dY
            float step = Math::Abs(dX) > Math::Abs(dY) ? Math::Abs(dX) : Math::Abs(dY);

            float xInc = dX / step;
            float yInc = dY / step;

            float x = x1;
            float y = y1;

            for(int i = 1; i <= step; i++)
            {
                window->GetFrameBuffer()->DrawPixel(window, x, y, color);
                x += xInc;
                y += yInc;
            }
        }

        //Clears the framebuffer with the color passed 
        void ClearBuffer(Window* window, uint32_t color)
        {
            for(int y = 0; y < window->GetHeight(); y++)
                for(int x = 0; x < window->GetWidth(); x++)
                    data[(window->GetWidth() * y) + x] = color;
        }
    };
};

#endif