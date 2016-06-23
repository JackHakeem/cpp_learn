#include "WorldBossMediator.h"
#include "socket/command/s2c/SCMD2C9.h"
#include "socket/command/s2c/SCMD2C8.h"
#include "socket/command/s2c/SCMD2CE.h"
#include "socket/command/s2c/SCMD2CC.h"
#include "manager/ViewManager.h"
#include "components/BossHPView.h"
#include "components/DamageRankView.h"
#include "components/DeathView.h"
#include "components/BoostView.h"
#include "socket/command/c2c/CCMD2CD.h"
#include "socket/command/c2c/CCMD2CB.h"
#include "control/wordBoss/WorldBossCmd.h"
#include "manager/GlobalManage.h"
#include "Message.h"
#include "utils/ValuesUtil.h"
#include "components/QuitView.h"
#include <sys/stat.h>
#include "socket/command/s2c/SCMD2C7.h"
#include "../dungeonEntrys/DungeonEntrysMediator.h"
#include "../fight/callback/FightFollowWorldBossAction.h"
#include "manager/CDManage.h"
#include "manager/TimerManage.h"
#include "socket/command/c2d/CCMD2DD.h"
#include <time.h>

WorldBossMediator::WorldBossMediator()
{
	_isLoaded = false;
	_isInTime = 0;
	_powerUp = 0;
	_restTime = 0;
}

WorldBossMediator::~WorldBossMediator()
{
	 
}

void WorldBossMediator::handleNotification( int M2Vcmd, char* data )
{
	switch(M2Vcmd) 
	{
	case ENTER:
		{
			initView();
		}
		break;
	case QUIT:
		{
			quit();
		}
		break;
	case UPDATE_BOSS_INFO:
		{
			updateBossInfo((SCMD2C9 *)data);
		}
		break;
	case UPDATE_PLAYER_INFO:
		{
			updatePlayerInfo((SCMD2C8 *)data);
		}
		break;
	case RELIVE:
		{
			relive((SCMD2CE *)data);
		}
		break;
	case BOOST:
		{
			boost((SCMD2CC *)data);
		}
		break;
	case UPDATE_OPEN_TIME:
		{
			updateOpenTime((SCMD2C7 *) data);
		}
		break;
		//				case BATTLE_END:
		//					battleEnd();
		//					break;
	default:
		break;
	}
}

void WorldBossMediator::updateBossInfo(SCMD2C9 * data)
{
	if (!data)
	{
		return;
	}
	int nCurHP = data->a_currentHP;
	int nMaxHP = data->b_maxHP;
	int nTotalDamageLow = data->c_totalDamage_low;
	int nTotalDamageHigh = data->c_totalDamage_high;
	std::list<SCMD2C9::SCMD2C9Node> dmgRankList = data->d_damageRankList;

	WorldBossMainView * pWBMainView = ViewManager::getInstance()->_pWBMainView;
	if (pWBMainView)
	{
		//
		BossHPView * pHPView = (BossHPView *)pWBMainView->getChildByTag(WorldBossMainView::TAG_BossHPView);
		if (pHPView)
		{
			if (nCurHP == -1)
			{
				// 前20分钟血量是剩余时间的百分比  please see QuitView
				// pHPView->updateHP(0.1f , nCurHP , nMaxHP ,  _restTime/ 1800);
			}
			else
			{
				// 后10分钟是真实血量
				pHPView->updateHP(0.1f , nCurHP , nMaxHP);
			}
		}

		// 伤害排名
		DamageRankView * pDamageView = (DamageRankView *)pWBMainView->getChildByTag(WorldBossMainView::TAG_DamageView);
		if (pDamageView)
		{
			pDamageView->updateDamageRankList(dmgRankList , nTotalDamageLow , nTotalDamageHigh);
		}

		//
		if (nCurHP == 0)
		{
			// 剩余时间置0 死亡框清除
			//
			//
			requestQuit();
		}
	}
}

void WorldBossMediator::updatePlayerInfo(SCMD2C8 * data)
{
	if (!data)
	{
		return;
	}
	int nMoveCD = data->a_movingCD;
	int nBattleCD = data->b_battleCD;
	int nBoostNum = data->c_boostNum;
	int nMyDamage = data->d_damage;

	_powerUp = data->c_boostNum;

	WorldBossMainView * pWBMainView = ViewManager::getInstance()->_pWBMainView;
	if (pWBMainView)
	{
		// 更新我的鼓舞加成
		BoostView * pBoostView = (BoostView *)pWBMainView->getChildByTag(WorldBossMainView::TAG_BoostView);
		if (pBoostView)
		{
			pBoostView->resetBoostResultText(_powerUp);
		}
		// 更新我的伤害
		DamageRankView * pDamageView = (DamageRankView * )pWBMainView->getChildByTag(WorldBossMainView::TAG_DamageView);
		if (pDamageView)
		{
			pDamageView->resetMyDamage(nMyDamage);
		}
		// 更新我的CD
		DeathView * pDeathView = (DeathView * )pWBMainView->getChildByTag(WorldBossMainView::TAG_DeathView);
		if (pDeathView)
		{
			pDeathView->updateCD(nMoveCD);
		}
	}
}

void WorldBossMediator::relive(SCMD2CE * data)
{
	if (!data)
	{
		return;
	}
	int nMode = data->a_mode;
	int nResult = data->b_result;

	// 复活提示message
	switch (nResult)
	{
	case 0:
		Message::Instance()->show(ValuesUtil::Instance()->getString("WBS110") , ccc3(12,233,25) , 1);		
		showDeathView(false);
		break;
	case 1:
		Message::Instance()->show(ValuesUtil::Instance()->getString("WBS122") , ccc3(233,12,25) , 1);
		break;
	case 2:
		Message::Instance()->show(ValuesUtil::Instance()->getString("WBS108") , ccc3(233,12,25) , 1);
		break;
	case 3:
		Message::Instance()->show(ValuesUtil::Instance()->getString("WBS124") , ccc3(233,12,25) , 1);
		break;
	default:
		break;
	}
}

void WorldBossMediator::showDeathView(bool bVar)
{
	WorldBossMainView * pWBMainView = ViewManager::getInstance()->_pWBMainView;
	if (pWBMainView)
	{
		DeathView * pDeathView = (DeathView * )pWBMainView->getChildByTag(WorldBossMainView::TAG_DeathView);
		if (pDeathView)
		{
			pDeathView->setIsVisible(bVar);
			if (!bVar)
			{
				pDeathView->stopCD();
			}
		}
	}

	/*
	// add fight call back
	FightProxy *pFightProxy = (FightProxy *) g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
	if (pFightProxy)
	{
		int curMapID = RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId;
		if (curMapID == 1208 && !bVar)
		{
			pFightProxy->_bData._callbacks.push_back(new FightFollowWorldBossAction());
		}
	}
	*/
}

void WorldBossMediator::boost(SCMD2CC * data)
{
	if (!data)
	{
		return;
	}

	int var = data->a_result;
	//一些提示
	switch (var)
	{
	case 0:
		{
			Message::Instance()->show(ValuesUtil::Instance()->getString("WBS027") , ccc3(12,233,25) , 1);
		}
		break;
	case 1:
		{
			Message::Instance()->show(ValuesUtil::Instance()->getString("WBS028") , ccc3(233,12,25) , 1);
		}
		break;
	case 2:
		{
			Message::Instance()->show(ValuesUtil::Instance()->getString("WBS029") , ccc3(233,12,25) , 1);
		}
		break;
	case 3:
		{
			Message::Instance()->show(ValuesUtil::Instance()->getString("WBS030") , ccc3(233,12,25) , 1);
		}
		break;
	case 4:
		{
			Message::Instance()->show(ValuesUtil::Instance()->getString("WBS031") , ccc3(233,12,25) , 1);
		}
		break;
	case 5:
		{
			Message::Instance()->show(ValuesUtil::Instance()->getString("WBS032") , ccc3(233,12,25) , 1);
		}
		break;
	case 6:
		{
			Message::Instance()->show(ValuesUtil::Instance()->getString("WBS033") , ccc3(233,12,25) , 1);
		}
		break;
	}
}

/** 离开地图消息处理 */
void WorldBossMediator::quit()
{
	// 玩家请求退出世界BOSS活动
	CCMD2DD cmd;
	GameServerSocket * pSocket = GameServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&cmd);
	}

	// 析构
	showWorldBossUI(false);
	removeWorldBossScene();

	
	

	//LH20121120
	if (ViewManager::getInstance()->mainNavigate)
	{
		ViewManager::getInstance()->mainNavigate->showVScrollAndTaskUIView(true);
	}
	if (ViewManager::getInstance()->mainNavigate)
	{
		ViewManager::getInstance()->mainNavigate->enableMainavigate(true);
	}
	g_pGlobalManage->setIsInWorldBoss(false);
}

void WorldBossMediator::removeWorldBossScene()
{
	if (ViewManager::getInstance()->_pWBMainView)
	{
		//ViewManager::getInstance()->_pWBMainView->removeAllChildrenWithCleanup(true);
	}

	_isLoaded = false;
}

void WorldBossMediator::requestQuit()
{
	
	// 显示累计奖励
	sendNotification(Facade_Command , AppFacade_WorldBoss_Command , (char *)0 , WorldBossCmd::ON_CLICK_QUIT);
}

void WorldBossMediator::requestRelive() 
{
	// 判断金币
	int nGold = RoleManage::Instance()->accountInfo()->_gold;
	if(nGold >= 5)
	{
		CCMD2CD cmd;
		cmd.a_mode = (uint8)0;
		GameServerSocket * pSocket = GameServerSocket::getInstance();
		if (pSocket)
		{
			pSocket->sendMessage(&cmd);
		}
	}
	else
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("WBS108") , ccc3(233,12,25) , 1);
	}
}

void WorldBossMediator::requestReborn()
{
	// 判断金币
	int nGold = RoleManage::Instance()->accountInfo()->_gold;
	if(nGold >= 10)
	{
		CCMD2CD cmd;
		cmd.a_mode = (uint8)1;
		GameServerSocket * pSocket = GameServerSocket::getInstance();
		if (pSocket)
		{
			pSocket->sendMessage(&cmd);
		}
	}
	else
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("WBS108") , ccc3(233,12,25) , 1);
	}
}

void WorldBossMediator::requestGoldBoost()
{
	// 金币鼓舞需要10金币
	int nGold = RoleManage::Instance()->accountInfo()->_gold;
	if(nGold < 10)
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("WBS108") , ccc3(233,12,25) , 1);
		return;
	}
	// 如果战斗力已满,不能继续鼓舞
	if(_powerUp >= 100)
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("WBS111") , ccc3(233,12,25) , 1);
		return;
	}

	CCMD2CB cmd;
	cmd.type = (uint8)0;
	GameServerSocket * pSocket = GameServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&cmd);
	}
}

void WorldBossMediator::requestPracBoost()
{
	// 历练鼓舞需要人物等级*9.5历练
	int nPractice = RoleManage::Instance()->accountInfo()->_practice;
	int nRoleLev = RoleManage::Instance()->roleLev();
	if(nPractice < (int)(nRoleLev * 9.5))
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("WBS109") , ccc3(233,12,25) , 1);
		return;
	}
	// 如果战斗力已满,不能继续鼓舞
	if(_powerUp >= 100)
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("WBS111") , ccc3(233,12,25) , 1);
		return;
	}

	CCMD2CB cmd;
	cmd.type = (uint8)1;
	GameServerSocket * pSocket = GameServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&cmd);
	}
}

void WorldBossMediator::sockOpenTime(SCMD2C7 * data)
{
	sendNotification(Facade_Command , AppFacade_WorldBoss_Command , (char *)data , WorldBossCmd::IS_OPEN_TIME);
}

void WorldBossMediator::sockPlayerInfo(SCMD2C8 * data)
{
	sendNotification(Facade_Command , AppFacade_WorldBoss_Command , (char *)data , WorldBossCmd::UPDATE_PLAYER_INFO);
}

void WorldBossMediator::sockBossInfo(SCMD2C9 * data)
{
	sendNotification(Facade_Command , AppFacade_WorldBoss_Command , (char *)data , WorldBossCmd::UPDATE_BOSS_INFO);
}

void WorldBossMediator::sockBoost(SCMD2CC * data)
{
	sendNotification(Facade_Command , AppFacade_WorldBoss_Command , (char *)data , WorldBossCmd::BOOST);
}

void WorldBossMediator::sockRelive(SCMD2CE * data)
{
	sendNotification(Facade_Command , AppFacade_WorldBoss_Command , (char *)data , WorldBossCmd::RELIVE);
}

void WorldBossMediator::initView()
{
	bool var = (RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId == 1208);
	showWorldBossUI(var);	
	g_pGlobalManage->setIsInWorldBoss(true);

	//LH20121120
	if (ViewManager::getInstance()->mainNavigate)
	{
		ViewManager::getInstance()->mainNavigate->showVScrollAndTaskUIView(false);
	}
	if (ViewManager::getInstance()->mainNavigate)
	{
		ViewManager::getInstance()->mainNavigate->enableMainavigate(false);
	}

	//g_pGlobalManage->showAllUI(!var);
	if (_isLoaded)
	{
		return;
	}

	WorldBossMainView * pWBMainView = new WorldBossMainView();
	if (pWBMainView)
	{
		pWBMainView->init();
		if (LayerManager::sceneLayer && !LayerManager::sceneLayer->getChildByTag(SceneUILayer::SceneUILayerTAG_WorldBoss))
		{
			pWBMainView->setTag(SceneUILayer::SceneUILayerTAG_WorldBoss);
			LayerManager::sceneLayer->addChild(pWBMainView , SceneUILayer::SceneUILayerZ_WorldBoss);
			pWBMainView->release();
			_isLoaded = true;

			ViewManager::getInstance()->_pWBMainView = pWBMainView;
		}
	}
	showWorldBossUI(var);	
	//g_pGlobalManage->showAllUI(!var);

	// request all info and renew
	sendNotification(Facade_Command , AppFacade_WorldBoss_Command , (char *)0 , WorldBossCmd::INIT_WORLD_BOSS_PROXY);
}

void WorldBossMediator::showWorldBossUI(bool var)
{
	if (LayerManager::sceneLayer && LayerManager::sceneLayer->getChildByTag(SceneUILayer::SceneUILayerTAG_WorldBoss))
	{
		LayerManager::sceneLayer->getChildByTag(SceneUILayer::SceneUILayerTAG_WorldBoss)->setIsVisible(var);
	}
}

void WorldBossMediator::updateOpenTime(SCMD2C7 * data)
{
	_restTime = 1800 - TimerManage::getSeconds(data->a_nextTime , CDManage::Instance()->getServerTime() / 1000);
	_isInTime = data->b_inTime;

	// update dungeonEntry tips
	//std::string strOpenDate = TimerManage::formatServerTimeToDate(data->a_nextTime);
	std::string strOpenDate = getTimeStringByMili((Number)data->a_nextTime);
	if (ViewManager::getInstance()->_WorldBossOpenTimeText)
	{
		ViewManager::getInstance()->_WorldBossOpenTimeText->setString(strOpenDate.c_str());
	}

	// update deathview CD
	WorldBossMainView * pWBMainView = ViewManager::getInstance()->_pWBMainView;
	if (pWBMainView)
	{
		QuitView * pQuitView = (QuitView * )pWBMainView->getChildByTag(WorldBossMainView::TAG_QuitView);
		if (pQuitView && _restTime >= 0)
		{
			//pQuitView->updateCD(data->a_nextTime);
			pQuitView->runActivityCD(_restTime);
		}
	}
}

std::string WorldBossMediator::getTimeStringByMili(Number time)
{
	std::string szDate("");
	struct tm * stTime = localtime((const time_t *)&time); 
	int year = stTime->tm_year + 1900;
	int month = stTime->tm_mon + 1;
	int day = stTime->tm_mday;
	int hour = stTime->tm_hour;
	int min = stTime->tm_min;
	char path[256] = {0};
	sprintf(path,"%d-%02d-%02d %02d:%02d~%02d:%02d", year,month,day,hour,min,hour,min+30);
	szDate = path;
	return szDate;
}
