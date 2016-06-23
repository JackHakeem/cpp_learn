#ifndef _COMBAT_DATA_MANAGE_H_
#define _COMBAT_DATA_MANAGE_H_
#include "socket/command/s13/SCMD13D.h"
#include "utils/Singleton.h"

class CombatDataManage : public Singleton<CombatDataManage>
{
public:
	CombatDataManage(){}
	~CombatDataManage(){}

	void addFightReward(SCMD13D *pData);
public:
	 std::map<int ,SCMD13D *> _rewardDic;

};
#endif