#include "CCMD159.h"


bool CCMD159::Write()
{
	writeByte(_type);
	writeShort(_id);
	return true;
}
