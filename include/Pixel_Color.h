#ifndef PIXEL_COLOR_H
#define PIXEL_COLOR_H

#include <Pixel_Math.h>

namespace pixel
{
    class Color
    {
    public:
        uint8 r, g, b, a;

    public:
        Color();
        Color(float r, float g, float b, float a);
        Color(float r, float g, float b);
        
    public:
        static Color White();
        static Color Black();
        static Color Red();
        static Color Blue();
        static Color Green();
        static Color Pink();
        static Color Cyan();
        static Color Purple();
        static Color Yellow();

    public:
        Color operator +(Color color)
        {
            Color result;
            result.r = pixel::Math::Clamp(this->r + color.r, 0, 255);
            result.g = pixel::Math::Clamp(this->g + color.g, 0, 255);
            result.b = pixel::Math::Clamp(this->b + color.b, 0, 255);
            result.a = pixel::Math::Clamp(this->a + color.a, 0, 255);
            return result;
        }
        Color operator -(Color color)
        {
            Color result;
            result.r = pixel::Math::Clamp(this->r - color.r, 0, 255);
            result.g = pixel::Math::Clamp(this->g - color.g, 0, 255);
            result.b = pixel::Math::Clamp(this->b - color.b, 0, 255);
            result.a = pixel::Math::Clamp(this->a - color.a, 0, 255);
            return result;
        }
        Color operator *(Color color)
        {
            Color result;
            result.r = pixel::Math::Clamp(this->r * color.r, 0, 255);
            result.g = pixel::Math::Clamp(this->g * color.g, 0, 255);
            result.b = pixel::Math::Clamp(this->b * color.b, 0, 255);
            result.a = pixel::Math::Clamp(this->a * color.a, 0, 255);
            return result;
        }
        Color operator *(float value)
        {
            Color result;
            result.r = pixel::Math::Clamp(this->r * value, 0, 255);
            result.g = pixel::Math::Clamp(this->g * value, 0, 255);
            result.b = pixel::Math::Clamp(this->b * value, 0, 255);
            result.a = pixel::Math::Clamp(this->a * value, 0, 255);
            return result;
        }
        bool operator =(Color color)
        {
            return this->r == color.r && 
                   this->g == color.g &&
                   this->b == color.b &&
                   this->a == color.a;
        }
        bool operator !=(Color color)
        {
            return this->r != color.r && 
                   this->g != color.g &&
                   this->b != color.b &&
                   this->a != color.a;
        }

    public:
        /**
         * @brief Linearly interpolates between colors a and b by t.
         * 
         * @param a Color a
         * @param b Color b
         * @param t Float for combining a and b
         * 
         * @return returns a new color that lies between a and b by t
         */
        static Color Lerp(Color a, Color b, float t);

    public:
        /**
         * @brief Converts a RGB value to hexadecimal
         * 
         * @param color the color to be converted
         * 
         * @return returns an unsigned 32 bit integer
         */
        static uint32 RgbToHex(Color color);

        /**
         * @brief Converts a hex value to RGB 
         * 
         * @param color the color to be converted
         * 
         * @return returns a color object
         */
        static Color HextoRGB(uint32 color);
    };
}

#endif