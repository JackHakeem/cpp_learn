#ifndef _SCMD285NODE_H_
#define _SCMD285NODE_H_

#include "BaseType.h"

struct SCMD285Node
{
	SCMD285Node()
	{
		a_rank = 0;
		b_playerId = 0;
		c_playerName = "";
		d_level = 0;
	}
	int16 a_rank;
	int32 b_playerId;
	std::string c_playerName;
	uint32 d_level;
};
#endif