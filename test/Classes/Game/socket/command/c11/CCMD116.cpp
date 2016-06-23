#include "CCMD116.h"

bool CCMD116::Write()
{
	writeShort(triggerId);
	return true;
}