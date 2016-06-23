#include "CCMD19C.h"


bool CCMD19C::Write()
{
	writeByte(a_type);
	writeUint(b_id);

	return true;
}
