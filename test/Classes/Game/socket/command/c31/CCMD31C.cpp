#include "CCMD31C.h"


bool CCMD31C::Write()
{
	writeUint(a_figureId);
	return true;
}
