#ifndef M_VECTOR_H
#define M_VECTOR_H

#include <cmath>
#include <stdio.h>

class Vector
{
public:
    float* v;

protected:
    int _dimension;

public:
    Vector(int dimension)
    {
        this->_dimension = dimension;
        this->v = new float[dimension];
        for (int i = 0; i < dimension; i++)
            this->v[i] = 0;
    }
    Vector(int dimension, float* array)
    {
        this->_dimension = dimension;
        this->v = new float[dimension];
        for (int i = 0; i < dimension; i++)
            this->v[i] = array[i];
    }
    ~Vector()
    {
        delete[] this->v;
        this->v = nullptr;
    }


    void Print() const
    {
        printf("[");
        for (int i = 0; i < this->_dimension; i++)
            printf(" %f ", this->v[i]);
        printf("]");
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
    void Scale(float s)
    {
        for (int i = 0; i < this->_dimension; i++)
            this->v[i] *= s;
    }


    /**
     * @brief 矢量相加

     * 矢量相加必须两个矢量的维度相同，对应元素相加即可

     * 我们可以按照几何形式将矢量a和b相加，方法是定位矢量，使得a的头部接触b的尾部，然后绘制一个从a的尾部到b的头部的矢量，矢量加法的三角形法则
     *
     * @param res
     * @param a
     * @param b
     * @return
     */
    Vector& Add(const Vector& source)
    {
        if (this->_dimension != source._dimension)
            throw "Vector dimension not match";
        for (int i = 0; i < this->_dimension; i++)
            this->v[i] += source.v[i];
        return *this;
    }
    static Vector Add(const Vector& source, const Vector& target)
    {
        if (source._dimension != target._dimension)
            throw "Vector dimension not match";
        Vector res(source._dimension);
        res.Add(source).Add(target);
        return res;
    }

    /**
     * @brief 矢量相减

     * 可以看作加一个反方向的矢量
     *
     * @param res
     * @param a
     * @param b
     * @return
     */
    Vector& Subtract(const Vector& source)
    {
        if (this->_dimension != source._dimension)
            throw "Vector dimension not match";
        for (int i = 0; i < this->_dimension; i++)
            this->v[i] -= source.v[i];
        return *this;
    }
    static Vector Subtract(const Vector& source, const Vector& target)
    {
        if (source._dimension != target._dimension)
            throw "Vector dimension not match";
        Vector res(source._dimension);
        res.Subtract(source).Subtract(target);
        return res;
    }

    /**
     * @brief 矢量点积

     * 两个矢量的点积等于它们的各分量的乘积之和

     * 点积的几何意义是矢量的投影，即矢量a在矢量b上的投影长度，矢量a和b的点积等于矢量a在矢量b上的投影向量的长度，矢量a和b的点积等于矢量a在矢量b上的投影面积
     *
     * @param a
     * @param b
     * @return
     */
    float DotProduct(const Vector& source)
    {
        if (source._dimension != this->_dimension)
            throw "Vector dimension not match";
        float res = 0.0f;
        for (int i = 0; i < this->_dimension; i++)
            res += this->v[i] * source.v[i];
        return res;
    }
    static float DotProduct(const Vector& source, const Vector& target)
    {
        if (source._dimension != target._dimension)
            throw "Vector dimension not match";
        float res = 0.0f;
        for (int i = 0; i < source._dimension; i++)
            res += source.v[i] * target.v[i];
        return res;
    }

    /**
     * @brief 矢量长度
     *
     * @param v
     * @return
     */
    float Length()
    {
        float sum = 0.0f;
        for (int i = 0; i < this->_dimension; i++)
            sum += this->v[i] * this->v[i];
        return sqrtf(sum);
    }

    /**
     * @brief 矢量归一化
     */
    void Normalize()
    {
        float len = this->Length();
        if (fabsf(len) < 1e-6)
            throw "Vector length is zero";
        float k = 1 / len;
        for (int i = 0; i < this->_dimension; i++)
            this->v[i] *= k;
    }
};

#endif  // !M_VECTOR_H
