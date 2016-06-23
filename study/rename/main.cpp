#include <stdio.h>
int main(int argc,char **argv)
{
if(argc < 3)
{
printf("Usage: %s old_name new_name\n",argv[0]);
return -1;
}
printf("%s => %s\n", argv[1], argv[2]);
if(rename(argv[1], argv[2]) < 0 )
printf("error!\n");
else
printf("ok!\n");
return 0;
}
