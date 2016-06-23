#include "CCMD25B.h"

bool CCMD25B::Write()
{
	writeByte(a_type);
    //writeBtye(b_lev);
	writeShort(c_begin);
    writeShort(d_end);

	return true;
}

