#include "CCMD119.h"

bool CCMD119::Write()
{
	writeShort(a_mapId);
	return true;
}