#include "DungeonEntrysMediator.h"
#include "model/dungeonEntrys/DungeonEntrysManage.h"
#include "socket/command/c2c/CCMD2C6.h"
#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"
#include "manager/ViewManager.h"
#include "model/scene/SceneManager.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "model/player/RoleManage.h"
#include "Message.h"
#include "model/scene/vo/SceneType.h"
#include "socket/command/c11/CCMD116.h"
#include "manager/PopEventName.h"
#include "model/worldBoss/WorldBossProxy.h"
#include "utils/ValuesUtil.h"
#include "model/silverMine/SilverMineManage.h"
#include "manager/ViewManager.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "socket/command/c37/CCMD372.h"
#include "socket/command/c37/CCMD374.h"
<<<<<<< .mine
#include "socket/command/c45/CCMD450.h" //camp fight
=======
#include "socket/command/c45/CCMD450.h" //camp fight
#include "socket/command/c11/CCMD116.h" //camp fight

#include "manager/CDManage.h"
>>>>>>> .r5911
#include "manager/LevLimitConst.h"
#include "../newhand/components/NewHandView.h"

DungeonEntrysMediator::DungeonEntrysMediator()
{
	cityIDs = DungeonEntrysManage::Instance()->getCityIDs(  );

	dungeonEntrysView = NULL;
	storyMapsView = NULL;
	challengeMapsView = NULL;
	minTaskId = 0;
	GameDispatcher::getInstance()->addEventListener(GameDispatcher::MSG_UPDATE_CHALLENGE_TIME, this, callfuncND_selector(DungeonEntrysMediator::applyForChallengeTimes));
}

void DungeonEntrysMediator::handleNotification(int M2Vcmd, char* data)
{
	switch(M2Vcmd)
	{
	case OPEN_DUNGEON_ENTRYS_VIEW:
		openDungeonEntrysView();
		break;
	case CLOSE_DUNGEON_ENTRYS_VIEW:
		closeDungeonEntrysView();
		break;
	case OPEN_LAIR_ENTRYS_VIEW:
		//openLairView();
		break;
	case OPEN_STORY_ENTRYS_VIEW:
		{
			int i = *((int*)data);
			openStoryMapsView(i);
			break;
		}
	default:
		break;
	}
}

void DungeonEntrysMediator::openDungeonEntrysView()
{
	// world boss time request
	GameServerSocket* sock = GameServerSocket::getInstance();
	if(sock)
	{
		CCMD2C6 ccmd2c6;
		sock->sendMessage(&ccmd2c6);
	}

	loadMainEntrys();
	if(!dungeonEntrysView)
		return;


	
	{

		if(g_pGlobalManage && g_pGlobalManage->inGongTime())//silvermineclose
		{

			ViewManager::getInstance()->_GongEnterTimeText->setString(ValuesUtil::Instance()->getString( "DNE008").c_str());//silvermineclose
			//ViewManager::getInstance()->_SilverMineEnterTimeText->setString(ValuesUtil::Instance()->getString( "DNE009").c_str());
		}
		else
		{
			Number openTime = SilverMineManage::Instance()->getgongStartTime();

			time_t pTimeT = (time_t)openTime;
			struct tm* pTm = localtime(&pTimeT);
			//struct tm* pTm = gmtime(  &pTimeT  );	// UTC Time

			if ( !pTm )
			{
				return;
			}
	
			int year = pTm->tm_year + 1900;	//Local time
			int month = pTm->tm_mon + 1;
			int day = pTm->tm_mday;
			int hour = pTm->tm_hour;
			int minute = pTm->tm_min;
			int second = pTm->tm_sec;
			char shows[150];
			sprintf(shows, "%s %d-%02d-%02d  %02d:%02d~%02d:%02d",  ValuesUtil::Instance()->getString( "DNE007" ).c_str(), year, month, day, hour, minute,
				hour, minute+30);
			ViewManager::getInstance()->_GongEnterTimeText->setString(shows);
		}
	}
	//
	{

		if(g_pGlobalManage && g_pGlobalManage->inMineTime())//silvermineclose
		//if (1)//silvermineclose
		{

			ViewManager::getInstance()->_SilverMineEnterTimeText->setString(ValuesUtil::Instance()->getString( "DNE008").c_str());//silvermineclose
			//ViewManager::getInstance()->_SilverMineEnterTimeText->setString(ValuesUtil::Instance()->getString( "DNE009").c_str());
		}
		else
		{
			Number openTime = SilverMineManage::Instance()->getmineStartTime();
			//var date2:Date = new Date(openTime*1000);
			//var time:String = LangManager.getText("DNE007")+date2.fullYear+"-"+(date2.month+1)+"-"+date2.date+" "+date2.hours+":"+date2.minutes;
			//if(date2.minutes == 0){
			//	time += "0";
			//}
			//time += "~";
			//date2 = new Date(openTime*1000 + 30*60*1000);
			//time += date2.hours+":"+date2.minutes;
			//dungeonEntrysView.setText(5,time,"");
			//dungeonEntrysView.enterEnable(5,false);

			//std::string str = TimerManage::formatServerTimeToDate(openTime);
			time_t pTimeT = (time_t)openTime;
			struct tm* pTm = localtime(&pTimeT);
			//struct tm* pTm = gmtime(  &pTimeT  );	// UTC Time

			if ( !pTm )
			{
				return;
			}
	
			int year = pTm->tm_year + 1900;	//Local time
			int month = pTm->tm_mon + 1;
			int day = pTm->tm_mday;
			int hour = pTm->tm_hour;
			int minute = pTm->tm_min;
			int second = pTm->tm_sec;
			char shows[150];
			sprintf(shows, "%s %d-%02d-%02d  %02d:%02d~%02d:%02d",  ValuesUtil::Instance()->getString( "DNE007" ).c_str(), year, month, day, hour, minute,
				hour, minute+30);
			ViewManager::getInstance()->_SilverMineEnterTimeText->setString(shows);
		}
	}
	/**/

	dungeonEntrysView->setisPop(!dungeonEntrysView->getisPop());

	if (dungeonEntrysView->getisPop())
	{
		dungeonEntrysView->release();
		g_pGlobalManage->setCurFocusGID(LayerManager::windowLayer->getMyFocusGID());
	}
	else
	{
		g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID());
	}
}

void DungeonEntrysMediator::closeDungeonEntrysView()
{
	//dungeonEntrysView.isPop = !dungeonEntrysView.isPop;
	if(!storyMapsView)
		return;

	storyMapsView->setisPop(!storyMapsView->getisPop());

	if (storyMapsView->getisPop() && LayerManager::windowLayer)
	{
		storyMapsView->release();
		g_pGlobalManage->setCurFocusGID(LayerManager::windowLayer->getMyFocusGID());
	}
	else if(LayerManager::sceneLayer)
	{
		g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID());
	}
}

void DungeonEntrysMediator::loadMainEntrys()
{
	onMainEntrysLoaded();
}

void DungeonEntrysMediator::onMainEntrysLoaded()
{
	initMainEntrysData();
}

void DungeonEntrysMediator::initMainEntrysData()
{
	if(dungeonEntrysView == NULL)
	{
		dungeonEntrysView = new DungeonEntrysView();
		if(dungeonEntrysView && dungeonEntrysView->init())
		{
			//dungeonEntrysView->addEventListener(DungeonEntrysMediator::CLICK_FUNCTION_ENTER, this, callfuncND_selector(DungeonEntrysMediator::onClickFunctionEnter));
			//dungeonEntrysView->addEventListener(DungeonEntrysMediator::CLICK_FUNCTION_CLOSE, this, callfuncND_selector(DungeonEntrysMediator::onClickFunctionClose));
			ViewManager::getInstance()->dungeonEntrysView = dungeonEntrysView;
		}
	}
	entrysOpenedDic.clear();
	entrysOpenedDic.insert(make_pair(1, 0));
	//if(g_pShopManage)
	//	minTaskId = g_pShopManage->lowestTaskIdOfLair();
	if(challengeMapIDs.size() == 0)
	{
		challengeMapIDs = SceneManager::Instance()->getChallengeMapIDs();
	}
	bool isOpen = false;
	if(_sceneProxy)
	{
		for(std::vector<SceneVo*>::iterator iter = challengeMapIDs.begin();
			iter != challengeMapIDs.end(); ++iter)
		{
			if((*iter) == NULL)
				continue;

			int rs = _sceneProxy->getSceneStatus((*iter)->id);
			if(rs != -1)
			{		
				isOpen = true;
				break;
			}
		}
	}

	if(isOpen)
	{
		entrysOpenedDic[2] = 0;
	}

	//if(_taskProxy && _taskProxy->isTaskFinished(minTaskId))
	//{
	//	entrysOpenedDic[3] = 0;
	//}

	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(info)
	{
		int mainLev = info->playerBaseInfo._lev;
		if(mainLev >= 40)
		{
			entrysOpenedDic[4] = 0;
			entrysOpenedDic[5] = 0;
		}
		if(mainLev >= 45)
		{
			entrysOpenedDic[6] = 0;
		}
	}
}

void DungeonEntrysMediator::onClickFunctionEnter(CCNode*n, void* data)
{
	int type = *((int*)data);
	switch(type)
	{
	case 1://juqing fuben
		{
			//closeDungeonEntrysView();
			openStoryMapsView();
			break;
		}
	case 2://tiaozhan fuben
		{
			//closeDungeonEntrysView();
			openChallengeMapsView();
			entrysOpenedDic[2] = 0;
			break;
		}
	case 3://caoxue fuben
		{
			//closeDungeonEntrysView();
			openLairView();
			entrysOpenedDic[3] = 0;
			break;
		}
	case 4://world boss
		{
			WorldBossProxy * pWBProxy = (WorldBossProxy *)g_pFacade->retrieveProxy(AppFacade_WorldBoss_Proxy);
			if (pWBProxy)
			{
				if (pWBProxy->canEnter())
				{
					Message::Instance()->show(ValuesUtil::Instance()->getString("WBS123") , ccc3(12,255,23) , 1);
					//closeDungeonEntrysView();
					openWorldBossView();

					//LH20121120 hide vscroll and taskuiview
					if (ViewManager::getInstance()->mainNavigate)
					{
						ViewManager::getInstance()->mainNavigate->showVScrollAndTaskUIView(false);
					}
				}
				else
				{
					char path[128] = {0};
					sprintf(path , ValuesUtil::Instance()->getString("WBS120").c_str() , LevLimitConst::Limit_WorldBoss);
					Message::Instance()->show(path , ccc3(233,12,25) , 1);
				}
			}
			entrysOpenedDic[4] = 0;
			break;
		}
	case 5://yinkuangzhan
		{
			//if(RoleManage::Instance()->roleLev() >40 && g_pGlobalManage && g_pGlobalManage->inMineTime())
			if (1)
			{
				openSilverMineView();//silvermineclose
			}
			else
			{
				Message::Instance()->show("DNE009");
				//LangManager.msgShow("DNE009");
			}
			entrysOpenedDic[5] = 0;
			break;
		}
	case 6://huanlongta
		{
			//closeDungeonEntrysView();
			// 人物等级40级才开启
			if(RoleManage::Instance()->roleInfo()->playerBaseInfo._lev >= LevLimitConst::Limit_DragonTower)
			{
				openDragonTowerView();
			}
			else
			{
				char path[128] = {0};
				sprintf(path , ValuesUtil::Instance()->getString("TOWR100").c_str() , LevLimitConst::Limit_DragonTower);
				Message::Instance()->show(path , ccc3(233,12,25) , 1);
			}
			entrysOpenedDic[6] = 0;
			break;
		}
	case 7://ranking
		{
			if (RoleManage::Instance()->roleInfo()->playerBaseInfo._lev >= LevLimitConst::Limit_Ranking)
			{
				openRankingView();
			}
			else
			{
				char path[128] = {0};
				sprintf(path, ValuesUtil::Instance()->getString("RK020").c_str(), LevLimitConst::Limit_Ranking);
				Message::Instance()->show(path, ccc3(233, 12, 25), 1);
			}
			entrysOpenedDic[7] = 0;
			break;
		}
<<<<<<< .mine
	case 8:
		{
			if (RoleManage::Instance()->roleInfo()->playerBaseInfo._lev >= LevLimitConst::Limit_CampFight)
			{
				openCampFight();
			}
			else
			{
				char path[128] = {0};
				sprintf(path, ValuesUtil::Instance()->getString("CFA001").c_str(), LevLimitConst::Limit_CampFight);
				Message::Instance()->show(path, ccc3(233, 12, 25), 1);
			}
			entrysOpenedDic[8] = 0;
			break;
		}
=======
	case 8:
		{
			if (RoleManage::Instance()->roleInfo()->playerBaseInfo._lev >= LevLimitConst::Limit_CampFight)
			{
				openCampFight();
			}
			else
			{
				char path[128] = {0};
				sprintf(path, ValuesUtil::Instance()->getString("CFA001").c_str(), LevLimitConst::Limit_CampFight);
				Message::Instance()->show(path, ccc3(233, 12, 25), 1);
			}
			entrysOpenedDic[8] = 0;
			break;
		}
	case 9:
		{
			if (RoleManage::Instance()->roleInfo()->playerBaseInfo._lev >= 28)
			{
				//openCampFight();
				if (g_pGlobalManage->inGongTime())
				{
					CCMD116 ccmd116;
					ccmd116.triggerId = (int16)1003;

					GameServerSocket * pSocket = GameServerSocket::getInstance();
					if(pSocket)
					{
						//LayerManager::loadingPic->socketWait_old(WMSG_WORLD_MAP_SKIP);
						pSocket->sendMessage(&ccmd116);
					}
				}
				else
				{
					char path[128] = {0};
					sprintf(path, ValuesUtil::Instance()->getString("GONG020").c_str());
					Message::Instance()->show(path, ccc3(233, 12, 25), 1);
				}
			}
			else
			{
				char path[128] = {0};
				sprintf(path, ValuesUtil::Instance()->getString("GONG019").c_str(), 28);
				Message::Instance()->show(path, ccc3(233, 12, 25), 1);
			}
			entrysOpenedDic[9] = 0;
			break;
		}
>>>>>>> .r5911
	default:
		break;
	}

	// LH  20130128
	NewHandView::Instance()->clearArrowRectangle();
}

void DungeonEntrysMediator::onClickFunctionClose(CCNode* n, void* data)
{
	closeDungeonEntrysView();
}

void DungeonEntrysMediator::openStoryMapsView(int id)
{
	initStoryEntrysData(id);
	//storyMapsView.isPop = !storyMapsView.isPop;
	if(!storyMapsView)
		return;
	if(storyMapsView->getisPop())
	{
		return;
	}
	storyMapsView->setisPop(/*!storyMapsView->getisPop()*/true);

	if (storyMapsView->getisPop() && LayerManager::windowLayer)
	{
		storyMapsView->release();
		g_pGlobalManage->setCurFocusGID(LayerManager::windowLayer->getMyFocusGID());
	}
	else if(LayerManager::sceneLayer)
	{
		g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID());
	}
}

void DungeonEntrysMediator::initStoryEntrysData(int id)
{
	if(storyMapsView == NULL)
	{
		storyMapsView = new StoryMapsView();
		if(storyMapsView && storyMapsView->init())
		{
			storyMapsView->addEventListener(DungeonEntrysMediator::CLICK_STORY_CITY_TAB, this, callfuncND_selector(DungeonEntrysMediator::onClickStoryCityTab));
			storyMapsView->addEventListener(DungeonEntrysMediator::CLICK_STORY_CITY_CLOSE, this, callfuncND_selector(DungeonEntrysMediator::onClickStoryCityClose));
			//storyMapsView->addEventListener(DungeonEntrysMediator::CLICK_STORY_MAP_ICON, this, callfuncND_selector(DungeonEntrysMediator::onClickStoryMapIcon));
			ViewManager::getInstance()->storyMapsView = storyMapsView;
		}
	}
	int cityId = 0;
	if(id == 0)
	{
		PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
		if(info)
		{
			cityId = info->playerBaseInfo._mapId;
		}
	}
	else
	{
		cityId = DungeonEntrysManage::Instance()->getCityIDByMapID(id);
	}

	SceneVo* curMap = SceneManager::Instance()->getSceneDic(cityId);
	if(curMap && curMap->type != SceneType::CITY)
	{
		cityId = DungeonEntrysManage::Instance()->getCityIDByMapID(cityId);
	}

	storyMapsView->clearCityDataList();
	if(cityIDs && _sceneProxy)
	{
		std::vector<int>::iterator iter = cityIDs->begin();
		for(; iter != cityIDs->end(); ++iter)
		{
			if(_sceneProxy && _sceneProxy->isSceneOpened(*iter))
			{
				storyMapsView->openCity(*iter - 1000, true);
			}
			else
			{
				storyMapsView->openCity(*iter - 1000, false);
			}
		}
	}
	storyMapsView->setViewAdapter();
	storyMapsView->selectTab(cityId - 1000, true);
	//onClickStoryCityTab(new ParamEvent("","_tab"+(cityId-1000)));
}

void DungeonEntrysMediator::openChallengeMapsView()
{
	/*if(!ModuleLoaderManage.getInstance().isLoaded(ResourceName.CHALLENGE_DUNGEON_ENTRYS_PATH)){
		loadChallengeEntrys();
		return;
	}
	challengeMapsView.isPop = !challengeMapsView.isPop;*/

	initChallengeEntrysData();
	//storyMapsView.isPop = !storyMapsView.isPop;
	if(!challengeMapsView)
		return;
	
	applyForChallengeTimes();

	challengeMapsView->setisPop(!challengeMapsView->getisPop());

	if (challengeMapsView->getisPop() && LayerManager::windowLayer)
	{
		challengeMapsView->release();
		g_pGlobalManage->setCurFocusGID(LayerManager::windowLayer->getMyFocusGID());
	}
	else if(LayerManager::sceneLayer)
	{
		g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID());
	}
}

void DungeonEntrysMediator::initChallengeEntrysData()
{
	if(challengeMapsView != NULL)
	{
		challengeMapsView->removeFromParentAndCleanup(true);
		challengeMapsView = 0;
		ViewManager::getInstance()->challengeMapsView = 0;
	}

	if(challengeMapsView == NULL)
	{
		challengeMapsView = new ChallengeMapsView();
	}
	if(challengeMapsView && challengeMapsView->init())
	{
		ViewManager::getInstance()->challengeMapsView = challengeMapsView;
	}

	std::vector<MapData> ary;
	challengeMapIDs.clear();
	if(challengeMapIDs.size() == 0)
	{
		challengeMapIDs = SceneManager::Instance()->getChallengeMapIDs();
	}

	if(!_sceneProxy)
		return;

	std::vector<SceneVo*>::iterator iter = challengeMapIDs.begin();
	for(; iter != challengeMapIDs.end(); ++iter)
	{
		if(!(*iter))
			continue;

		MapData mapData;
		mapData._id = (*iter)->id;
		mapData._name = (*iter)->name;
		int rs = _sceneProxy->getSceneStatus((*iter)->id);
		if(rs == -1)
		{
			mapData._star = 4;// LTT not open
		}
		else if (rs > 0)
		{
			mapData._star = 5;//can taofa, TongGuan le
		}
		else
		{
			mapData._star = 3;// LTT						
		}
		//if (mapData._id == 1209)//kevinshit
		//	mapData._star = 3;

		ary.push_back(mapData);
	}
	//MapData mapData;
	//mapData._id = 1209;
	//mapData._name = "shit";
	//mapData._star = 3;
	//ary.push_back(mapData);

	challengeMapsView->addIcons(ary);
	//challengeMapsView->setViewAdapter();
}

void DungeonEntrysMediator::openLairView()
{
	//var shopVo:ShopVo = new ShopVo();
	//shopVo.otherinfos = "1";
	//GameDispatcher.getInstance().dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_ARMY,shopVo));
}

void DungeonEntrysMediator::openWorldBossView()
{
	CCMD116 cmd;
	cmd.triggerId = (int16)1208;

	GameServerSocket * pSocket = GameServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&cmd);
	}
}


void DungeonEntrysMediator::openSilverMineView()
{
	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::INTO_SILVERMINE, 0);
}

void DungeonEntrysMediator::openDragonTowerView()
{
	GameDispatcher::getInstance()->dispatchEvent(
		PopEventName::SHOW_UI_TOWER, 0
		);
}

void DungeonEntrysMediator::openRankingView()
{
	GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_RANKING, 0);
}
//
void DungeonEntrysMediator::openCampFight()
{
	//GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::MSG_OPEN_CAMPFIGHT_VIEW, 0);
	CCMD450 ccmd450;
	GameServerSocket * pSocket = GameServerSocket::getInstance();
	if(pSocket)
	{
		//LayerManager::loadingPic->socketWait_old(WMSG_WORLD_MAP_SKIP);
		pSocket->sendMessage(&ccmd450);
	}
}

void DungeonEntrysMediator::onClickStoryCityTab(CCNode* n, void* data)
{
	//var id:int = indexToMapId(int((e.param as String).substr(4,1)));
	//wSocket.sendMessage(SocketCMDConst.CMSG_MAPS_OF_CITY_INFO,new Int16(id));
}

void DungeonEntrysMediator::onClickStoryCityClose(CCNode* n, void* data)
{
	closeStoryMapsView();
}

void DungeonEntrysMediator::closeStoryMapsView()
{
	//storyMapsView.isPop = !storyMapsView.isPop;
}

void DungeonEntrysMediator::onClickStoryMapIcon(CCNode* n, void* data)
{
	CCMD116 ccmd116;
	ccmd116.triggerId = *((int16*)data);
	GameServerSocket * pSocket = GameServerSocket::getInstance();
	if(pSocket)
	{
		//LayerManager::loadingPic->socketWait_old(WMSG_WORLD_MAP_SKIP);
		pSocket->sendMessage(&ccmd116);
	}
	//wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_MAP_ENTER,new Int16(int(e.param)));
}

void DungeonEntrysMediator::handleMapsOfCityInfo(SCMD3DB* packet)
{
	if(!packet)
	{
		return;
	}

	int cityId = packet->a_cityId;
	if(!storyMapsView)
		return;

	storyMapsView->deleteIcons();

	storyMapsView->selectTab(cityId - 1000, false);
	std::vector<MapData> ary;
	std::vector<SCMD3DBNode>::iterator iter = packet->b_mapsInfo.begin();
	//for each(node in packet.b_mapsInfo)
	for(; iter != packet->b_mapsInfo.end(); ++iter)
	{
		MapData obj;
		obj._id = iter->a_id;
		obj._star = iter->b_star;
		
		SceneVo* sceneVo = SceneManager::Instance()->getSceneDic(iter->a_id);
		if(sceneVo)
		{
			obj._name = sceneVo->name;
		}
		else
		{
			obj._name = "????";
		}
		ary.push_back(obj);
	}
	storyMapsView->addIcons(ary);
}

void DungeonEntrysMediator::applyForChallengeTimes()
{
	CCMD372 cmd372;
	GameServerSocket::getInstance()->sendMessage( &cmd372 );
	//这里需要同步373
	LayerManager::loadingPic->socketWait( WMSG_WORLD_DUNGEON_ENTER_TIMES, 0, 0);
}

void DungeonEntrysMediator::HandleChallengeTimesApply(SCMD373* packet)
{
	if (!packet)
	{
		return;
	}
	if (challengeMapsView)
	{
		challengeMapsView->setChallengeTimes(packet->a_canDungeonTimes);
		challengeMapsView->_buyTimes = packet->b_buyDungeonTimes;
		challengeMapsView->_canChallengeTimes = packet->a_canDungeonTimes;
	}
}

void DungeonEntrysMediator::applyForBuyChaTimes()
{
	CCMD374 cdm374;
	GameServerSocket::getInstance()->sendMessage( &cdm374 );
	//这里需要同步373
	LayerManager::loadingPic->socketWait( WMSG_WORLD_DUNGEON_BUY_ENTER_TIMES, 0, 0);
}

void DungeonEntrysMediator::HandleUpdateForBuyChaTimes(SCMD375* packet)
{
	if (!packet)
	{
		return;
	}
	if (challengeMapsView && packet->a_errorCode == 0)
	{
		challengeMapsView->setChallengeTimes(packet->b_canDungeonTimes);
		challengeMapsView->_buyTimes = packet->c_buyDungeonTimes;
		challengeMapsView->_canChallengeTimes = packet->b_canDungeonTimes;
	}
	if (1 == packet->a_errorCode)
	{
		LangManager::msgShow( "DNE014" , ccRED );
		return;
	}
	if (2 == packet->a_errorCode)
	{
		LangManager::msgShow( "STG022" , ccRED );
		return;
	}
}