#include "SCMD183.h"
#include "view/crystal/CrystalMediator.h"
#include "manager/CDManage.h"

bool SCMD183::Read()
{
	a_state = readByte();
	b_type = readByte();

	return true;
}


int32 	SCMD183::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD183Handler::Execute(this) ;
}


uint32 SCMD183Handler::Execute(SCMD183* pPacket)
{
	if (!pPacket) return 1;

	//add code here
	CDManage::Instance()->clearCD(pPacket->b_type, pPacket->a_state);


	CrystalMediator * pCrysMediator = (CrystalMediator *)g_pFacade->retrieveMediator(AppFacade_CRYSTAL_PROXY_CHANGE);
	if (pCrysMediator)
	{
		pCrysMediator->respClearCD((char *)pPacket);
	}
	
	return 0;
}