#ifndef PIXEL_MATH_H
#define PIXEL_MATH_H

#include <math.h>
#include <iostream>

namespace pixel
{
    typedef uint8_t uint8;
    typedef uint16_t uint16;
    typedef uint32_t uint32;
    
    class Math
    {
    private:
        Math() {}

    public:
        static constexpr double PI =  3.14159265359;

    public:
        //Convert from radians to degree
        static float RadToDegree(float rad)
        {
            return rad * (180.0 / PI);
        }

        //Convert from degree to radians
        static float DegreeToRad(float degree)
        {
            return degree * (PI / 180.0);
        }

        //Calculates the cos of an angle in degrees
        static float Sin(float angle)
        {
            float _angle = DegreeToRad(angle);
            return sin(_angle);
        }

        //Calculates the cos of an angle in degrees
        static float Cos(float angle)
        {
            float _angle = DegreeToRad(angle);
            return cos(_angle);
        }

        //Calculates the cos of an angle in degrees
        static float Tan(float angle)
        {
            float _angle = DegreeToRad(angle);
            return tan(_angle);
        }

        //Calculates the inverse sin of a value and returns in radians
        static float Asin(float value)
        {
            return asin(value);
        }

        //Calculates the inverse cos of a value and returns in radians
        static float Acos(float value)
        {
            return acos(value);
        }

        //Calculates the inverse tan of a value and returns in radians
        static float Atan(float value)
        {
            return atan(value);
        }

        //Calculates the radian value of tan y/x
        static float Atan2(float y, float x)
        {
            return atan2(y, x);
        }

        //Calculates the square root of a value
        static float Sqrt(float value)
        {
            return sqrt(value);
        }

        //Returns the largest of two values
        static float Max(float a, float b)
        {
            return a >= b ? a : b;
        }

        //Returns the smallest of two values
        static float Min(float a, float b)
        {
            return a <= b ? a : b;
        }
    
        //Returns the value passed rounded to the nearest integer
        static int Round(float value)
        {
            return (int)(value < 0 ? value - 0.5 : value + 0.5);
        }

        //Returns the float result between the min and max values
        static float Clamp(float value, float min, float max)
        {
            if(value < min)
                value = min;
            else if(value > max)
                value = max;

            return value; 
        }

        //Swaps two values
        template<typename T>
        static void Swap(T* a, T* b)
        {
            T temp = *a;
            *a = *b;
            *b = temp;
        }

        //Returns the absolute of the value passed
        static float Abs(float value)
        {
            return value < 0 ? -value : value;
        }
    };
};

#endif