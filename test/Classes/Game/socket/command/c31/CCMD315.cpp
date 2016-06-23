#include "CCMD315.h"


bool CCMD315::Write()
{
	writeShort(a_passiveId);

	return true;
}
