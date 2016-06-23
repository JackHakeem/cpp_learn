#include "CCMD1A0.h"


bool CCMD1A0::Write()
{
	writeByte(a_mailType);
	writeShort(b_startNum);
	writeShort(c_mailNum);

	return true;
}
