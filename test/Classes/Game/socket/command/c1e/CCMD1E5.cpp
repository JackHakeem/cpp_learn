#include "CCMD1E5.h"

bool CCMD1E5::Write()
{
	writeShort(a_goods.size());
	std::list<int16>::iterator it;
	for(it = a_goods.begin(); it != a_goods.end(); ++it)
	{
		writeShort(*it);
	}
	return true;
}

