#include "CCMD448.h"

bool	CCMD448::Write()
{
	writeByte(a_MBType);
	return true;
}