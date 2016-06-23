#ifndef HLQS_MusicVo_H_
#define HLQS_MusicVo_H_

#include "BaseType.h"
USING_NS_CC;

class MusicVo
{
public:
	int mapId;
	int type;
	int musicId;

public: 
	MusicVo()
	{
		mapId = 0;
		type = 0;
		musicId = 0;
	}

	~MusicVo()
	{
		CCLog(".......................................");
		mapId = 0;
		type = 0;
		musicId = 0;
	}
};

#endif