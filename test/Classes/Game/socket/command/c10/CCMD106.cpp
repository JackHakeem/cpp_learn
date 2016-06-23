#include "CCMD106.h"

bool CCMD106::Write()
{
	writeInt(a_accountId);
	writeInt(b_key);
	writeString(c_sn.c_str());
    //Doyang 20120814
    writeByte(1);
	return true;
}