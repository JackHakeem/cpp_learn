#include "CCMD21c.h"


bool CCMD21c::Write()
{
	int16 size = a_listNode.size();
	writeShort(size);
	std::list<CCMD21CNode>::iterator it; 
	for (it = a_listNode.begin(); it != a_listNode.end(); it++)
	{
		writeInt(it->a_recommendId);
	}
	return true;
}
