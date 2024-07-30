#ifndef RAN_VECTOR_H
#define RAN_VECTOR_H

#include "Vector.h"

class Vector4 : public Vector
{
public:
    Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) : Vector(4)
    {
        this->_dimension = 4;
        this->v = new float[this->_dimension];
        this->v[0] = x;
        this->v[1] = y;
        this->v[2] = z;
        this->v[3] = w;
    }
    /**
     * @brief 矢量叉积

     * 叉积将产生一个矢量，垂直于原始的两个矢量，方↵
向取决于左右手坐标系
     *
     * @param res
     * @param a
     * @param b
     */
    static void CrossProduct(Vector4& res, const Vector4& a, const Vector4& b)
    {
        res.v[0] = a.v[1] * b.v[2] - a.v[2] * b.v[1];
        res.v[1] = a.v[2] * b.v[0] - a.v[0] * b.v[2];
        res.v[2] = a.v[0] * b.v[1] - a.v[1] * b.v[0];
    }
    static Vector4 CrossProduct(const Vector4& a, const Vector4& b)
    {
        Vector4 res;
        CrossProduct(res, a, b);
        return res;
    }
};

#endif  // !RAN_VECTOR_H
