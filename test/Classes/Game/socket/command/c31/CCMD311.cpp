#include "CCMD311.h"


bool CCMD311::Write()
{
	writeShort(a_formationId);
	
	return true;
}
