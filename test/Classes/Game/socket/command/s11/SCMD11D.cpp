#include "SCMD11D.h"
#include "socket/network/GameServerSocket.h"
#include "view/scene/SceneListenerMediator.h"
#include "view/report/ReportMediator.h"
#include "manager/GlobalManage.h"
bool	SCMD11D::Read()
{

	a_mapId = readShort();
	b_mapStatus = readByte();
	c_isAward = readByte();
	int16 cnt = readShort();
	for(int16 i = 0; i < cnt; ++i)
	{
		SCMD11DNode node;
		node.a_process = readShort();
		node.b_starLev = readByte();
		d_finisheds.push_back(node);
	}

	cnt = readShort();
	for(int16 i = 0; i < cnt; ++i)
	{
		SCMD11DNode2 node;
		node.mgId = readShort();
		e_randMg.push_back(node);
	}
	
	return true;
}

int32 	SCMD11D::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD11DHandler::Execute(this) ;
}


uint32 SCMD11DHandler::Execute(SCMD11D* pPacket)
{
	if (!pPacket) return 1;
	
	SceneListenerMediator* md = 
		(SceneListenerMediator*)g_pFacade->retrieveMediator(AppFacade_SCENELISTENER_MEDIATOR);
	md->initProcess(pPacket);

	g_pGlobalManage->loadOneProgress( 2 );

	//Begin chenjian 20121013
	g_pReportMediator->updateReportData();
	//End chenjian 20121013
	return 0;
}