#include "CCMD35B.h"

bool CCMD35B::Write()
{
	writeInt( a_playerId );
	writeByte( b_type );
	return true;
}
