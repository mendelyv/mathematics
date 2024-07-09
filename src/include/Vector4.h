#ifndef RAN_VECTOR_H
#define RAN_VECTOR_H

#include <iostream>

class Vector4
{
public:
    float x;
    float y;
    float z;
    float w;

public:
    Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }


    void Print()
    {
        std::cout << "[ " << x << ", " << y << ", " << z << ", " << w << " ]" << std::endl;
    }


    /**
     * @brief 矢量缩放
     *
     * 矢量与标量相乘，使用标量乘以矢量的每个分量即可
     *
     * 在几何上，将矢量乘以标量s具有将长度缩放|s|因子的效果，如果s<0，则反转矢量的方向
     *
     * @param v 矢量
     * @param s 缩放系数
     */
    static void Scale(Vector4* v, float s)
    {
        v->x *= s;
        v->y *= s;
        v->z *= s;
        v->w *= s;
    }


};

#endif // !RAN_VECTOR_H
