#include "CCMD210.h"


bool CCMD210::Write()
{
	writeString(a_name.c_str());

	return true;
}
