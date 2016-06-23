

#include <stdio.h>
#include <stdlib.h>

int main()
{
    char sz[12]={0};
    
    printf("%d\n", sizeof(sz));

    //int nLen = snprintf(sz, sizeof(sz)-1, "%s", "0123456789012345");

    int nLen = sprintf(sz, "%s", "0123456789012345");
    
    
    printf("%d\n", nLen);
    printf("%s\n", sz);
    return 0;
}
