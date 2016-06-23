#include "CCMD20A.h"


bool CCMD20A::Write()
{
	writeString(a_delName.c_str());

	return true;
}
