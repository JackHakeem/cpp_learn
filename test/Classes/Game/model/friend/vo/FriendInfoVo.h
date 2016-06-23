#pragma once

#include "BaseType.h"
#include "BlessInfo.h"

class FriendInfoVo
{
public:
	FriendInfoVo(){OF = 0;}

		/**角色原型ID*/
	uint32 avatarID;
		/**角色名称*/
	std::string name;
		/**命之水晶等级*/
	uint32 level;
		/**是否能进行祝福操作*/
	uint32 blessDisable;
		/**角色是否在线，0在线，1不在线*/
	uint32 OF;
	uint32 cloth;
	uint32 sex;
	int32 id;
	BlessInfoVo blessInfo;
};
