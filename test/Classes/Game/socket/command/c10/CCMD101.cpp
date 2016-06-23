#include "CCMD101.h"

bool CCMD101::Write()
{
		writeInt(a_clientversion);
		writeString(b_account.c_str());
		writeByte(c_loginType);
		writeInt(d_times);
		writeString(e_flag.c_str());
		return true;
}