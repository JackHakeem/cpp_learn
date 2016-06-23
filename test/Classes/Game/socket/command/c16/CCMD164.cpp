#include "CCMD164.h"

bool CCMD164::Write()
{
	writeByte((unsigned char)0);
	return true;
}