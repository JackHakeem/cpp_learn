#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	char (*cc)[128] = new char[4][128];
	
	printf("cc size is %d\n", sizeof(cc) );
	
    memcpy(cc[0], "exp\0", 4);
	memcpy(cc[1], "sub\0", 4);
	memcpy(cc[2], "money\0", 6);
	memcpy(cc[3], "hello\0", 6);
	
	for ( int i=0; i<4; ++i)
	{
		printf("cc[%d] = %s\n", i, cc[i]);
	}	

	delete[] cc;
	//memset(cc, 0, 512);
	
	char fs[4][128] = {"exp", "sub", "money", "hello"};

	 for ( int i=0; i<4; ++i)
     {
         printf("cc[%d] = %s\n", i, fs[i]);
     }
	char **ppfs=fs;

	return 0;
}


