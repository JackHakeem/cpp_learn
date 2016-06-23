#include "CCMD208.h"


bool CCMD208::Write()
{
	writeString(a_name.c_str());

	return true;
}
