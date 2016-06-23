#include "SCMD123.h"
#include "socket/network/GameServerSocket.h"
#include "view/login/LoginMediator.h"
#include "manager/GlobalManage.h"
bool	SCMD123::Read()
{
	int16 cnt = readShort();
	for(int16 i = 0; i < cnt; ++i)
	{
		SCMD123Node node;
		node.a_mapId = readShort();
		node.b_status = readByte();
		a_openMap.push_back(node);
	}
	
	return true;
}

int32 	SCMD123::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD123Handler::Execute(this) ;
}


uint32 SCMD123Handler::Execute(SCMD123* pPacket)
{
	if (!pPacket) return 1;
	
	LoginMediator* _mediator = (LoginMediator*)g_pFacade->retrieveMediator(AppFacade_LOGIN_MEDIATOR);
	_mediator->initScene(pPacket);

	g_pGlobalManage->loadOneProgress( 2 );
	return 0;
}