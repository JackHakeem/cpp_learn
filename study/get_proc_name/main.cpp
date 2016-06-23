


#include <libgen.h>
#include <stdio.h>




int main(int argc, char* argv[])
{
	printf("%s\n", argv[0]);

	printf("%s\n", basename(argv[0]));


	return 0;



}




