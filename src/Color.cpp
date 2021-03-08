#include <Pixel_Color.h>

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

