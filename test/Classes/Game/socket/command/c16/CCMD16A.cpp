#include "CCMD16A.h"

bool CCMD16A::Write()
{
	writeByte(a_type);
	writeByte(b_sitGrid);
	return true;
}