#include "SCMD309.h"
#include "socket/network/GameServerSocket.h"
#include "view/login/LoginMediator.h"
#include "manager/GlobalManage.h"

bool	SCMD309::Read()
{
	a_threat = readUshort();
	b_mercLim = readUbyte();
	int16 cnt = readUshort(); 
	c_mercInfo.clear();
	for(int i = 0; i < cnt; ++i)
	{
		SCMD309Node node;
		node.a_id = readInt();
		node.b_typeId = readShort();
		node.c_level = readByte();
		node.d_ad_lv = readByte();
		node.e_rebornNum = readByte();
		node.f_exp_type = readByte();
		node.g0_ad_exp = readInt();
		node.g1_exp = readInt();
		node.h_maxHp = readInt();
		node.i_hp = readInt();
		node.j_strength = readShort();
		node.k_intellect = readShort();
		node.l_stamina = readShort();
		node.m_plus_str = readShort();
		node.n_plus_intel = readShort();
		node.o_plus_sta = readShort();
		node.p_sp_str = readShort();
		node.q_sp_intel = readShort();
		node.r_sp_sta = readShort();
		node.s_p_att = readInt();
		node.t_p_def = readInt();
		node.u_m_att = readInt();
		node.v_m_def = readInt();
		node.w_equipSkillId = readShort();
		node.x_aoyiId = readShort();
		node.y_passiveId = readShort();
		node.z_att = readInt();

		c_mercInfo.push_back(node);
	}

	return true;
}

int32 	SCMD309::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD309Handler::Execute(this) ;
}


uint32 SCMD309Handler::Execute(SCMD309* pPacket)
{
	if (!pPacket) return 1;
	
	CCLog("RoleAndSkill:merch list response received SCMD309");
	LoginMediator* loginMediator = (LoginMediator*)g_pFacade->retrieveMediator(AppFacade_LOGIN_MEDIATOR);
	loginMediator->mercenaryBaseInfo(pPacket);

	g_pGlobalManage->loadOneProgress( 2 );
	return 0;
}