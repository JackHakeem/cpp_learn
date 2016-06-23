#include "CrystalType.h"

CrystalType::CrystalType()
{

}


CrystalType::~CrystalType()
{

}

uint32 CrystalType::getIndex( uint32 id )
{
	for(uint32 i=0; i< CrystalType::CRYSTAL_NUM; i++)
	{
		if(CRYSTALS[i] == id) return i;
	}
	return -1;
}
