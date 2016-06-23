#include "CCMD2A4.h"

bool CCMD2A4::Write()
{
	writeInt(a_mercId);
	writeByte(b_useItem);

	return true;
}