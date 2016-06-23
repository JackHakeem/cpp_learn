#include "CCMD115.h"

bool CCMD115::Write()
{
	writeShort(a_x);
	writeShort(b_y);
	return true;
}