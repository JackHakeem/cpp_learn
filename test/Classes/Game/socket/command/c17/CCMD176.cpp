#include "CCMD176.h"

bool CCMD176::Write()
{
	writeByte(a_gridType);
	writeByte(b_number);
	return true;
}