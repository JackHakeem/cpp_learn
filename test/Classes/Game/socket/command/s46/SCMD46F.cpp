#include "SCMD46F.h"
#include "manager/LangManager.h"
#include "control/AppFacade.h"
#include "socket/network/GameServerSocket.h"
#include "view/ce/components/ceView.h"

bool SCMD46F::Read()
{

	short SCMD46FNodeNum = 0;
	SCMD46FNodeNum = readShort();

	for (int i = 0; i < SCMD46FNodeNum; i++)
	{
		SCMD46FNode node;
		node.a_name = readString();

		node.phyAttack			= readInt();
		node.magAttack			= readInt();
		node.phydef				= readInt();
		node.magdef				= readInt();
		node.health				= readInt();
		node.critRating			= readFloat();
		node.antiCrit			= readFloat();
		node.critHarm			= readFloat();
		node.counterRating		= readFloat();
		node.antiCounterRating	= readFloat();
		node.counterHarmRating	= readFloat();
		node.hitRating			= readFloat();
		node.dodgeRating		= readFloat();
		node.startep			= readInt();

		nodes.push_back(node);
	}



	return true;
}

int32 SCMD46F::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD46FHandler::Execute(this);
}

uint32 SCMD46FHandler::Execute( SCMD46F* pPacket )
{
	//ceView
	{
		ceView* pce = ceView::Instance();
		if (!pce->getParent())
		{
			pce->init();
			LayerManager::intervalLayer->addChild(pce, PreTipsLayer::PreTipsLayerZ_ce+1000, PreTipsLayer::PreTipsLayerTAG_ce+1000);
			pce->release();		
		}
		pce->cleanStrs();
	}


	char str[300];

	for (int i = 0; i < pPacket->nodes.size(); i++)
	{
		sprintf(str, ValuesUtil::Instance()->getString( "ZX026" ).c_str(),  
		pPacket->nodes[i].a_name.c_str(), 

		pPacket->nodes[i].phyAttack,			
		pPacket->nodes[i].magAttack,			
		pPacket->nodes[i].phydef,				
		pPacket->nodes[i].magdef,				
		pPacket->nodes[i].health,				
		pPacket->nodes[i].critRating,			
		pPacket->nodes[i].antiCrit,			
		pPacket->nodes[i].critHarm,			
		pPacket->nodes[i].counterRating,		
		pPacket->nodes[i].antiCounterRating,	
		pPacket->nodes[i].counterHarmRating,	
		pPacket->nodes[i].hitRating,			
		pPacket->nodes[i].dodgeRating,			
		pPacket->nodes[i].startep	
		);

		ceView::Instance()->insertNode(str);
	}
				
			
	

	return 0;
}
