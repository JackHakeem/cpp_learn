#include "CCMD25D.h"

bool CCMD25D::Write()
{
    writeByte(a_type);
    writeInt(b_playerId);

	return true;
}
