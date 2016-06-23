#include "CCMD32C.h"


bool CCMD32C::Write()
{
	writeByte(a_reason);

	return true;
}