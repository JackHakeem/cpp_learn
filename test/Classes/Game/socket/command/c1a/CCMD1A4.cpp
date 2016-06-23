#include "CCMD1A4.h"


bool CCMD1A4::Write()
{
	uint16 len = a_mailIdList.size();
	writeShort(len);
	std::list<uint>::iterator iter;
	for (iter = a_mailIdList.begin();iter != a_mailIdList.end();iter++)
	{
		writeUint(*iter);
	}
	return true;
}
