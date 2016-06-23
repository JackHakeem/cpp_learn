#include "CCMD467.h"

bool	CCMD467::Write()
{
	writeByte(a_bankPos);
	return true;
}