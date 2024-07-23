#ifndef M_MATRIX_H
#define M_MATRIX_H

#include <stdio.h>

class Matrix
{
public:
    float** m;

protected:
    int _row;
    int _column;

public:
    Matrix(int row, int column)
    {
        this->Init(row, column);
    }
    Matrix(const Matrix& other)
    {
        this->Init(other._row, other._column);
        for (int i = 0; i < other._row; i++)
            for (int j = 0; j < other._column; j++)
                this->m[i][j] = other.m[i][j];
    }
    Matrix& operator=(const Matrix& other)
    {
        if (this == &other)
            return *this;
        this->Destroy();
        this->Init(other._row, other._column);
        for (int i = 0; i < other._row; i++)
            for (int j = 0; j < other._column; j++)
                this->m[i][j] = other.m[i][j];
        return *this;
    }
    ~Matrix()
    {
        this->Destroy();
    }


    int row() const
    {
        return this->_row;
    }
    int column() const
    {
        return this->_column;
    }


    void SetValuesFromArray(const float* array)
    {
        if (nullptr == array)
            throw "Input array cannot be null";
        for (int i = 0; i < this->_row; i++)
            for (int j = 0; j < this->_column; j++)
                this->m[i][j] = array[i * this->_column + j];
    }


    void SetValuesFrom2DArray(const float** array)
    {
        if (nullptr == array)
            throw "Input array cannot be null";
        for (int i = 0; i < this->_row; i++)
            for (int j = 0; j < this->_column; j++)
                this->m[i][j] = array[i][j];
    }


    void Init(int row, int column, float defaultValue = 0.0f)
    {
        this->_row = row;
        this->_column = column;
        this->m = new float*[row];
        for (int i = 0; i < row; i++)
        {
            this->m[i] = new float[column];
            for (int j = 0; j < column; j++)
            {
                this->m[i][j] = defaultValue;
            }
        }
    }


    void Destroy()
    {
        if (this->m)
        {
            for (int i = 0; i < this->_row; i++)
            {
                delete[] this->m[i];
                this->m[i] = nullptr;
            }
        }
        delete[] this->m;
        this->m = nullptr;
    }


    void Print()
    {
        for (int i = 0; i < this->_row; i++)
        {
            printf(" | ");
            for (int j = 0; j < this->_column; j++)
            {
                printf(" %f ", this->m[i][j]);
            }
            printf(" | \n");
        }
    }


    Matrix Clone()
    {
        return Matrix(*this);
    }


    /**
     * @brief 矩阵转置
     */
    void Transpose()
    {
        Matrix temp = this->Clone();
        this->Destroy();
        int row = temp._column;
        int column = temp._row;
        this->Init(row, column);
        for (int i = 0; i < temp._row; i++)
            for (int j = 0; j < temp._column; j++)
                this->m[j][i] = temp.m[i][j];
    }


    /**
     * @brief 矩阵缩放
     *
     * @param s 缩放倍率
     */
    void Scale(float s)
    {
        for (int i = 0; i < this->_row; i++)
            for (int j = 0; j < this->_column; j++)
                this->m[i][j] *= s;
    }


    /**
     * @brief 加一个矩阵
     *
     * @param datas
     */
    void Add(const Matrix& datas)
    {
        if (datas._row != this->_row && datas._column != this->_column)
            throw "Matrix size not match";
        for (int i = 0; i < this->_row; i++)
            for (int j = 0; j < this->_column; j++)
                this->m[i][j] += datas.m[i][j];
    }


    /**
     * @brief 减一个矩阵
     *
     * @param datas
     */
    void Subtract(const Matrix& datas)
    {
        if (datas._row != this->_row && datas._column != this->_column)
            throw "Matrix size not match";
        for (int i = 0; i < this->_row; i++)
            for (int j = 0; j < this->_column; j++)
                this->m[i][j] -= datas.m[i][j];
    }


    /**
     * @brief 矩阵相乘
     *
     * @param a
     * @param b
     * @return
     */
    static Matrix Multiply(const Matrix& a, const Matrix& b)
    {
        if (a._column != b._row)
            throw "Matrix size not match";
        Matrix res(a._row, b._column);
        for (int i = 0; i < a._row; i++)
            for (int j = 0; j < b._column; j++)
                for (int k = 0; k < a._column; k++)
                    res.m[i][j] += a.m[i][k] * b.m[k][j];
        return res;
    }


    /**
     * @brief 子矩阵
     *
     * @param row
     * @param column
     * @return
     */
    Matrix Submatrix(int excludingRow, int excludingColumn) const
    {
        Matrix sub(this->_row - 1, this->_column - 1);
        int sub_i = 0;
        for (int i = 0; i < this->_row; i++)
        {
            if (i == excludingRow)
                continue;
            int sub_j = 0;
            for (int j = 0; j < this->_column; j++)
            {
                if (j == excludingColumn)
                    continue;
                sub.m[sub_i][sub_j] = m[i][j];
                sub_j++;
            }
            sub_i++;
        }
        return sub;
    }


    float Determinant() const
    {
        if (this->_row != this->_column)
            throw "Matrix must be square to compute determinant";
        if (this->_row == 2 && this->_column == 2)
            return this->m[0][0] * this->m[1][1] - this->m[0][1] * this->m[1][0];
        float det = 0.0f;
        for (int i = 0; i < this->_row; i++)
        {
            Matrix sub = this->Submatrix(0, i);
            int direction = (i % 2 == 0) ? 1 : -1;
            float minor = sub.Determinant();
            det += this->m[0][i] * direction * minor;
        }
        return det;
    }


    /**
     * @brief 伴随矩阵
     *
     * @return
     */
    Matrix Adjugate() const
    {
        if (this->_row != this->_column)
            throw "Matrix must be square to compute determinant";
        Matrix adj(this->_row, this->_column);
        for (int i = 0; i < this->_row; i++)
        {
            for (int j = 0; j < this->_column; j++)
            {
                Matrix sub = this->Submatrix(i, j);
                adj.m[j][i] = ((i + j) % 2 == 0) ? sub.Determinant() : -sub.Determinant();
            }
        }
        return adj;
    }


    /**
     * @brief 逆矩阵
     *
     * @return
     */
    Matrix Inverse() const
    {
        if (this->_row != this->_column)
            throw "Matrix must be square to compute determinant";
        Matrix adj = this->Adjugate();
        float det = this->Determinant();
        if (det == 0)
            throw "Matrix is singular and cannot be inverted";
        Matrix inv(this->_row, this->_column);
        for (int i = 0; i < this->_row; i++)
            for (int j = 0; j < this->_column; j++)
                inv.m[i][j] = adj.m[i][j] / det;
        return inv;
    }
};

#endif  // !M_MATRIX_H
