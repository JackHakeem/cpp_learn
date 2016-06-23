#include "WorldBossCmd.h"
#include "socket/network/GameServerSocket.h"
#include "model/worldBoss/WorldBossProxy.h"
#include "socket/command/s2c/SCMD2C7.h"
#include "socket/command/c2c/CCMD2CF.h"
#include "socket/command/c2d/CCMD2DC.h"
#include "socket/command/c2c/CCMD2C6.h"
#include "Confirm.h"
#include "utils/ValuesUtil.h"
#include "model/backpack/GoodsManager.h"
#include "manager/ViewManager.h"
#include "view/worldBoss/WorldBossMediator.h"

WorldBossCmd::WorldBossCmd()
{

}

WorldBossCmd::~WorldBossCmd()
{

}

void WorldBossCmd::execute(int32 command, char* data)
{
	WorldBossProxy * pWBProxy = (WorldBossProxy *)g_pFacade->retrieveProxy(AppFacade_WorldBoss_Proxy);
	if (!pWBProxy)	{		return;	}
	switch(command)
	{
	case IS_OPEN_TIME:
		{
			pWBProxy->handleOpenTime((SCMD2C7 *)data);
		}
		break;
	case UPDATE_BOSS_INFO:
		{
			pWBProxy->handleBossInfo((SCMD2C9 *)data);
		}
		break;
	case UPDATE_PLAYER_INFO:
		{
			pWBProxy->handlePlayerInfo((SCMD2C8 *)data);
		}
		break;
	case RELIVE:
		{
			pWBProxy->handleRelive((SCMD2CE *)data);
		}
		break;
	case BOOST:
		{
			pWBProxy->handleBoost((SCMD2CC *)data);
		}
		break;
	case MAP_SKIP:
		{
			pWBProxy->setCurMapID(*(int *)data);
		}
		break;
	case INIT_WORLD_BOSS_PROXY:
		{
			requestWorldBossInfo();
		}
		break;
	case ON_CLICK_QUIT:
		{
			// 弹出确认窗口 上面显示当前累计收益
			showQuitConfirm();
		}
		break;
	}
}

void WorldBossCmd::requestWorldBossInfo()
{
	CCMD2C6 cmd2c6; // world boss time info 
	CCMD2CF cmd2cf; // player info
	CCMD2DC cmd2dc; // boss info

	GameServerSocket * pSocket = GameServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&cmd2c6);
		pSocket->sendMessage(&cmd2cf);
		pSocket->sendMessage(&cmd2dc);
	}
}

void WorldBossCmd::showQuitConfirm()
{
	std::list<SCMD2C8::SCMD2C8Node> * pList = 0;
	WorldBossProxy * pProxy = (WorldBossProxy *)g_pFacade->retrieveProxy(AppFacade_WorldBoss_Proxy);
	if (pProxy)
	{
		pList = pProxy->getAwardList();
	}
	std::string strReword(ValuesUtil::Instance()->getString("WBS102").c_str());
	if (pList)
	{
		std::list<SCMD2C8::SCMD2C8Node>::iterator iter = pList->begin();
		for (; iter != pList->end() ; iter++)
		{
			std::string strGoods("?");

			switch (iter->a_id)
			{
			case 1:
				strGoods = ValuesUtil::Instance()->getString("WBS116");
				break;
			case 2:
				strGoods = ValuesUtil::Instance()->getString("WBS117");
				break;
			case 3:
				strGoods = ValuesUtil::Instance()->getString("WBS118");
				break;
			case 4:
				strGoods = ValuesUtil::Instance()->getString("WBS119");
				break;
			default :
				break;
			}

			GoodsBasic * pGoodsBase = g_pGoodsManager->getBasicGood(iter->a_id);
			if (pGoodsBase)
			{
				strGoods = pGoodsBase->goodName;
			}
			char path[32] = {0};
			sprintf(path , "%d" , iter->b_num);
			strReword.append(path);
			strReword.append(strGoods.c_str());
			strReword.append(",");
		}
	}
	else
	{
		strReword.append("0");
	}
	Confirm * _confirmBuy = new Confirm();
	_confirmBuy->initWithParam(
		strReword,
		this,
		menu_selector(WorldBossCmd::clickQuit),
		menu_selector(WorldBossCmd::clickCancel));
	if (LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame))
	{
		LayerManager::windowLayer->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
	}
	LayerManager::windowLayer->addChild(_confirmBuy,WindowLayer::WindowLayerZ_confirmFrame,WindowLayer::WindowLayerTAG_confirmFrame);
	_confirmBuy->release();
}

void WorldBossCmd::clickQuit(CCObject * pSender)
{
	clickCancel(0);
	// send quit request and dispose
	WorldBossProxy * pWBProxy = (WorldBossProxy *)g_pFacade->retrieveProxy(AppFacade_WorldBoss_Proxy);
	if (pWBProxy)	
	{
		pWBProxy->handleQuit();	
	}

	// out map
	if (ViewManager::getInstance()->mainNavigate)
	{
		ViewManager::getInstance()->mainNavigate->outOfMap(0);
	}	
}

void WorldBossCmd::clickCancel(CCObject * pSender)
{
	Confirm * _confirmBuy = (Confirm *)LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame);
	if (_confirmBuy&&_confirmBuy->getParent())
	{
		_confirmBuy->getParent()->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
	}  
}