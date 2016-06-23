#include "CCMD1A8.h"


bool CCMD1A8::Write()
{
	writeUint(a_mailId);

	return true;
}
