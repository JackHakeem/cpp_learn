#include "CCMD1A6.h"


bool CCMD1A6::Write()
{
	writeString(a_recvName.c_str());
	writeString(b_mailTitle.c_str());
	writeString(c_mailContent.c_str());

	return true;
}
