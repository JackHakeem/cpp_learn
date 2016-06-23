
#include "CCMD13B.h"

bool CCMD13B::Write()
{
	writeInt(a_accountId);
    return true;
}