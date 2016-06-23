#include "SCMD153.h"

int32 SCMD153::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return 0;
}


bool SCMD153::Read()
{
	// ...未完成，委托任务
	return true;
}
