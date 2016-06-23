#include "CCMD162.h"

bool CCMD162::Write()
{
	writeByte(c_oldSit);
	writeByte(d_newSit);
	return true;
}