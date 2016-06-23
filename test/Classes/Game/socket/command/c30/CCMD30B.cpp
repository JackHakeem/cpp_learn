#include "CCMD30B.h"

bool CCMD30B::Write()
{

	writeInt(a_figureId);

	return true;
}

