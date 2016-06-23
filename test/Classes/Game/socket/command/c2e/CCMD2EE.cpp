#include "CCMD2EE.h"

bool	CCMD2EE::Write()
{
	writeByte(a_type);
	writeUint(b_mineID);
	return true;
}