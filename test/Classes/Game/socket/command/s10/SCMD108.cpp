#include "SCMD108.h"
#include "manager/LangManager.h"
#include "manager/GlobalManage.h"

bool SCMD108::Read()
{
	a_errCode = readShort();

	return true;
}


int32 	SCMD108::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD108Handler::Execute(this) ;
}


uint32 SCMD108Handler::Execute(SCMD108* pPacket)
{
	if (!pPacket) return 1;

	//add code here
//	CDManage::Instance()->serverTimer( pPacket->a_time );
	char str[30];
	sprintf(str, "S%d", pPacket->a_errCode);
	LangManager::msgShow(str);

//Begin chenjian 20121019  report error return
	if (pPacket->a_errCode == 260)
	{
		if (g_pGlobalManage)
			g_pGlobalManage->isReport = false;
	}
//End chenjian 20121019
	return 0;
}