#include "CCMD156.h"

bool CCMD156::Write()
{
	writeByte(_type);
	writeShort(_id);
	return true;
}
