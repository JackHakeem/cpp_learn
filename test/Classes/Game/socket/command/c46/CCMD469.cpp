#include "CCMD469.h"

bool	CCMD469::Write()
{
	writeByte(a_fromPosType);
	writeByte(b_fromPos);
	writeByte(c_toPosType);
	writeByte(d_toPos);
	writeUint(e_roldId);

	return true;
}