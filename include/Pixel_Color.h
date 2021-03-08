#ifndef PIXEL_COLOR_H
#define PIXEL_COLOR_H

namespace pixel
{
    class Color
    {
    public:
        float r, g, b, a;

    public:
        Color(float r, float g, float b, float a);
        Color(float r, float g, float b);
        
    public:
        static Color White();
        static Color Black();
        static Color Pink();
        static Color Cyan();
        static Color Purple();
        static Color Yellow();

    public:
        Color operator +(Color color);
        Color operator -(Color color);
        Color operator *(Color color);
        Color operator *(float value);
    };
}

#endif