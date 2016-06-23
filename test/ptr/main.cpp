

#include <stdlib.h>
#include <stdio.h>

int a = 10;

int main()
{
    int *b = &a;
    *b = 9;
    printf("a=%d\n", a);
    return 0;
}

