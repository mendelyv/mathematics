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
    ~Matrix()
    {
        this->Destroy();
    }


    const int row()
    {
        return this->_row;
    }
    const int column()
    {
        return this->_column;
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
        for (int i = 0; i < this->_row; i++)
        {
            delete[] this->m[i];
            this->m[i] = nullptr;
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


    Matrix* Clone()
    {
        Matrix* _clone = new Matrix(this->_row, this->_column);
        for (int i = 0; i < this->_row; i++)
            for (int j = 0; j < this->_column; j++)
                _clone->m[i][j] = this->m[i][j];
        return _clone;
    }


    /**
     * @brief 矩阵转置
     */
    void Transpose()
    {
        Matrix* temp = this->Clone();
        this->Destroy();
        int row = temp->_column;
        int column = temp->_row;
        this->Init(row, column);
        for (int i = 0; i < temp->_row; i++)
            for (int j = 0; j < temp->_column; j++)
                this->m[j][i] = temp->m[i][j];
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
    void Add(Matrix* datas)
    {
        if (datas->row() != this->_row && datas->column() != this->_column)
            return;
        for (int i = 0; i < this->_row; i++)
            for (int j = 0; j < this->_column; j++)
                this->m[i][j] += datas->m[i][j];
    }


    /**
     * @brief 减一个矩阵
     *
     * @param datas
     */
    void Subtract(Matrix* datas)
    {
        if (datas->row() != this->_row && datas->column() != this->_column)
            return;
        for (int i = 0; i < this->_row; i++)
            for (int j = 0; j < this->_column; j++)
                this->m[i][j] -= datas->m[i][j];
    }


    /**
     * @brief 矩阵相乘
     *
     * @param a
     * @param b
     * @return
     */
    static Matrix* Multiply(Matrix* a, Matrix* b)
    {
        if (a->column() != b->row())
            return nullptr;
        Matrix* res = new Matrix(a->row(), b->column());
        for (int i = 0; i < a->row(); i++)
            for (int j = 0; j < b->column(); j++)
                for (int k = 0; k < a->column(); k++)
                    res->m[i][j] += a->m[i][k] * b->m[k][j];
        return res;
    }


    /**
     * @brief 子矩阵
     *
     * @param row
     * @param column
     * @return
     */
    Matrix* Submatrix(int row, int column)
    {
        Matrix* res = new Matrix(this->_row - 1, this->_column - 1);
        for (int i = 0; i < this->_row; i++)
        {
            if (i == row)
                continue;
            for (int j = 0; j < this->_column; j++)
            {
                if (j == column)
                    continue;
                int resRow = i > row ? i - 1 : i;
                int resCol = j > column ? j - 1 : j;
                res->m[resRow][resCol] = this->m[i][j];
            }
        }
        return res;
    }
};

#endif  // !M_MATRIX_H
