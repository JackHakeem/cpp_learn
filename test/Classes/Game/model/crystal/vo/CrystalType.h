#ifndef _CrystalType_H_
#define _CrystalType_H_

#include "BaseType.h"
#include "view/crystal/CrystalMediator.h"

//const  uint32 CRYSTALS[CrystalType::CRYSTAL_NUM]={31,35,32,36,33,34,37,44,41,43,39,38,45,42,40};
//const  uint32 CRYSTALS[CrystalType::CRYSTAL_NUM]={35,32,36,33,34,37,44,41,43,39,38,45,42};
const  uint32 CRYSTALS[]={35,32,36,33,37,39,38,45,42};

//const int LEVEL[] = {0,1,9,11,15,17,36,40,42,45,50,55,101,102,999};
//const int LEVEL[] = {1,9,11,15,17,36,40,42,45,50,55,101,102};
const int LEVEL[] = {1,9,11,15,36,50,55,101,102};

class CrystalType
{
public:
	CrystalType();
	virtual ~CrystalType();

public:
	static const uint32 MAX_LEVEL = 120;			// crystal max level
	static const uint32 CRYSTAL_NUM = 9;		// max numbers
public:

	enum
	{
		CRYSTAL_MAIN		= 31,
		CRYSTAL_FENG	    = 32,
		CRYSTAL_SHUI		= 33,
		CRYSTAL_YOU		= 34,
		CRYSTAL_HUO		= 35,
		CRYSTAL_TU		= 36,
		CRYSTAL_YUN		= 37,
		CRYSTAL_YAN		= 38,
		CRYSTAL_MOHUA		= 39,
		CRYSTAL_MING2		= 40,
		CRYSTAL_SHANG		= 41,
		CRYSTAL_YAN2		= 42,
		CRYSTAL_TIANFU	= 43,
		CRYSTAL_KUANG		= 44,
		CRYSTAL_GUI		= 45,

	};

	uint32 getIndex(uint32 id);


};

 
#endif

