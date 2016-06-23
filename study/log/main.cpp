
#include <unistd.h>
#include <stdio.h>
#include "logger.h"

using namespace std;

int main()
{
	cc::g_logger.SetLogPath("./");

	cc::LogDebug("xxx", "hello here i am. %s", "master");
	
	for ( int i=0; i<100; ++i)
	{
		sleep(60);
		cc::LogDebug("for", "i=%d", i);
		printf("i=%d\n",i);
	}
	//sleep(1000*1000);
	return 0;


}



