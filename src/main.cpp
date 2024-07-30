#include "Matrix.h"
#include "include/Vector4.h"
#include <stdio.h>

void VectorTest()
{
    Vector4 vec(1, 2, 0.5f, 3);
    printf("initial vector : \n");
    vec.Print();
    printf("initial vector length : %f \n", vec.Length());

    int scale = 2;
    printf("vector scale by %d : \n", scale);
    vec.Scale(2);
    vec.Print();

    float data2[] = { 2.2f, 1, 0.3f, 1 };
    Vector vec2(4, data2);
    printf("initial vector2 : \n");
    vec2.Print();
    printf("vector add vector2 : \n");
    Vector::Add(vec, vec2);

    Vector4* vec3 = new Vector4(2.2f, 1, 0.3f, 1);
    printf("initial vector3 : \n");
    vec3->Print();
    printf("vector sub vector3 : \n");
    Vector::Subtract(vec, *vec3);
    vec.Print();

    vec3->Normalize();
    printf("vector3 normalize : \n");
    vec3->Print();
    printf("vector normalized length : %f \n", vec3->Length());

    printf("vector dot product with vector2 : %f \n", Vector4::DotProduct(vec, vec2));
    Vector4* crossVec = new Vector4(1, 3, 4, 0);
    Vector4* crossVec2 = new Vector4(2, -5, 8, 0);
    Vector4* crossRes = new Vector4();
    Vector4::CrossProduct(*crossRes, *crossVec, *crossVec2);
    printf("crossVec x crossVec2 : \n");
    crossRes->Print();

    delete vec3;
    delete crossVec;
    delete crossVec2;
    delete crossRes;
}

void MatrixTest()
{
    // clang-format off
    float data[] = {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f,
        10.0f, 11.0f, 12.0f,
    };
    // clang-format on
    Matrix mat(4, 3);
    mat.SetValuesFromArray(data);
    printf("initial mat : \n");
    mat.Print();
    printf("mat transpose : \n");
    mat.Transpose();
    mat.Print();
    // clang-format off
    float dataMultA[] = {
        1, -5, 3,
        0, -2, 6,
        7, 2, -4,
    };
    // clang-format on
    Matrix matA(3, 3);
    printf("inital matA : \n");
    matA.SetValuesFromArray(dataMultA);
    matA.Print();
    // clang-format off
    float dataMultB[] = {
        -8, 6, 1,
        7, 0, -3,
        2, 4, 5,
    };
    // clang-format on
    Matrix matB(3, 3);
    matB.SetValuesFromArray(dataMultB);
    printf("inital matB : \n");
    matB.Print();
    printf("matA x matB : \n");
    Matrix matABres = Matrix::Multiply(matA, matB);
    matABres.Print();
    // clang-format off
    float dataC[] = {
         -4, -3, 3 ,
         0, 2, -2 ,
         1, 4, -1 ,
    };
    // clang-format on
    Matrix matC(3, 3);
    matC.SetValuesFromArray(dataC);
    printf("inital matC : \n");
    matC.Print();
    printf("matC submatrix: \n");
    matC.Submatrix(0, 1).Print();
    printf("matC determinant : %f \n", matC.Determinant());
    printf("matC adjugate : \n");
    matC.Adjugate().Print();
    printf("matC inverse : \n");
    matC.Inverse().Print();
    printf("matC x inverse matC : \n");
    Matrix::Multiply(matC, matC.Inverse()).Print();
}

int main()
{
    VectorTest();
    // MatrixTest();
}
