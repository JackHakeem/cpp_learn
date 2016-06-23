

#include <iostream>

using namespace std;


int main(int argc, char* argv[])
{
	int a[5] = {0,1,2,3,4};

	int loop = 5;
	int i = 0;
	while(loop -- > 0)
	{
		//cout << a[i++] << endl;
	}
	
	if ( argc < 4)
	{	
		cout << "argc must lt than 4." << endl;
		return -1;
	}
	

	bool b1 = atoi(argv[1]) != 0 ? true : false;
	bool b2 = atoi(argv[2]) != 0 ? true : false;
	bool b3 = atoi(argv[3]) != 0 ? true : false;
	bool b4 = atoi(argv[4]) != 0 ? true : false;
	cout << b1 << endl;
	cout << b2 << endl;
	cout << b3 << endl;
	//cout << ( b1 ? "true" : "false") << endl;
	//if ( b1 ) { cout << "test" << endl; }
	if ( b1 && ( b2 || b3 ) || !b1 && b3 && b2 )	
		cout << "true" << endl;
	else
		cout << "false" << endl;
	return 0;
}



