#include "SCMD19F.h"
#include "view/crystal/CrystalMediator.h"
#include "manager/CDManage.h"
#include "CustomCD.h"
#include "manager/ViewManager.h"

bool SCMD19F::Read()
{
	a_type = readByte();
	b_cost = readShort();

	return true;
}


int32 	SCMD19F::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD19FHandler::Execute(this) ;
}


uint32 SCMD19FHandler::Execute(SCMD19F* pPacket)
{
	if (!pPacket) return 1;

	//add code here
	//CustomCD::clearCD
	CustomCD* pCustomCD = CDManage::Instance()->getCustomCD( pPacket->a_type );
	if ( pCustomCD )
	{
		pCustomCD->clearCD( pPacket );
	}

	// crystal buy CD
	CrystalMediator * pCrysMediator = (CrystalMediator *)g_pFacade->retrieveMediator(AppFacade_CRYSTAL_PROXY_CHANGE);
	if (pPacket->a_type >= CDManage::CRYSTAL_0 && pPacket->a_type <= CDManage::CRYSTAL_5)
	{
		pCrysMediator->respMoney((char *)pPacket);
	}

	return 0;
}