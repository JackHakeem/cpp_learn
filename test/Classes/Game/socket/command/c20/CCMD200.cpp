#include "CCMD200.h"


bool CCMD200::Write()
{
	 writeShort(a_page);

	return true;
}
