#ifndef M_MATRIX_H
#define M_MATRIX_H

#include <stdio.h>

class Matrix4x4
{
public:
    const static int MAX = 4;
    float m[Matrix4x4::MAX][Matrix4x4::MAX];

public:
    Matrix4x4()
    {
        int len = Matrix4x4::MAX;
        for (int i = 0; i < len; i++)
            for (int j = 0; j < len; j++)
            {
                this->m[i][j] = 0.0f;
            }
    }
    Matrix4x4(float v[Matrix4x4::MAX][Matrix4x4::MAX])
    {
        int len = Matrix4x4::MAX;
        for (int i = 0; i < len; i++)
            for (int j = 0; j < len; j++) this->m[i][j] = v[i][j];
    }


    void Print()
    {
        int len = Matrix4x4::MAX;
        for (int i = 0; i < len; i++)
        {
            printf(" | ");
            for (int j = 0; j < len; j++)
            {
                printf(" %f ", this->m[i][j]);
            }
            printf(" | \n");
        }
    }


    /**
     * @brief 转置
     */
    void Transpose(int len = Matrix4x4::MAX)
    {
        for (int i = 0; i < len; i++)
            for (int j = i + 1; j < len; j++)
            {
                float temp = this->m[i][j];
                this->m[i][j] = this->m[j][i];
                this->m[j][i] = temp;
            }
    }


    /**
     * @brief 矩阵缩放
     *
     * @param s
     */
    void Scale(float s)
    {
        int len = Matrix4x4::MAX;
        for (int i = 0; i < len; i++)
            for (int j = 0; j < len; j++) this->m[i][j] *= s;
    }


    /**
     * @brief 矩阵相加
     *
     * @param res
     * @param a
     * @param b
     */
    static void Add(Matrix4x4* res, Matrix4x4* a, Matrix4x4* b)
    {
        int len = Matrix4x4::MAX;
        for (int i = 0; i < len; i++)
            for (int j = 0; j < len; j++) res->m[i][j] = a->m[i][j] + b->m[i][j];
    }
    static Matrix4x4 Add(Matrix4x4* a, Matrix4x4* b)
    {
        Matrix4x4 res;
        Matrix4x4::Add(&res, a, b);
        return res;
    }


    /**
     * @brief 矩阵减法
     *
     * @param res
     * @param a
     * @param b
     */
    static void Subtract(Matrix4x4* res, Matrix4x4* a, Matrix4x4* b)
    {
        int len = Matrix4x4::MAX;
        for (int i = 0; i < len; i++)
            for (int j = 0; j < len; j++) res->m[i][j] = a->m[i][j] - b->m[i][j];
    }
    static Matrix4x4 Subtract(Matrix4x4* a, Matrix4x4* b)
    {
        Matrix4x4 res;
        Matrix4x4::Subtract(&res, a, b);
        return res;
    }


    /**
     * @brief 矩阵相乘
     *
     * @param res
     * @param a
     * @param b
     */
    static void Multiply(Matrix4x4* res, Matrix4x4* a, Matrix4x4* b)
    {
        int len = Matrix4x4::MAX;
        for (int i = 0; i < len; i++)
            for (int j = 0; j < len; j++) res->m[i][j] = a->m[i][0] * b->m[0][j] + a->m[i][1] * b->m[1][j] + a->m[i][2] * b->m[2][j] + a->m[i][3] * b->m[3][j];
    }
    static Matrix4x4 Multiply(Matrix4x4* a, Matrix4x4* b)
    {
        Matrix4x4 res;
        Matrix4x4::Multiply(&res, a, b);
        return res;
    }
};

#endif  // !M_MATRIX_H
