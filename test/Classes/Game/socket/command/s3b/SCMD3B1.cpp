#include "SCMD3B1.h"
#include "model/battle/FightProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/scene/SceneListenerMediator.h"
#include "manager/GlobalManage.h"

int32 SCMD3B1::Execute()
{
	if(!Read())
	{
		return 1;
	}

	return SCMD3B1Handler::Execute(this);
}

bool SCMD3B1::Read()
{
	_battleId1 = readInt();
	_battleId2 = readInt();
	return true;
}

uint32 SCMD3B1Handler::Execute( SCMD3B1 *pPacket )
{
	if(!pPacket)
	{
		return 1;
	}

	FightProxy *pFightProxy = (FightProxy *) g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
	if(!pFightProxy)
		return 0;

	pFightProxy->battleReport(pPacket);
    CCLog("kevinmark0811 SCMD3B1");
	/*pFightProxy->showProcess();
	pFightProxy->setFightLayer();

	SceneListenerMediator* md = (SceneListenerMediator*)g_pFacade->retrieveMediator(AppFacade_SCENELISTENER_MEDIATOR);
	md->pveFightStart(pFightProxy->getPVEData());
*/

	//if (pFightProxy->getIsCanPlay())
	//{
	//	pFightProxy->fightStart();
	//}

	//if(pFightProxy->_callCount < 1)
	//{
	//	pFightProxy->_callCount ++;
	//}
	//else
	//{
	//	pFightProxy->_callCount = 0;
	//	if (g_pGlobalManage->_isInFight == false)
	//	{
	//		pFightProxy->fightStart();
	//	}
	//}
	return 0;
}
