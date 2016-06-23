#include "CCMD190.h"


bool CCMD190::Write()
{
	writeString(a_content.c_str());
	writeString(b_data.c_str());

	return true;
}
