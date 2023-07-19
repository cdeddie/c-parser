#include <stdio.h>

int add(int x, int y)
{
    int z = x + y;
    return z;
}

int main()
{
    printf("x + y = %d\n", add(1, 2));
}