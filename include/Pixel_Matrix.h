#ifndef PIXEL_MATRIX_H
#define PIXEL_MATRIX_H

#include <Pixel_Vector.h>

namespace pixel
{
    class Matrix4
    {
    private:
        float n[4][4];

    public:
        Matrix4()
        {
            n[0][0] = 0; n[0][1] = 0; n[0][2] = 0; n[0][3] = 0;
            n[1][0] = 0; n[1][1] = 0; n[1][2] = 0; n[1][3] = 0;
            n[2][0] = 0; n[2][1] = 0; n[2][2] = 0; n[2][3] = 0;
            n[3][0] = 0; n[3][1] = 0; n[3][2] = 0; n[3][3] = 0;
        }
        Matrix4(float n00, float n01, float n02, float n03,
                float n10, float n11, float n12, float n13,
                float n20, float n21, float n22, float n23,
                float n30, float n31, float n32, float n33)
        {
            n[0][0] = n00; n[0][1] = n01; n[0][2] = n02; n[0][3] = n03;
            n[1][0] = n10; n[1][1] = n11; n[1][2] = n12; n[1][3] = n13;
            n[2][0] = n20; n[2][1] = n21; n[2][2] = n22; n[2][3] = n23;
            n[3][0] = n30; n[3][1] = n31; n[3][2] = n32; n[3][3] = n33;
        }
        Matrix4(Vec3& v1, Vec3& v2, Vec3& v3, Vec3& v4)
        {
            n[0][0] = v1.x; n[0][1] = v1.y; n[0][2] = v1.z; n[0][3] = 1;
            n[1][0] = v2.x; n[1][1] = v2.y; n[1][2] = v2.z; n[1][3] = 1;
            n[2][0] = v3.x; n[2][1] = v3.y; n[2][2] = v3.z; n[2][3] = 1;
            n[3][0] = v4.x; n[3][1] = v4.y; n[3][2] = v4.z; n[3][3] = 1;
        }
    
    public:
        float& operator()(int row, int column)
        {
            return n[row][column];
        }
        Matrix4 operator+(Matrix4 m)
        {
            return Matrix4
            (
                this->n[0][0] + m(0,0), this->n[0][1] + m(0,1), this->n[0][2] + m(0,2), this->n[0][3] + m(0,3),
                this->n[1][0] + m(1,0), this->n[1][1] + m(1,1), this->n[1][2] + m(1,2), this->n[1][3] + m(1,3),
                this->n[2][0] + m(2,0), this->n[2][1] + m(2,1), this->n[2][2] + m(2,2), this->n[2][3] + m(2,3),
                this->n[3][0] + m(3,0), this->n[3][1] + m(3,1), this->n[3][2] + m(3,2), this->n[3][3] + m(3,3)
            );
        }
        Matrix4 operator-(Matrix4 m)
        {
            return Matrix4
            (
                this->n[0][0] - m(0,0), this->n[0][1] - m(0,1), this->n[0][2] - m(0,2), this->n[0][3] - m(0,3),
                this->n[1][0] - m(1,0), this->n[1][1] - m(1,1), this->n[1][2] - m(1,2), this->n[1][3] - m(1,3),
                this->n[2][0] - m(2,0), this->n[2][1] - m(2,1), this->n[2][2] - m(2,2), this->n[2][3] - m(2,3),
                this->n[3][0] - m(3,0), this->n[3][1] - m(3,1), this->n[3][2] - m(3,2), this->n[3][3] - m(3,3)
            );
        }
        Matrix4 operator*(Matrix4 m)
        {
            return Matrix4
            (
                this->n[0][0] * m(0,0) + this->n[0][1] * m(1,0) + this->n[0][2] * m(2,0) + this->n[0][3] * m(3,0),
                this->n[0][0] * m(0,1) + this->n[0][1] * m(1,1) + this->n[0][2] * m(2,1) + this->n[0][3] * m(3,1),
                this->n[0][0] * m(0,2) + this->n[0][1] * m(1,2) + this->n[0][2] * m(2,2) + this->n[0][3] * m(3,2),
                this->n[0][0] * m(0,3) + this->n[0][1] * m(1,3) + this->n[0][2] * m(2,3) + this->n[0][3] * m(3,3),

                this->n[1][0] * m(0,0) + this->n[1][1] * m(1,0) + this->n[1][2] * m(2,0) + this->n[1][3] * m(3,0),
                this->n[1][0] * m(0,1) + this->n[1][1] * m(1,1) + this->n[1][2] * m(2,1) + this->n[1][3] * m(3,1),
                this->n[1][0] * m(0,2) + this->n[1][1] * m(1,2) + this->n[1][2] * m(2,2) + this->n[1][3] * m(3,2),
                this->n[1][0] * m(0,3) + this->n[1][1] * m(1,3) + this->n[1][2] * m(2,3) + this->n[1][3] * m(3,3),

                this->n[2][0] * m(0,0) + this->n[2][1] * m(1,0) + this->n[2][2] * m(2,0) + this->n[2][3] * m(3,0),
                this->n[2][0] * m(0,1) + this->n[2][1] * m(1,1) + this->n[2][2] * m(2,1) + this->n[2][3] * m(3,1),
                this->n[2][0] * m(0,2) + this->n[2][1] * m(1,2) + this->n[2][2] * m(2,2) + this->n[2][3] * m(3,2),
                this->n[2][0] * m(0,3) + this->n[2][1] * m(1,3) + this->n[2][2] * m(2,3) + this->n[2][3] * m(3,3),

                this->n[3][0] * m(0,0) + this->n[3][1] * m(1,0) + this->n[3][2] * m(2,0) + this->n[3][3] * m(3,0),
                this->n[3][0] * m(0,1) + this->n[3][1] * m(1,1) + this->n[3][2] * m(2,1) + this->n[3][3] * m(3,1),
                this->n[3][0] * m(0,2) + this->n[3][1] * m(1,2) + this->n[3][2] * m(2,2) + this->n[3][3] * m(3,2),
                this->n[3][0] * m(0,3) + this->n[3][1] * m(1,3) + this->n[3][2] * m(2,3) + this->n[3][3] * m(3,3)
            );
        }
        Vec3 operator*(Vec3 v)
        {
            return Vec3
            (
                this->n[0][0] * v.x + this->n[0][1] * v.y + this->n[0][2] * v.z + this->n[0][3] * 1,
                this->n[1][0] * v.x + this->n[1][1] * v.y + this->n[1][2] * v.z + this->n[1][3] * 1,
                this->n[2][0] * v.x + this->n[2][1] * v.y + this->n[2][2] * v.z + this->n[2][3] * 1
            );
        }
    
    public:
        //Returns the identity matrix
        static Matrix4 Identity()
        {
            // | 1   0   0   0 |
            // | 0   1   0   0 |
            // | 0   0   1   0 |
            // | 0   0   0   1 |

            return Matrix4
            (
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            );
        }

        //Creates a translation matrix
        static Matrix4 Translate(Vec3 direction)
        {       
            // | 1   0   0   x |
            // | 0   1   0   y |
            // | 0   0   1   z |
            // | 0   0   0   1 |
            
            Matrix4 m = Identity();

            m(0,3) = direction.x;
            m(1,3) = direction.y;
            m(2,3) = direction.z;

            return m;
        }

        //Creates a scaling matrix
        static Matrix4 Scale(Vec3 scaleFactor)
        {
            // | x   0   0   0 |
            // | 0   y   0   0 |
            // | 0   0   z   0 |
            // | 0   0   0   1 |

            Matrix4 m = Identity();

            m(0,0) = scaleFactor.x;
            m(1,1) = scaleFactor.y;
            m(2,2) = scaleFactor.z;
            
            return m;
        }   

        //Creates a rotation matrix around x-axis
        static Matrix4 RotateX(float angle)
        {
            // |   1       0       0       0 |
            // |   0     cos(0)  sin(0)    0 |
            // |   0    -sin(0)  cos(0)    0 |
            // |   0       0       0       1 |

            float c = Math::Cos(angle);
            float s = Math::Sin(angle);

            Matrix4 m = Identity();

            m(1,1) = c;
            m(1,2) = s;
            m(2,1) = -s;
            m(2,2) = c;

            return m;
        }

        //Creates a rotation matrix around y-axis
        static Matrix4 RotateY(float angle)
        {
            // | cos(0)    0    -sin(0)    0 |
            // |   0       1      0        0 |
            // | sin(0)    0    cos(0)     0 |
            // |   0       0      0        1 |

            float c = Math::Cos(angle);
            float s = Math::Sin(angle);

            Matrix4 m = Identity();

            m(0,0) = c;
            m(0,2) = -s;
            m(2,0) = s;
            m(2,2) = c;

            return m;
        }
    
        //Creates a rotation matrix around z-axis
        static Matrix4 RotateZ(float angle)
        {
            // | cos(0)    -sin(0)   0     0 |
            // | sin(0)     cos(0)   0     0 |
            // |   0          0      1     0 |
            // |   0          0      0     1 |

            float c = Math::Cos(angle);
            float s = Math::Sin(angle);

            Matrix4 m = Identity();

            m(0,0) = c;
            m(0,1) = -s;
            m(1,0) = s;
            m(1,1) = c;

            return m;
        }
    };
};

#endif