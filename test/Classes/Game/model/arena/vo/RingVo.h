#ifndef _RINGVO_H_
#define _RINGVO_H_

class RingVo
{
public:
	RingVo()
	{
		accountId = 0;
		roleId = 0;
		crystalLev = 0;
		pvpRankId = 0;
		pvpRankType = 0;
		awardNum = 0;
		std::string roleName = "";
	}

	int32 accountId;		//账号ID
	int32 roleId;			//佣兵原型ID
	int32 crystalLev;		//水晶等级
	int32 pvpRankId;		//擂台级别
	int32 pvpRankType;		//擂台类型
	int32 awardNum;			//奖励数量
	std::string roleName;	//角色名
};

#endif
