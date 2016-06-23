#ifndef _ARENADAREVO_H_
#define _ARENADAREVO_H_

#include "BaseType.h"

class ArenaDareVo
{
public:
	ArenaDareVo()
	{
		accountId = 0;
		crystalLev = 0;
		roleId = 0;
		rankings = 0;
		std::string roleName = "";
		threat = 0;
	}

	int32 accountId;		//账号ID
	int32 crystalLev;		//水晶等级
	int32 roleId;			//角色原型ID
	int32 rankings;			//排位等级
	std::string roleName;	//角色名
	int32 threat;			// 威胁度		 
};

#endif
