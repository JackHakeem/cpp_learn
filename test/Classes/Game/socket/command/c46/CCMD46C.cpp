#include "CCMD46C.h"

bool	CCMD46C::Write()
{
	writeInt(a_xhtype);
	return true;
}