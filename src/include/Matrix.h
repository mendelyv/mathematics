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


    float Determinant()
    {
        if (this->_row != this->_column)
            return 0;
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
    Matrix* Adjugate()
    {
        if (this->_row != this->_column)
            return nullptr;
        Matrix* adj = new Matrix(this->_row, this->_column);
        for (int i = 0; i < this->_row; i++)
        {
            for (int j = 0; j < this->_column; j++)
            {
                Matrix sub = this->Submatrix(i, j);
                adj->m[j][i] = ((i + j) % 2 == 0) ? sub.Determinant() : -sub.Determinant();
            }
        }
        return adj;
    }


    /**
     * @brief 逆矩阵
     *
     * @return 
     */
    Matrix* Inverse()
    {
        if (this->_row != this->_column)
            return nullptr;
        Matrix* adj = this->Adjugate();
        float det = this->Determinant();
        if (det == 0)
            return nullptr;
        Matrix* inv = new Matrix(this->_row, this->_column);
        for (int i = 0; i < this->_row; i++)
            for (int j = 0; j < this->_column; j++)
                inv->m[i][j] = adj->m[i][j] / det;
        return inv;
    }
};

#endif  // !M_MATRIX_H
