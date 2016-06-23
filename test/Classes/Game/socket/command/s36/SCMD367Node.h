#pragma once
/**
 * 银矿战玩家排名数组
	Uint8	排名（0-9）
	Uint32	玩家ID
	String	玩家姓名
	Uint32	采集银币数
 */
#include "BaseType.h"

struct SCMD367Node
{
	SCMD367Node()
	{
		a_rank = 0;
		b_playerId = 0;
		c_playerName = "";
		d_silver = 0;
	}
	int8 a_rank;
	uint32 b_playerId;
	std::string c_playerName;
	uint32 d_silver;
};