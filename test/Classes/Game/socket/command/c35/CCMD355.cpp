#include "CCMD355.h"


bool CCMD355::Write()
{
	writeInt( a_playerId );
	writeByte( b_mode );
	return true;
}