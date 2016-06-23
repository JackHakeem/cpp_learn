#include "CCMD171.h"

bool CCMD171::Write()
{
	writeUint(a_figureId);
	writeByte(b_sitGrid);
	writeByte(c_bagGrid);
	return true;
}