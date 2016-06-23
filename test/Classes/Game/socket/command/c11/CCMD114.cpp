#include "CCMD114.h"

bool CCMD114::Write()
{
	writeShort(a_x);
	writeShort(b_y);
	return true;
}