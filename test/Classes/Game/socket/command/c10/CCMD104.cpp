#include "CCMD104.h"

bool CCMD104::Write()
{
	writeString(a_account.c_str());
	writeString(b_roleName.c_str());
	writeShort(c_roleId);
	writeShort(d_accid);

	return true;
}