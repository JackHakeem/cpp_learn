
#include <string.h>
#include <stdio.h>


int ff(char[] s)
{
	printf("%d\n", sizeof(s));
	return 0;
}

int main()
{
	char szBuff[1024] = {0};

	printf("sizeof %d\n", sizeof(szBuff));

	printf("strlen %d\n", strlen(szBuff));

	ff(szBuff);
	return 0; 


}

