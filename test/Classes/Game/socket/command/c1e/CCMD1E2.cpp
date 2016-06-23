#include "CCMD1E2.h"

bool CCMD1E2::Write()
{
	writeByte(a_type);
	writeByte(b_lev);
	writeByte(c_isGold);
	return true;
}

