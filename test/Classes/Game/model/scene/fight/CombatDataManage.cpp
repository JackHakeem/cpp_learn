#include "CombatDataManage.h"


void CombatDataManage::addFightReward( SCMD13D *pData )
{
	if(!pData)
		return;
	_rewardDic.insert(std::map<int, SCMD13D *>::value_type(pData->_sceneId, pData));
}

