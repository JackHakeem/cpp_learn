#include "SCMD29E.h"
#include "control/vip/VipCommand.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "model/vip/VipProxy.h"
#include "manager/GlobalManage.h"


bool SCMD29E::Read()
{
	this->a_num = readInt();
	return true;
}

int32 SCMD29E::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD29EHandler::Execute(this);
}

uint32 SCMD29EHandler::Execute( SCMD29E* pPacket )
{
	/*VipCommand *pVipCommand = (VipCommand *) g_pFacade->retrieveController(AppFacade_VIP_COMMAND);
	if(pVipCommand)
	{
		pVipCommand->execute(VipCommand::REWARD_UPDATE, (char *) pPacket);
	}*/

	VipProxy *pVipProxy = (VipProxy *) g_pFacade->retrieveProxy(AppFacade_VIP_PROXY);
	pVipProxy->updateVipReward(pPacket);
	
	g_pGlobalManage->loadOneProgress( 2 );
	return 0;
}
