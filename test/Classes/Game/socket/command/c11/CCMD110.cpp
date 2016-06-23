#include "CCMD110.h"

bool CCMD110::Write()
{
	std::vector<CCMD110Node>::iterator iter = a_path.begin();
	int16 size = (int16)a_path.size();
	writeShort(size);
	for(; iter != a_path.end(); ++iter)
	{
		writeShort(iter->a_x);
		writeShort(iter->b_y);
	}

	return true;
}