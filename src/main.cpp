#include <stdio.h>
#include "include/Vector4.h"

int main()
{
    Vector4* vec = new Vector4(1, 2, 0.5f, 3);
    printf("initial vector : \n");
    vec->Print();

    int scale = 2;
    printf("vector scale by %d : \n", scale);
    Vector4::Scale(vec, 2);
    vec->Print();
}
