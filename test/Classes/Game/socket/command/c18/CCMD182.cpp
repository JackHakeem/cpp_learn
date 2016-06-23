#include "CCMD182.h"

bool CCMD182::Write()
{
	writeByte( a_type );
	writeByte( b_free );
	return true;
}
