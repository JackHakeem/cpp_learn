#include "SCMD35F.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/figure/FigureMediator.h"
#include "view/scene/SceneListenerMediator.h"

bool	SCMD35F::Read()
{
	a_id = readInt();
	b_maxHp = readInt();
	c_Dhp = readInt();
	d_DphsicsAttack = readInt();
	e_DmagicAttack = readInt();
	f_DphsicsDefend = readInt();
	g_DmagicDefend = readInt();
	h_str = readShort();
	i_int = readShort();
	j_sta = readShort();
	k_plusStr = readShort();
	l_plusInt = readShort();
	m_plusSta = readShort();
	n_sp_Str = readShort();
	o_sp_Int = readShort();
	p_sp_Sta = readShort();
	return true;
}

int32 	SCMD35F::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD35FHandler::Execute(this) ;
}


uint32 SCMD35FHandler::Execute(SCMD35F* pPacket)
{
	if (!pPacket) return 1;

	SceneListenerMediator* md = (SceneListenerMediator*)g_pFacade->retrieveMediator(AppFacade_SCENELISTENER_MEDIATOR);
	md->merAttributeChange(pPacket);

	return 0;
}