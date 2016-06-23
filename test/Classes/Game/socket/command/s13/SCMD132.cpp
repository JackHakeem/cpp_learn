#include "SCMD132.h"
#include "view/scene/layer/BattleLayer.h"
#include "model/battle/BattleProxy.h"
#include "view/scene/components/BattlePlay.h"
#include "control/AppFacade.h"
#include "model/battle/FightProxy.h"
#include "view/battle/SceneFightMediator.h"
#include "manager/GlobalManage.h"

//Change the read data, save data to 132
bool	SCMD132::Read()
{
   
	a_BattleId  = readInt();

	if (a_BattleId==0)
	{
		a_BattleId = 999;
	}
	b_round	 = readByte();
    c_Actions.clear();


	 SCMD132Node1Num = readShort();
	for (int i = 0; i < (int)SCMD132Node1Num; i++)
	{
        
      
		SCMD132Node1 newnode1;
		newnode1.a_attackId = readByte();
		newnode1.b_resonanceId = readByte();
		newnode1.c_skill = readShort();
		newnode1.d_attackhp = readInt();
		newnode1.e_attackmp = readShort();
		newnode1.f_buffType = readInt();
        
		  SCMD132Node2Num = readShort();
		for (int j = 0; j < (int)SCMD132Node2Num; j++)
		{
            
		 
			SCMD132Node2 newnode2;
			newnode2.a_hitedId	= readByte();
			newnode2.b_crit		= readByte();
			newnode2.c_hitedhp	= readInt();
			newnode2.d_hitedmp	= readShort();
			newnode2.e_damage	= readInt();
			newnode2.f_buffType = readByte();
			newnode2.g_state	= readByte();
            
			  SCMD132Node3Num = readShort();
			for(int k = 0; k < (int)SCMD132Node3Num; k++)
			{
				 
				SCMD132Node3 newnode3;
				newnode3.a_hitedId	= readByte();
				newnode3.b_hitedhp	= readInt();
				newnode3.c_hitedmp	= readShort();
				newnode3.d_damage	= readInt();
				newnode3.e_diffEp	= readInt();
				newnode3.f_buffType	= readByte();
				newnode3.g_state	= readByte();
                
				newnode2.h_hiteds.push_back(newnode3);
                
			}
            
			newnode1.g_hiteds.push_back(newnode2);
            
		}
		
		 
        c_Actions.push_back(newnode1);
	}
    
    
    
	  SCMD132Node4Num = readShort();

	for (int i = 0; i < (int)SCMD132Node4Num; i++)
	{
      
		SCMD132Node4 newnode4;
		newnode4.a_buffTtype	= readByte();
		newnode4.b_id			= readByte();
		newnode4.c_hp			= readInt();
		newnode4.d_mp			= readShort();
		newnode4.e_damage		= readInt();
		newnode4.f_ep_damage	= readByte();
		newnode4.g_state		= readByte();
		newnode4.h_isremove		= readByte();

		  SCMD132Node5Num = readShort();
		for (int j = 0 ; j < (int)SCMD132Node5Num; j++)
		{
			 
			SCMD132Node5 newnode5;
			newnode5.a_hitedId = readByte();
			newnode5.b_hitedhp = readInt();
			newnode5.c_hitedmp = readShort();
			newnode5.d_damage  = readInt();
			newnode5.e_diffEp  = readInt();
			newnode5.f_buffType= readByte();
			newnode5.g_state   = readByte();
            
			newnode4.i_hiteds.push_back(newnode5);
		}
        
	 
		d_buffs.push_back(newnode4);
	}

	
	return true;
}

int32 	SCMD132::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD132Handler::Execute(this) ;
}


uint32 SCMD132Handler::Execute(SCMD132* pPacket)
{

	if (!pPacket) return 1;

	if (g_pGlobalManage->m_canSCMD133Enable != 2)
	{
		if (g_pGlobalManage->m_canSCMD133Enable == 1)
			g_pGlobalManage->m_canSCMD133Enable = 2;
		else 
			g_pGlobalManage->m_canSCMD133Enable = 9;
	
	}

	if (g_pGlobalManage->getTowerGUA() != 0)
		return 1;

	//FightProxy* _fightProxy = (FightProxy*)g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
	//_fightProxy->addFightPack(pPacket);  //Each read a 132 package, are credited to the object pointer containers

	SceneFightMediator* m = (SceneFightMediator*)g_pFacade->retrieveMediator(AppFacade_FIGHT_PROXY_CHANGE);
	if(m)
		m->addBattleContent((char*)pPacket);
//_fightPr	g_pFacade->retrieveMediator(AppFacade_FIGHT_PROXY_CHANGE);

	//BattleLayer::getInstance()->startBattleAnimation();
	//BattlePlay::getInstance()->checkBattleAction();
	return 0;
}