#ifndef PIXEL_GEOMETRY_H
#define PIXEL_GEOMETRY_H

#include <Pixel_Window.h>
#include <Pixel_Vector.h>
#include <Pixel_FrameBuffer.h>
#include <iostream>

namespace pixel
{
    //A 2D Rectangle defined by X and Y position, width and height
    struct Rect
    {
        float x;
        float y;
        int width;
        int height;

        Rect(float x, float y, int width, int height) : x(x), y(y), width(width), height(height) {}

        void DrawNoFill(Window* window, uint32_t color)
        {
            FrameBuffer* frameBuffer = window->GetFrameBuffer();

            //Draw top and bottom edges
            for(int counter = 0; counter <= width; counter++)
            {
                frameBuffer->DrawPixel(window, x + counter, y, color);
                frameBuffer->DrawPixel(window, x + counter, y + height, color);
            }
            //Draw right and left edges
            for(int counter = 0; counter <= height; counter++)
            {
                frameBuffer->DrawPixel(window, x, y + counter, color);
                frameBuffer->DrawPixel(window, x + width, y + counter, color);
            }
        }
        void DrawFill(Window* window, uint32_t color)
        {
            FrameBuffer* frameBuffer = window->GetFrameBuffer();

            //Draw top and bottom edges
            for(int counter = 0; counter <= width; counter++)
            {
                frameBuffer->DrawPixel(window, x + counter, y, color);
                frameBuffer->DrawPixel(window, x + counter, y + height, color);
            }
            //Draw right and left edges
            for(int counter = 0; counter <= height; counter++)
            {
                frameBuffer->DrawPixel(window, x, y + counter, color);
                frameBuffer->DrawPixel(window, x + width, y + counter, color);
            }

            //Fills the shape with color passed
            for(int counter_1 = 0; counter_1 <= height; counter_1++)
                for(int counter_2 = 0; counter_2 <= width; counter_2++)
                    frameBuffer->DrawPixel(window, x + counter_2, y + counter_1, color);
        }
    };

    //A 2D Triangle defined by 3 vertices
    struct Triangle
    {
        Vec2 vertices[3];

        Triangle () {}
        Triangle(Vec2 vertices[])
        {
            for(int i = 0; i < 3; i++)
                this->vertices[i] = vertices[i];
        }

        void DrawNoFill(Window* window, uint32_t color)
        {
            FrameBuffer* frameBuffer = window->GetFrameBuffer();

            frameBuffer->DrawLine(window, vertices[0].x, vertices[0].y, vertices[1].x, vertices[1].y, color);
            frameBuffer->DrawLine(window, vertices[1].x, vertices[1].y, vertices[2].x, vertices[2].y, color);
            frameBuffer->DrawLine(window, vertices[2].x, vertices[2].y, vertices[0].x, vertices[0].y, color);
        }
    };
};

#endif