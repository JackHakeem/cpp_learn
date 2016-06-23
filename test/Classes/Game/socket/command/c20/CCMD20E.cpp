#include "CCMD20E.h"


bool CCMD20E::Write()
{
	writeString(a_name.c_str());

	return true;
}
