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
};

#endif  // !M_MATRIX_H
