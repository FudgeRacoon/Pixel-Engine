#ifndef PIXEL_VECTOR_H
#define PIXEL_VECTOR_H

#include <Pixel_Math.h>

namespace pixel
{
    //Representation of 2D vectors and points
    class Vec2
    {
    public:
        float x;
        float y;

    public:
        Vec2() : x(0), y(0) {}
        Vec2(float x, float y) : x(x), y(y) {}

    public:
        Vec2 operator +(Vec2 vec)
        {
            Vec2 result;
            result.x = this->x + vec.x;
            result.y = this->y + vec.y;
            return result;
        }
        Vec2 operator -(Vec2 vec)
        {
            Vec2 result;
            result.x = this->x - vec.x;
            result.y = this->y - vec.y;
            return result;
        }
        Vec2 operator -()
        {
            Vec2 result;
            result.x = -this->x;
            result.y = -this->y;
            return result;
        }
        Vec2 operator *(int value)
        {
            Vec2 result;
            result.x = this->x * value;
            result.y = this->y * value;
            return result;
        }
        bool operator ==(Vec2 vec)
        {
            return this->x == vec.x && this->y == vec.y;
        }
        bool operator !=(Vec2 vec)
        {
            return this->x != vec.x && this->y != vec.y;
        }

    public:
        //Calculates the magnitude of a vector
        static float Magnitude(Vec2 v1)
        {
            return Math::Sqrt((v1.x * v1.x) + (v1.y * v1.y));
        }
        
        //Calculates the unit vector of a vector
        static Vec2 Normalize(Vec2 v1)
        {
            return v1 * (1 / Magnitude(v1));
        }
        
        //Calculates the dot product of two vectors
        static float Dot(Vec2 v1, Vec2 v2)
        {
            return ((v1.x * v2.x) + (v1.y * v2.y));
        }
        
        //Calculates the distance between two vectors
        static float Distance(Vec2 v1, Vec2 v2)
        {
            float distX = v1.x - v2.x;
            float distY = v1.y - v2.y;
            return Magnitude(Vec2(distX, distY));
        }
        
        //Calculates the degree angle between two vectors
        static float Angle(Vec2 v1, Vec2 v2)
        {
            return Math::RadToDegree(Math::Acos((Dot(v1, v2) / (Magnitude(v1) * Magnitude(v2)))));
        }
    };

    //Representation of 3D vectors and points
    class Vec3
    {
    public:
        float x;
        float y;
        float z;

    public:
        Vec3() : x(0), y(0), z(0) {}
        Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    public:
        Vec3 operator +(Vec3 vec)
        {
            Vec3 result;
            result.x = this->x + vec.x;
            result.y = this->y + vec.y;
            result.z = this->z + vec.z;
            return result;
        }
        Vec3 operator -(Vec3 vec)
        {
            Vec3 result;
            result.x = this->x - vec.x;
            result.y = this->y - vec.y;
            result.z = this->z - vec.z;
            return result;
        }
        Vec3 operator -()
        {
            Vec3 result;
            result.x = -this->x;
            result.y = -this->y;
            result.z = -this->z;
            return result;
        }
        Vec3 operator *(int value)
        {
            Vec3 result;
            result.x = this->x * value;
            result.y = this->y * value;
            result.z = this->z * value;
            return result;
        }
        bool operator ==(Vec3 vec)
        {
            return this->x == vec.x && this->y == vec.y && this->z == vec.z;
        }
        bool operator !=(Vec3 vec)
        {
            return this->x != vec.x && this->y != vec.y && this->z != vec.z;
        }

    public:
        //Calculates the magnitude of a vector
        static float Magnitude(Vec3 v1)
        {
            return Math::Sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
        }
        
        //Calculates the unit vector of a vector
        static Vec3 Normalize(Vec3 v1)
        {
            return v1 * (1 / Magnitude(v1));
        }
        
        //Calculates the dot product of two vectors
        static float Dot(Vec3 v1, Vec3 v2)
        {
            return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
        }
        
        //Calculates the cross product of two vectors
        static Vec3 Cross(Vec3 v1, Vec3 v2)
        {
            return Vec3((v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z), (v1.x * v2.y) - (v1.y * v2.x));
        }

        //Calculates the distance between two vectors
        static float Distance(Vec3 v1, Vec3 v2)
        {
            float distX = v1.x - v2.x;
            float distY = v1.y - v2.y;
            float distZ = v1.z - v2.z;
            return Magnitude(Vec3(distX, distY, distZ));
        }
        
        //Calculates the degree angle between two vectors
        static float Angle(Vec3 v1, Vec3 v2)
        {
            return Math::RadToDegree(Math::Acos((Dot(v1, v2) / (Magnitude(v1) * Magnitude(v2)))));
        }

        static Vec3 RotateX(Vec3 point, float angle)
        {
            Vec3 newPoint;
            newPoint.x = point.x;
            newPoint.y = point.y * Math::Cos(angle) + point.z * Math::Sin(angle);
            newPoint.z = point.z * Math::Cos(angle) - point.y * Math::Sin(angle);
            return newPoint;
        }
        static Vec3 RotateY(Vec3 point, float angle)
        {
            Vec3 newPoint;
            newPoint.x = point.x * Math::Cos(angle) - point.z * Math::Sin(angle);
            newPoint.y = point.y;
            newPoint.z = point.z * Math::Cos(angle) + point.x * Math::Sin(angle);
            return newPoint;
        }
        static Vec3 RotateZ(Vec3 point, float angle)
        {
            Vec3 newPoint;
            newPoint.x = point.x * Math::Cos(angle) - point.y * Math::Sin(angle);
            newPoint.y = point.y * Math::Cos(angle) + point.z * Math::Sin(angle);
            newPoint.z = point.z;
            return newPoint;
        }
    };
};


#endif