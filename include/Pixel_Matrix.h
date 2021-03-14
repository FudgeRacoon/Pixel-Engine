#ifndef PIXEL_MATRIX_H
#define PIXEL_MATRIX_H

#include <Pixel_Vector.h>

namespace pixel
{
    class Matrix3
    {
    private:
        float n[3][3];

    public:
        Matrix3() = default;
        Matrix3(float n00, float n01, float n02,
                float n10, float n11, float n12,
                float n20, float n21, float n22)
        {
            n[0][0] = n00; n[0][1] = n01; n[0][2] = n02;
            n[1][0] = n10; n[1][1] = n11; n[1][2] = n12;
            n[2][0] = n20; n[2][1] = n21; n[2][2] = n22;
        }
        Matrix3(Vec3& v1, Vec3& v2, Vec3& v3)
        {
            n[0][0] = v1.x; n[0][1] = v1.y; n[0][2] = v1.z;
            n[1][0] = v2.x; n[1][1] = v2.y; n[1][2] = v2.z;
            n[2][0] = v3.x; n[2][1] = v3.y; n[2][2] = v3.z;
        }
    
    public:
        float& operator()(int row, int column)
        {
            return n[row][column];
        }
        Matrix3 operator+(Matrix3 m)
        {
            return Matrix3
            (
                this->n[0][0] + m(0,0), this->n[0][1] + m(0,1), this->n[0][2] + m(0,2),
                this->n[1][0] + m(1,0), this->n[1][1] + m(1,1), this->n[1][2] + m(1,2),
                this->n[2][0] + m(2,0), this->n[2][1] + m(2,1), this->n[2][2] + m(2,2)
            );
        }
        Matrix3 operator-(Matrix3 m)
        {
            return Matrix3
            (
                this->n[0][0] - m(0,0), this->n[0][1] - m(0,1), this->n[0][2] - m(0,2),
                this->n[1][0] - m(1,0), this->n[1][1] - m(1,1), this->n[1][2] - m(1,2),
                this->n[2][0] - m(2,0), this->n[2][1] - m(2,1), this->n[2][2] - m(2,2)
            );
        }
        Matrix3 operator*(Matrix3 m)
        {
            return Matrix3
            (
                this->n[0][0] * m(0,0) + this->n[0][1] * m(1,0) + this->n[0][2] * m(2,0),
                this->n[0][0] * m(0,1) + this->n[0][1] * m(1,1) + this->n[0][2] * m(2,1),
                this->n[0][0] * m(0,2) + this->n[0][1] * m(1,2) + this->n[0][2] * m(2,2),

                this->n[1][0] * m(0,0) + this->n[1][1] * m(1,0) + this->n[1][2] * m(2,0),
                this->n[1][0] * m(0,1) + this->n[1][1] * m(1,2) + this->n[1][2] * m(2,1),
                this->n[1][0] * m(0,2) + this->n[1][1] * m(1,2) + this->n[1][2] * m(2,2),

                this->n[2][0] * m(0,0) + this->n[2][1] * m(1,0) + this->n[2][2] * m(2,0),
                this->n[2][0] * m(0,1) + this->n[2][1] * m(1,1) + this->n[2][2] * m(2,1),
                this->n[2][0] * m(0,2) + this->n[2][1] * m(1,2) + this->n[2][2] * m(2,2)
            );
        }
        Vec3 operator*(Vec3 v)
        {
            return Vec3
            (
                this->n[0][0] * v.x + this->n[0][1] * v.y + this->n[0][2] * v.z,
                this->n[1][0] * v.x + this->n[1][1] * v.y + this->n[1][2] * v.z,
                this->n[2][0] * v.x + this->n[2][1] * v.y + this->n[2][2] * v.z
            );
        }
    
    public:
        //Returns the identity matrix
        static Matrix3 Identity()
        {
            return Matrix3
            (
                1, 0, 0,
                0, 1, 0,
                0, 0, 1
            );
        }

        //Creates a scaling matrix
        static Matrix3 Scale(Vec3 scale)
        {
            Matrix3 m = Identity();

            m(0,0) = scale.x;
            m(1,1) = scale.y;
            m(2,2) = scale.z;
            
            return m;
        }   
    };
};

#endif