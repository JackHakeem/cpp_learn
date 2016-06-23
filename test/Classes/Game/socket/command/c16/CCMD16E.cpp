#include "CCMD16E.h"

bool CCMD16E::Write()
{
	writeByte( a_locationType );
	writeByte( b_sitNum );
	writeUint( c_roleId );

	return true;
}

