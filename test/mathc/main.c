#include <stdio.h>
#include <math.h>

int main(void)
{
	double ang1,result;
	ang1 = 1;
	result = acos(cos(ang1));
	printf("acos(%lf) is %lf\n",cos(ang1),result);
	ang1 = 3.14;
	result = acos(cos(ang1));
	printf("acos(%lf) is %lf\n",cos(ang1),result);


	int x=3,y=3;

	result = atan((double)y * 1.0/x)/M_PI;
	printf("atan(%lf) is %lfM_PI\n",y*1.0/x,result);


	return 0;

}
