#include <Pixel_Color.h>
#include <string>
#include <sstream>
#include <iostream>

pixel::Color::Color() : r(0), g(0), b(0), a(255) {}
pixel::Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
pixel::Color::Color(float r, float g, float b) :  r(r), g(g), b(b)
{
    this->a = 255;
}

pixel::Color pixel::Color::White()
{
    return Color(255, 255, 255);
}
pixel::Color pixel::Color::Black()
{
    return Color(0, 0, 0);
}
pixel::Color pixel::Color::Red()
{
    return Color(255, 0, 0);
}
pixel::Color pixel::Color::Blue()
{
    return Color(0, 0, 255);
}
pixel::Color pixel::Color::Green()
{
    return Color(0, 255, 0);
}
pixel::Color pixel::Color::Pink()
{
    return Color(255, 192, 203);
}
pixel::Color pixel::Color::Cyan()
{
    return Color(0, 255, 255);
}
pixel::Color pixel::Color::Purple()
{
    return Color(128, 0, 128);
}
pixel::Color pixel::Color::Yellow()
{
    return Color(255, 255, 0);
}

pixel::Color pixel::Color::Lerp(Color a, Color b, float t)
{
    return pixel::Color
    (
        a.r + (b.r - a.r) * t,
        a.g + (b.g - a.g) * t,
        a.b + (b.b - a.b) * t,
        a.a + (b.a - a.a) * t
    );
}

pixel::uint32 pixel::Color::RgbToHex(Color color)
{   
    int r = color.r;
    int g = color.g;
    int b = color.b;
    int a = color.a;

    return (a << 24) + (r << 16) + (g << 8) + b;
}

pixel::Color pixel::Color::HextoRGB(pixel::uint32 color)
{
    Color _color;

    _color.a = color >> 24;
    _color.r = color >> 16;
    _color.g = color >> 8;
    _color.b = color;

    return _color;
}