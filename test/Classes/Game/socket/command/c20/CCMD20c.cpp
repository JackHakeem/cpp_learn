#include "CCMD20c.h"


bool CCMD20c::Write()
{
	writeString(a_name.c_str());

	return true;
}
