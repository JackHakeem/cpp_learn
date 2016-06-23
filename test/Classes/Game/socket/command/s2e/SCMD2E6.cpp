#include "SCMD2E6.h"
#include "socket/network/GameServerSocket.h"
#include "view/silverMine/SilverMineMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool	SCMD2E6::Read()
{
	a_intime = readUbyte();
	b_actionCD = readUint();
	c_inActionCD = readUbyte();
	d_digCD = readUint();
	e_inDigCD = readUbyte();
	f_mineId = readUint();
	g_onMine = readUint();
	h_attPlus = readUint();
	i_defPlus = readUint();
	j_token0 = readUbyte();
	k_token1 = readUbyte();
	l_silver = readUint();
	m_mojinshi = readByte();

	short SCMD2E6NodeNum = readShort();
	for (short i = 0; i < SCMD2E6NodeNum; i++)
	{
		SCMD2E6Node newnode;
		newnode.a_mineId = readUint();
		newnode.b_online = readUint();
		newnode.c_mineType = readUbyte();
		newnode.d_isDouble = readUbyte();

		m_mineArr.push_back(newnode);
	}
	return true;
}

int32 	SCMD2E6::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2E6Handler::Execute(this) ;
}


uint32 SCMD2E6Handler::Execute(SCMD2E6* pPacket)
{
	if (!pPacket) return 1;

	SilverMineMediator * pSilverMineMediator = (SilverMineMediator*)g_pFacade->retrieveMediator(AppFacade_SilverMine_PROXY_CHANGE);
	if (pSilverMineMediator)
		pSilverMineMediator->handleInfoList(pPacket);
	
	return 0;
}