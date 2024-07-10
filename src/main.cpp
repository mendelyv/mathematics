#include "include/Matrix4x4.h"
#include "include/Vector4.h"
#include <stdio.h>

void VectorTest()
{
    Vector4* vec = new Vector4(1, 2, 0.5f, 3);
    printf("initial vector : \n");
    vec->Print();
    printf("initial vector length : %f \n", vec->Length());

    int scale = 2;
    printf("vector scale by %d : \n", scale);
    Vector4::Scale(vec, 2);
    vec->Print();

    Vector4* vec2 = new Vector4(2.2f, 1, 0.3f, 1);
    printf("initial vector2 : \n");
    vec2->Print();
    printf("vector add vector2 : \n");
    Vector4::Add(vec, vec2).Print();

    Vector4* vec3 = new Vector4(2.2f, 1, 0.3f, 1);
    printf("initial vector3 : \n");
    vec3->Print();
    printf("vector sub vector3 : \n");
    Vector4::Sub(vec, vec, vec3);
    vec->Print();

    vec3->Normalize();
    printf("vector3 normalize : \n");
    vec3->Print();
    printf("vector normalized length : %f \n", vec3->Length());

    printf("vector dot product with vector2 : %f \n", Vector4::DotProduct(vec, vec2));
    Vector4* crossVec = new Vector4(1, 3, 4, 0);
    Vector4* crossVec2 = new Vector4(2, -5, 8, 0);
    Vector4* crossRes = new Vector4();
    Vector4::CrossProduct(crossRes, crossVec, crossVec2);
    printf("crossVec x crossVec2 : ");
    crossRes->Print();

    delete vec;
    delete vec2;
    delete vec3;
}

void MatrixTest()
{
    float data[4][4] = {
        { 1.0f, 2.0f, 3.0f, 4.0f },
        { 5.0f, 6.0f, 7.0f, 8.0f },
        { 9.0f, 10.0f, 11.0f, 12.0f },
        { 13.0f, 14.0f, 15.0f, 16.0f },
    };
    Matrix4x4* mat = new Matrix4x4(data);
    printf("initial matrix : \n");
    mat->Print();
    printf("matrix transpose : \n");
    mat->Transpose();
    mat->Print();
    float scale = 2.0f;
    printf("matrix scale by %f : \n", scale);
    mat->Scale(scale);
    mat->Print();

    float matMulDataA[4][4] = {
        { 1, -5, 3, 0 },
        { 0, -2, 6, 0 },
        { 7, 2, -4, 0 },
        { 0, 0, 0, 0 },
    };
    Matrix4x4* matMulA = new Matrix4x4(matMulDataA);
    float matMulDataB[4][4] = {
        { -8, 6, 1, 0 },
        { 7, 0, -3, 0 },
        { 2, 4, 5, 0 },
        { 0, 0, 0, 0 },
    };
    Matrix4x4* matMulB = new Matrix4x4(matMulDataB);
    printf("matMulA : \n");
    matMulA->Print();
    printf("matMulB : \n");
    matMulB->Print();
    printf("matMulA x matMulB : \n");
    Matrix4x4::Multiply(matMulA, matMulB).Print();
}

int main()
{
    // VectorTest();
    MatrixTest();
}
