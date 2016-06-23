#include "CCMD313.h"


bool CCMD313::Write()
{
	writeShort(a_formationId);

	return true;
}
