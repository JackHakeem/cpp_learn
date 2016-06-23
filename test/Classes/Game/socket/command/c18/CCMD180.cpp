#include "CCMD180.h"


bool CCMD180::Write()
{
	writeByte( a_typeSit );
	writeByte( b_sit );
	writeByte( c_isVIP );
	writeByte( d_strengType );
	writeByte( e_probability );
	writeInt( f_roleID );

	return true;
}
