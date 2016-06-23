#include <stdio.h>

int main()
{
   int a[5]={1,2,3,4,5};
  	printf("sizeof a is %d\n", sizeof(a)/sizeof(a[0])); 
	for(int i=0; i<5; ++i)
	{
		printf("%d\n", (&a+i));
	}

	int *p=(int *)(&a+1);
   printf("%d",*(p-1));
   return 0;
}

