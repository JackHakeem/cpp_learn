#include "CCMD31E.h"


bool CCMD31E::Write()
{
	writeUint(a_figureId);  
	writeByte(b_type);
	writeByte(c_useItem);
	return true;
}
