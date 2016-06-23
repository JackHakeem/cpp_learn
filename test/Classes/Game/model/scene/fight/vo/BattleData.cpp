#include "BattleData.h"
#include "view/fight/interfaces/BaseAction.h"

BattleData::BattleData()
{
	_fightRet = NULL;
	_fightAward = NULL;
	type= 0;
	id = 0;

	formation = 0;
	oppositeFormation = 0;
	procid = 0;

	_tailStoryAction = 0;

}


void dispose()
{
}

BattleData::~BattleData()
{
    std::vector<BaseAction*>::iterator callBackIt;
    for(callBackIt = _callbacks.begin();
        callBackIt != _callbacks.end();
        ++ callBackIt)
    {
        CC_SAFE_DELETE(*callBackIt);
    }
}