#include "CCMD17A.h"

bool CCMD17A::Write()
{
	writeShort(a_shopid);
	writeInt(b_sit);
	return true;
}