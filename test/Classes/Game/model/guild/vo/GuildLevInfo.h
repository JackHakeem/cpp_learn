#ifndef _GuildLevInfo_H_
#define _GuildLevInfo_H_

#include "BaseType.h"

class GuildLevInfo
{
public:
	GuildLevInfo()
	{
		lev = 0;
		needGold = 0;
		incMember = 0;
	}
	~GuildLevInfo(){}
public:
	uint lev;				//公会当前等级
	uint needGold;			//升级费用
	uint incMember;			//升级增加的人数上限
};

#endif