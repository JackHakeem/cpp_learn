#include "CCMD192.h"


bool CCMD192::Write()
{
	writeString(a_content.c_str());
	writeString(b_data.c_str());

	return true;
}
