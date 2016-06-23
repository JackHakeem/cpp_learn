#include "socket/network/GameServerSocket.h"
#include "SCMD17F.h"
#include "view/crystal/CrystalMediator.h"
#include "view/login/LoginMediator.h"
#include "manager/GlobalManage.h"

bool	SCMD17F::Read()
{
	int16 SCMD17FNodeNum = readShort();
	for(  int k = 0; k < (int)SCMD17FNodeNum; k++  )
	{

		SCMD17FNode newnode;
		newnode.a_type = readByte();
		newnode.b_incd = readByte();
		newnode.c_time = readInt();
		a_cd.push_back(newnode);
	}


	return true;
}

int32 	SCMD17F::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD17FHandler::Execute(this) ;
}


uint32 SCMD17FHandler::Execute( SCMD17F* pPacket )
{
	if (!pPacket) return 1;
	// custom CD
	
	LoginMediator* loginMediator = (LoginMediator*)g_pFacade->retrieveMediator(AppFacade_LOGIN_MEDIATOR);
	if ( loginMediator )
		loginMediator->initCD( pPacket );

	// crystal CD
	CrystalMediator * pCrysMediator = (CrystalMediator *)g_pFacade->retrieveMediator(AppFacade_CRYSTAL_PROXY_CHANGE);
	if ( pCrysMediator )
		pCrysMediator->initCDList((char *)pPacket);

	g_pGlobalManage->loadOneProgress( 2 );
	return 0;
}