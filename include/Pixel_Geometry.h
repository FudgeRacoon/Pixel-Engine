#ifndef PIXEL_GEOMETRY_H
#define PIXEL_GEOMETRY_H

#include <Pixel_Window.h>
#include <Pixel_Vector.h>
#include <Pixel_Color.h>
#include <Pixel_FrameBuffer.h>
#include <iostream>

namespace pixel
{
    float CrossProduct(const Vec2& v1, const Vec2& v2)
    {
        return (v1.x * v2.y) - (v1.y * v2.x);
    }

    //A 2D Rectangle defined by X and Y position, width and height
    struct Rect
    {
        float x;
        float y;
        int width;
        int height;

        Rect(float x, float y, int width, int height) : x(x), y(y), width(width), height(height) {}

        void DrawNoFill(Window* window, Color color)
        {
            FrameBuffer* frameBuffer = window->GetFrameBuffer();

            //Top edge
            frameBuffer->DrawLine(window, x, y, x + width, y, color);
            //Bottom edge
            frameBuffer->DrawLine(window, x, y - height, x + width, y - height, color);
            //Right edge
            frameBuffer->DrawLine(window, x, y, x, y - height, color);
            //Left edge
            frameBuffer->DrawLine(window, x + width, y, x + width, y - height, color);
        }
        void DrawFill(Window* window, Color color)
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

    private:
        void INTERNAL_FlatBottomFill(Window* window, const Vec2& v1, const Vec2& v2, const Vec2& v3, Color color)
        {
            float inverseSlope1 = (float)( v2.x - v1.x ) / ( v2.y - v1.y );
            float inverseSlope2 = (float)( v3.x - v1.x ) / ( v3.y - v1.y );

            float leftX = v1.x;
            float rightX = v1.x;

            for(int scanLine = v1.y; scanLine >= v2.y; scanLine--)
            {
                window->GetFrameBuffer()->DrawLine(window, leftX, scanLine, rightX, scanLine, color);
                leftX -= inverseSlope1;
                rightX -= inverseSlope2;
            }
        }
        void INTERNAL_FlatTopFill(Window* window, const Vec2& v1, const Vec2& v2, const Vec2& v3, Color color)
        {
            float inverseSlope1 = (float)( v3.x - v1.x ) / ( v3.y - v1.y );
            float inverseSlope2 = (float)( v3.x - v2.x ) / ( v3.y - v2.y );

            float leftX = v3.x;
            float rightX = v3.x;

            for(int scanLine = v3.y; scanLine <= v2.y; scanLine++)
            {
                window->GetFrameBuffer()->DrawLine(window, leftX, scanLine, rightX, scanLine, color);
                leftX += inverseSlope1;
                rightX += inverseSlope2;
            }
        }

    public:
        void DrawNoFill(Window* window, Color color)
        {
            FrameBuffer* frameBuffer = window->GetFrameBuffer();

            frameBuffer->DrawLine(window, vertices[0].x, vertices[0].y, vertices[1].x, vertices[1].y, color);
            frameBuffer->DrawLine(window, vertices[1].x, vertices[1].y, vertices[2].x, vertices[2].y, color);
            frameBuffer->DrawLine(window, vertices[2].x, vertices[2].y, vertices[0].x, vertices[0].y, color);
        }
        void DrawFill(Window* window, Color color)
        {   
            /*
            //Sort the vertices according to largest y descendingly
            Vec2 sortedVertices[3];
            for(int i = 0; i < 3; i++)
                sortedVertices[i] = vertices[i];

            for(int pass = 0; pass < 3 - 1; pass++)
                for(int i = 0; i < 3 - pass - 1; i++)
                {
                    if(sortedVertices[i].y <= sortedVertices[i + 1].y)
                    {
                        Vec2 temp = sortedVertices[i];
                        sortedVertices[i] = sortedVertices[i + 1];
                        sortedVertices[i + 1] = temp;
                    }
                }
            
            if(sortedVertices[1].y == sortedVertices[2].y)
                //Draw Flat-Bottom triangle
                INTERNAL_FlatBottomFill
                (
                    window,
                    sortedVertices[0],
                    sortedVertices[1],
                    sortedVertices[2],
                    color
                );
            else if(sortedVertices[0].y == sortedVertices[1].y)
                //Draw Flat-Top triangle
                INTERNAL_FlatTopFill
                (
                    window,
                    sortedVertices[0],
                    sortedVertices[1],
                    sortedVertices[2],
                    color
                );
            else
            {
                //Calcualte the mid-point vertices
                float mY = sortedVertices[1].y;
                float t = ( mY - sortedVertices[0].y ) / ( sortedVertices[2].y - sortedVertices[0].y );
                float mX = sortedVertices[0].x + ( sortedVertices[2].x - sortedVertices[0].x) * t;
            
                INTERNAL_FlatBottomFill(window, sortedVertices[0], sortedVertices[1], Vec2(mX, mY), color);
                INTERNAL_FlatTopFill(window, sortedVertices[1], Vec2(mX, mY), sortedVertices[2], color);
            }*/
            
            int maxX = Math::Max(vertices[0].x, Math::Max(vertices[1].x, vertices[2].x));
            int minX = Math::Min(vertices[0].x, Math::Min(vertices[1].x, vertices[2].x));
            int maxY = Math::Max(vertices[0].y, Math::Max(vertices[1].y, vertices[2].y));
            int minY = Math::Min(vertices[0].y, Math::Min(vertices[1].y, vertices[2].y));

            Vec2 vs1(vertices[1].x - vertices[0].x, vertices[1].y - vertices[0].y);
            Vec2 vs2(vertices[2].x - vertices[0].x, vertices[2].y - vertices[0].y);

            for (int x = minX; x <= maxX; x++)
            {
                for (int y = minY; y <= maxY; y++)
                {
                    Vec2 q(x - vertices[0].x, y - vertices[0].y);

                    float s = (float)CrossProduct(q, vs2) / CrossProduct(vs1, vs2);
                    float t = (float)CrossProduct(vs1, q) / CrossProduct(vs1, vs2);

                    if ( (s >= 0) && (t >= 0) && (s + t <= 1))
                        window->GetFrameBuffer()->DrawPixel(window, x, y, color);
                    
                }
            }
        }
    };
};

#endif