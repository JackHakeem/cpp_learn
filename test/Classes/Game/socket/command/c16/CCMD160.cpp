#include "CCMD160.h"

bool CCMD160::Write()
{
	writeByte(a_oldSit);
	writeByte(b_newSit);
	return true;
}