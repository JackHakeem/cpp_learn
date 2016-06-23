#include "CCMD154.h"


bool CCMD154::Write()
{
	writeByte(_type);
	writeShort(_id);
	return true;
}
