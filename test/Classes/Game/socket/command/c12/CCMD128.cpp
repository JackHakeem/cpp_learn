#include "CCMD128.h"

bool CCMD128::Write()
{
    writeShort(a_mapID);

    return true;
}
