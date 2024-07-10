#include "include/Vector4.h"
#include <stdio.h>

int main()
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
