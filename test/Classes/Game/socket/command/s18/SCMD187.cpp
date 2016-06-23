#include "SCMD187.h"
#include "view/crystal/CrystalMediator.h"
#include "manager/CDManage.h"
#include "events/CDEvent.h"
#include "../../network/GameServerSocket.h"
#include "../c1d/CCMD1DE.h"

bool SCMD187::Read()
{
	a_type = readByte();
	b_incd = readByte();
	c_time = readInt();

	return true;
}


int32 	SCMD187::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD187Handler::Execute(this) ;
}


uint32 SCMD187Handler::Execute(SCMD187* pPacket)
{
	if (!pPacket) return 1;

	//// CD
	//CDEvent a;
	//a.cdType = pPacket->a_type;
	//a.lock = pPacket->b_incd;
	//a.time = pPacket->c_time;
	//CDManage::Instance()->dispatchEvent(CDManage::CDCHANGED, &a);

	CDManage::Instance()->updateCD( pPacket->a_type, pPacket->b_incd, pPacket->c_time );

	if( pPacket->b_incd == 1 )
	{
		switch( pPacket->a_type )
		{
		case CDManage::TRAINING:
			{
				CCMD1DE cmd;
				cmd.a_cdType = CDManage::TRAINING;
				GameServerSocket::getInstance()->sendMessage( &cmd );//CMSG_WORLD_GUIDE_CDCONDITION
			}
			break;
		case CDManage::STRENGTHEN:
			{
				CCMD1DE cmd;
				cmd.a_cdType = CDManage::STRENGTHEN;
				GameServerSocket::getInstance()->sendMessage( &cmd );//CMSG_WORLD_GUIDE_CDCONDITION
			}
			break;
		}
	}

	//
	CrystalMediator * crystalMediator = (CrystalMediator *)g_pFacade->retrieveMediator(AppFacade_CRYSTAL_PROXY_CHANGE);

	//add code here
	// crystal
	if (pPacket->a_type>=CDManage::CRYSTAL_0 && pPacket->a_type<=CDManage::CRYSTAL_5)
	{
		crystalMediator->crystalCDLeftTimeListener((char *)pPacket);
	}	
	/////////////////////
	return 0;
}
