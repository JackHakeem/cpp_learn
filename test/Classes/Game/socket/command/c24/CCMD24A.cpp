#include "CCMD24A.h"

bool CCMD24A::Write()
{
	writeString(a_account.c_str());
	writeString(b_role.c_str());

	return true;
}