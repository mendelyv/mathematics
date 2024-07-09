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


    /**
     * @brief 矢量相加

     * 矢量相加必须两个矢量的维度相同，对应元素相加即可

     * 我们可以按照几何形式将矢量a和b相加，方法是定位矢量，使得a的头部接触b的尾部，然后绘制一个从a的尾部到b的头部的矢量，矢量加法的三角形法则
     *
     * @param a 
     * @param b 
     * @return 
     */
    static Vector4* Add(Vector4* a, Vector4* b)
    {
        Vector4* result = new Vector4();
        result->x = a->x + b->x;
        result->y = a->y + b->y;
        result->z = a->z + b->z;
        result->w = a->w + b->w;
        return result;
    }


};

#endif // !RAN_VECTOR_H
