#include "CCMD359.h"


bool CCMD359::Write()
{
	writeInt( a_playerId );
	writeByte( b_type );
	writeByte( c_mode );

	return true;
}
