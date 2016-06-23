#include "CCMD217.h"


bool CCMD217::Write()
{
	writeString(a_name.c_str());
	writeByte(b_type);
	return true;
}
