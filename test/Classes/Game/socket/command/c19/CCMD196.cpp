#include "CCMD196.h"


bool CCMD196::Write()
{
	writeString(a_name.c_str());
	writeString(b_content.c_str());
	writeString(c_data.c_str());

	return true;
}
