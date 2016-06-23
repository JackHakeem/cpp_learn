#include "CCMD178.h"

bool CCMD178::Write()
{
	writeShort(a_shopid);
	writeShort(b_goodid);
	return true;
}