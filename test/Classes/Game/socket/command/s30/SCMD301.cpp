#include "SCMD301.h"
#include "socket/network/GameServerSocket.h"
#include "view/recruit/RecruitMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "manager/GlobalManage.h"

bool	SCMD301::Read()
{
	count = readShort();
	a_mercenarys.clear();
	//int16 id = 0;
	SCMD301Node node;
	for(int i = 0; i < count; ++i)
	{
		node.a_mercenaryId = readInt();
		node.b_prototypeId = readShort();
		node.c_level = readByte();
		node.d_exp = readInt();
		node.e_strength = readShort();
		node.f_intellect = readShort();
		node.g_stamina = readShort();
		node.i_skill = readShort();
		node.j_reborn = readByte();
		node.k_maxHp = readInt();
		a_mercenarys.push_back(node);
	}

	return true;
}

int32 	SCMD301::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD301Handler::Execute(this) ;
}


uint32 SCMD301Handler::Execute(SCMD301* pPacket)
{
	if (!pPacket) return 1;

	RecruitMediator* pRecruitMediator = (RecruitMediator*)g_pFacade->retrieveMediator( AppFacade_RECRUIT_PROXY_CHANGE );
	if ( pRecruitMediator )
	{
		pRecruitMediator->dismissListListener( pPacket );
	}

	g_pGlobalManage->loadOneProgress( 2 );
	return 0;
}