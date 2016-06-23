#include "CCMD15B.h"

bool CCMD15B::Write()
{
	writeByte(_type);
	writeShort(_id);
	return true;
}
