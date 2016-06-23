#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;


int main(int argc, char* argv[])
{
    int a = atoi(argv[1]);
	switch(a)
	{
	case 1:
		cout<<1<<endl;
		break;
	case 2:
	case 3:
	default:
		cout<<"other"<<endl;
	
	}
	
	return 0;
}



