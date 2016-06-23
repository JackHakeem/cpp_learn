#include "CCMD16B.h"

bool CCMD16B::Write()
{
	writeByte(a_bagType);
	writeByte(b_sitGrid);
	return true;
}