#include <stdio.h>
#include <inttypes.h>


using namespace std;

struct TCmd
{
	TCmd() {}
	TCmd(int16_t a){ S_un.cmd = a; }
	

	union 
	{
		int16_t cmd;
		struct { int v : 12 ; unsigned t : 4;} split;
	}S_un;
	
	TCmd & operator=(const TCmd &a)
	{
		this->S_un.cmd = a.S_un.cmd;
		return *this;
	}
	
	TCmd & operator=(const int16_t &a) 
	{
		this->S_un.cmd = a;
		return *this;
	}
};

#define p_cmd		S_un.cmd
#define p_type		S_un.split.t
#define p_value		S_un.split.v


int main()
{
	int16_t cmd = 0x4012;

	TCmd c = cmd;
	//c.p_cmd = cmd;

	if ( c.p_type == 1 )
		printf("type == 1\n");
	else 
		printf("type != 1, %d\n", c.p_type);		
	
	printf("c = %x\n", c.p_cmd);
	printf("value = %d\n", c.p_value);


}


