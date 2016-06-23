#include "CCMD170.h"

bool CCMD170::Write()
{
	writeUint(a_figureId);
	writeByte(b_sitGrid);
	return true;
}