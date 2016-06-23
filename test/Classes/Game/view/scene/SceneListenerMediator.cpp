#include "SceneListenerMediator.h"
#include "model/player/RoleManage.h"
#include "util/TileUtil.h"
#include "control/scene/SceneProxyCommand.h"
#include "model/scene/vo/EventType.h"
#include "control/battle/SceneFightProxyCommand.h"
#include "manager/GlobalManage.h"
#include "manager/ViewManager.h"
#include "manager/layer/MapManage.h"
#include "model/scene/vo/FindVo.h"
#include "../task/components/TaskType.h"
#include "SceneMediator.h"
#include "events/GameDispatcher.h"
#include "socket/command/c11/CCMD114.h"
#include "socket/network/GameServerSocket.h"
#include "model/scene/vo/SceneType.h"
#include "model/scene/SceneManager.h"
#include "socket/command/c11/CCMD116.h"
#include "Message.h"
#include "socket/command/c11/CCMD11E.h"
#include "model/shop/ShopManage.h"
#include "socket/command/c11/CCMD119.h"
#include "socket/command/c12/CCMD121.h"
#include "socket/command/c11/CCMD115.h"
#include "manager/PopEventName.h"
#include "SceneWorldMediator.h"
#include "../dungeonEntrys/DungeonEntrysMediator.h"
#include "manager/LayerManager.h"
#include "SceneStoryMediator.h"
#include "mvc/Facade.h"
#include "utils/ValuesUtil.h"

#include "LoginManage.h"
#include "view/login/components/LoginView.h"
#include "model/trader/vo/CityPriceVo.h"
#include "model/trader/TraderManager.h"
#include "../trader/CityTraderMediator.h"
#include "socket/command/c0f/CCMD0F0.h"
#include "model/newhand/NewhandManager.h"
#include "../newhand/components/NewHandView.h"
#include "manager/LevLimitConst.h"

SceneListenerMediator::SceneListenerMediator()
{
	if(g_pFacade)
		_sceneMediator = (SceneMediator*)g_pFacade->retrieveMediator(AppFacade_SCENE_MEDIATOR);
}

void SceneListenerMediator::handleNotification(int M2Vcmd, char* data)
{
	switch(M2Vcmd) 
	{
	case START_SCENE_LISTENER:
		startSceneListener();
		break;
	case REMOVE_SCENE_LISTENER:
		removeSceneListener();
		break;
	//case GOTO_FIGHT_SCENE:
	//	gotoFightScene();
	//	break;
	}
}

void SceneListenerMediator::startSceneListener()
{
	GameDispatcher::getInstance()->addEventListener(GameDispatcher::FIND_ELEMENT, this, callfuncND_selector(SceneListenerMediator::findElementHandler));
	if(_sceneMediator && _sceneMediator->_scene)
	{
		_sceneMediator->_scene->addEventListener(SceneConst::MAP_BG_INIT, this, callfuncND_selector(SceneListenerMediator::getProcess));
		_sceneMediator->_scene->addEventListener(SceneConst::ROLE_MOVE, this, callfuncND_selector(SceneListenerMediator::roleMove));

		_sceneMediator->_scene->addEventListener(SceneConst::ROLE_POS_CHANGED, this, callfuncND_selector(SceneListenerMediator::rolePos));
		_sceneMediator->_scene->addEventListener(SceneConst::NPC_REMOVEDEADBODY, this, callfuncND_selector(SceneListenerMediator::npc_removedeadbody));
		_sceneMediator->_scene->addEventListener(SceneConst::TRIGGER_EXIT, this, callfuncND_selector(SceneListenerMediator::triggerExit));
		_sceneMediator->_scene->addEventListener(SceneConst::ATTACKMONSTER, this, callfuncND_selector(SceneListenerMediator::attackMonster));
		_sceneMediator->_scene->addEventListener(SceneConst::DIALOG_NPC, this, callfuncND_selector(SceneListenerMediator::dialogNPC));
		_sceneMediator->_scene->addEventListener(SceneConst::ELEMENT_LAYOUT, this, callfuncND_selector(SceneListenerMediator::elementLayout));
		_sceneMediator->_scene->addEventListener(SceneConst::NPC_MOVE, this, callfuncND_selector(SceneListenerMediator::npcMove));

		//_sceneMediator->_scene->addEventListener(SceneConst::STOP_AND_ATTACK_COMPLETE, this, callfuncND_selector(SceneListenerMediator::stopAndAttackCompleteHandler));
		_sceneMediator->_scene->addEventListener(SceneConst::WALK_START, this, callfuncND_selector(SceneListenerMediator::walkStartHandler));
		_sceneMediator->_scene->addEventListener(SceneConst::WALK_START_NODE, this, callfuncND_selector(SceneListenerMediator::walkStartNodeHandler));
		_sceneMediator->_scene->addEventListener(SceneConst::WALK_COMPLETE, this, callfuncND_selector(SceneListenerMediator::walkCompleteHandler));
		_sceneMediator->_scene->addEventListener(SceneConst::WALK_PATH_CHANGE, this, callfuncND_selector(SceneListenerMediator::walkPathChangeHandler));
		_sceneMediator->_scene->addEventListener(SceneConst::SELECT_PLAYER, this, callfuncND_selector(SceneListenerMediator::clickPlayerHandler));
		_sceneMediator->_scene->addEventListener(SceneConst::CANCEL_PLAYER, this, callfuncND_selector(SceneListenerMediator::cancelPlayerHandler));

		_sceneMediator->_scene->addEventListener(SceneConst::TRADE_WALK_START_NODE, this, callfuncND_selector(SceneListenerMediator::tradeWalkStartNodeHandler));
	}
	GameDispatcher::getInstance()->addEventListener(GameDispatcher::CREATE_PALYER_FINISH, this, callfuncND_selector(SceneListenerMediator::createPlayerFinish));

	GameDispatcher::getInstance()->addEventListener(GameDispatcher::CREATE_TRADEPALYER_FINISH, this, callfuncND_selector(SceneListenerMediator::createTradePlayerFinish));
		
}

void SceneListenerMediator::getProcess(CCNode*n, void* data)
{
	sendNotification(Facade_Mediator, AppFacade_SCENEWORLD_MEDIATOR, (char*)data, SceneWorldMediator::CLOSE_WORLD_SCENE);
	//startListener();
	GameServerSocket* pSocket = GameServerSocket::getInstance();
	if(!pSocket)
		return;

	CCMD119 ccmd119;
	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(info)
	{
		ccmd119.a_mapId = info->playerBaseInfo._mapId;
		pSocket->sendMessage(&ccmd119);
	}

	CCMD121 ccmd121;
	ccmd121.a_byte = 0;
	pSocket->sendMessage(&ccmd121);

	//_wSocket.sendMessage(SocketCMDConst::CMSG_WORLD_MAP_PROCESS_GET, new Int8(0)); // 121
	//_wSocket.sendMessage(SocketCMDConst::CMSG_WORLD_PLAYER_VIEW_GET,new Int16( _roleManage.roleInfo.playerBaseInfo.mapId)); // 119

}



void SceneListenerMediator::roleMove(CCNode* n, void* data)
{
	sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)data, SceneMediator::MOVE_ROLE);
}

void SceneListenerMediator::npcMove(CCNode* n, void* data)
{
	sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)data, SceneMediator::MOVE_NPC);
}

void SceneListenerMediator::stopAndAttackCompleteHandler(CCNode* n, void* data)
{
	//_fightProxy->_roleStopAndNpcAttack = true;
	//_fightProxy->gotoFightScene();
}

void SceneListenerMediator::removeSceneListener()
{
	GameDispatcher::getInstance()->removeEventListener(GameDispatcher::FIND_ELEMENT);

	if(_sceneMediator && _sceneMediator->_scene)
	{
		_sceneMediator->_scene->removeEventListener(SceneConst::MAP_BG_INIT);
		_sceneMediator->_scene->removeEventListener(SceneConst::ROLE_MOVE);
		_sceneMediator->_scene->removeEventListener(SceneConst::ROLE_POS_CHANGED);
		_sceneMediator->_scene->removeEventListener(SceneConst::NPC_REMOVEDEADBODY);
		_sceneMediator->_scene->removeEventListener(SceneConst::TRIGGER_EXIT);
		_sceneMediator->_scene->removeEventListener(SceneConst::ATTACKMONSTER);
		_sceneMediator->_scene->removeEventListener(SceneConst::DIALOG_NPC);

		_sceneMediator->_scene->removeEventListener(SceneConst::ELEMENT_LAYOUT);
		//_sceneMediator.scene.removeEventListener(SceneConst::NPC_LAYOUT);

		_sceneMediator->_scene->removeEventListener(SceneConst::NPC_MOVE);

		_sceneMediator->_scene->removeEventListener(SceneConst::WALK_START);
		_sceneMediator->_scene->removeEventListener(SceneConst::WALK_START_NODE);
		_sceneMediator->_scene->removeEventListener(SceneConst::WALK_COMPLETE);
		_sceneMediator->_scene->removeEventListener(SceneConst::WALK_PATH_CHANGE);

		_sceneMediator->_scene->removeEventListener(SceneConst::SELECT_PLAYER);
		_sceneMediator->_scene->removeEventListener(SceneConst::CANCEL_PLAYER);


		_sceneMediator->_scene->removeEventListener(SceneConst::TRADE_WALK_START_NODE);
	}

	GameDispatcher::getInstance()->removeEventListener(GameDispatcher::CREATE_PALYER_FINISH);
}

void SceneListenerMediator::gotoFightScene()
{
	/*bool useTrigger = 2 >_roleManage.accountInfo.team; 
	EnterCombatSceneMgr.getInstance().preGotoCommonScene(useTrigger)
		return;*/
}

std::vector<CCPoint> SceneListenerMediator::changeToMapPoint(std::vector<CCPoint>& path)
{
	std::vector<CCPoint> newPath;
	for(std::vector<CCPoint>::iterator iter = path.begin();
		iter != path.end(); ++iter)
	{
		CCPoint pos = TileUtil::Instance()->changePixsToTile(*iter);
		newPath.push_back(pos);
	}
	return newPath;
}

void SceneListenerMediator::rolePos(CCNode* n, void* data)
{
	if(!data)
		return;

	CCPoint* point = (CCPoint*)data;

	sendNotification(Facade_Command, AppFacade_SCENEPROXY_COMMAND, (char*)data, SceneProxyCommand::ROLE_POS_CHANGE);

	CCPoint newPoint = TileUtil::Instance()->changePixsToTile(*point);

	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(info)
	{
		info->playerBaseInfo.x = newPoint.x;
		info->playerBaseInfo.y = newPoint.y;
	}
}

void SceneListenerMediator::npc_removedeadbody(CCNode* n, void* data)
{
	sendNotification(Facade_Command, AppFacade_SCENEPROXY_COMMAND, (char*)data, SceneProxyCommand::REMOVE_NPC);
}

/**
	* change scene
	* @param evt
	* 
	*/
void SceneListenerMediator::triggerExit(CCNode* n, void* data)
{
	//StageProxy.ReDrawSrceen();
	int triggerId = *((int*)data);
	if(triggerId == 0)
	{
		if(_sceneProxy && _sceneProxy->sceneInfoVo()
			&& _sceneProxy->sceneInfoVo()->type != SceneType::COPY
			&& ViewManager::getInstance()->_scene
			&& !ViewManager::getInstance()->_scene->getIsTouchMoveBegin()) //LH
		{
			int sceneId = 0;
			if(MapManage::Instance()->isAutoFindPath)
			{
				sceneId = MapManage::Instance()->_nextFindVo._sceneId;
			}
			sendNotification(Facade_Mediator, AppFacade_DungeonEntrysMediator, (char*)&sceneId, DungeonEntrysMediator::OPEN_STORY_ENTRYS_VIEW);

			LayerManager::newhandLayer->setIsVisible(false);
		}
		return;
	}
	SceneVo* sceneVo = SceneManager::Instance()->getSceneDic(triggerId);
	AccountInfoVo* info = RoleManage::Instance()->accountInfo();
	if(!info)
		return;

	if(info->team == 0)
	{
		CCMD116 ccmd116;
		ccmd116.triggerId = (int16)triggerId;
		GameServerSocket * pSocket = GameServerSocket::getInstance();
		if(pSocket)
		{
			//LayerManager::loadingPic->socketWait_old(WMSG_WORLD_MAP_SKIP);
			pSocket->sendMessage(&ccmd116);
		}
		return;
	}
	else if(info->team == 1)
	{
		captainExit(*sceneVo);
	}
	else if(info->team == 2)
	{
		memberExit(*sceneVo);
	}
}

void SceneListenerMediator::captainExit(SceneVo& sceneVo)
{
	switch(sceneVo.type)
	{
	case SceneType::STORY:
		Message::Instance()->show("Not allowed to enter story scene when in team");
		break;
	case SceneType::COPY:
		{
			CCMD116 ccmd116;
			ccmd116.triggerId = (int16)sceneVo.id;
			GameServerSocket * pSocket = GameServerSocket::getInstance();
			if(pSocket)
			{
				//LayerManager::loadingPic->socketWait_old(WMSG_WORLD_MAP_SKIP);
				pSocket->sendMessage(&ccmd116);
			}

			break;
		}
	case SceneType::CITY:
		{
			PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
			if(info)
			{
				SceneVo* vo = SceneManager::Instance()->getSceneDic(info->playerBaseInfo._mapId);
				if(vo && vo->type == SceneType::CITY)
				{
					CCMD116 ccmd116;
					ccmd116.triggerId = (int16)sceneVo.id;
					GameServerSocket * pSocket = GameServerSocket::getInstance();
					if(pSocket)
					{
						//LayerManager::loadingPic->socketWait_old(WMSG_WORLD_MAP_SKIP);
						pSocket->sendMessage(&ccmd116);
					}
				}
				else
				{
					//Alert.show("Leave Copy?", "", 1, okFunc, null, null, null, null, null, 0);
					//function okFunc():void
					//{
					CCMD116 ccmd116;
					ccmd116.triggerId = (int16)sceneVo.id;
					GameServerSocket * pSocket = GameServerSocket::getInstance();
					if(pSocket)
					{
						//LayerManager::loadingPic->socketWait_old(WMSG_WORLD_MAP_SKIP);
						pSocket->sendMessage(&ccmd116);
					}

						//_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_MAP_ENTER, new Int16(sceneVo.id));
					//}
				}
			}
		break;
		}
	}
}

void SceneListenerMediator::memberExit(SceneVo& sceneVo)
{
	switch(sceneVo.type)
	{
	case SceneType::STORY:
		Message::Instance()->show("Not allowed to enter story scene when in team");
		break;

	case SceneType::COPY:
		Message::Instance()->show("Only leader can enter copy scene when in team");
		break;

	case SceneType::CITY:
		{
			PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
			if(!info)
				break;

			SceneVo* vo = SceneManager::Instance()->getSceneDic(info->playerBaseInfo._mapId);
			if(vo && vo->type == SceneType::CITY)
			{
				CCMD116 ccmd116;
				ccmd116.triggerId = (int16)sceneVo.id;
				GameServerSocket * pSocket = GameServerSocket::getInstance();
				if(pSocket)
				{
					//LayerManager::loadingPic->socketWait_old(WMSG_WORLD_MAP_SKIP);
					pSocket->sendMessage(&ccmd116);
				}

				//_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_MAP_ENTER,new Int16(sceneVo.id));
			}
			else
			{
				Message::Instance()->show("Not allowed to exit copy scene when in team");
			}
			break;

		}
	default:
		break;

	}
}

// when energe is 0 red monster will not attack role 
void SceneListenerMediator::attackMonster(CCNode* n, void* data)
{
	int monsterId = *((int*)data);
	if(monsterId != 0)
	{
		CCMD11E ccmd11e;
		ccmd11e.a_monsterId = monsterId;
		GameServerSocket * pSocket = GameServerSocket::getInstance();
		if(pSocket)
			pSocket->sendMessage(&ccmd11e);

		//_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_REDO_MAP_PROCESS,monsterId);
	}
}

//add by edward from flash
void SceneListenerMediator::dialogNPC(CCNode* n, void* data)
{
	int npcId = *((int*)data);
	if(npcId != 0)
	{
		if(_sceneProxy)
			_sceneProxy->setClickNPC(npcId);

		//if(businessEndCheck(npcId))
		//	return;

		if(meditationCheck(npcId))
			return;
		GameDispatcher::getInstance()->dispatchEvent( PopEventName::SHOW_UI_DIALOGUE, (void*)(&npcId));
	}
}

/**
	* check paoshang over?
	* @param npcId paoshang target NPC
	*/		
bool SceneListenerMediator::businessEndCheck(int npcId)
{
	CityPriceVo* traderNpc = TraderManager::Instance()->getselectedVo();
	if(traderNpc && (traderNpc->npcId == npcId) &&g_pGlobalManage->isOnBusiness())
	{
		sendNotification(Facade_Mediator,
			AppFacade_CITY_TRADER_CHANGE, (char*)0, CityTraderMediator::END_BUSINESS_PROCESS);
		return true;
	}	

	return false;
}

/**
	* if thinking NPC £¨pop up the panel£©
	* @return 
	*/		
bool SceneListenerMediator::meditationCheck(int npcId)
{
	std::vector<ShopVo>* arr = g_pShopManage->getShopsByNPCId(npcId);
	if(!arr)
		return false;

	if(arr->size() < 1)
		return false;

	std::vector<ShopVo>::iterator iter = arr->begin();
	if(iter != arr->end() && iter->type == 9)
	{
		GameDispatcher::getInstance()->dispatchEvent( PopEventName::SHOW_UI_MEDITATION, NULL);
		return true;
	}
	return false;
}

void SceneListenerMediator::elementLayout(CCNode* n, void* data)
{
	if(!data)
		return;

	struct Data
	{
		bool first;
		Element* live;
	};
	Data* d = (Data*)data;
	LiveThing* live = (LiveThing*)d->live;
	bool first = d->first;

	if(!live)
		return;

	CCPoint p1 = live->getMapStartPoint();
	CCPoint newPoint = TileUtil::Instance()->changePixsToTile(ccp(p1.x, p1.y));
	int value;
	CCPoint oldPoint;
	if(!_sceneProxy)
		return;

	if(first)
	{
		value = _sceneProxy->checkTilePoint(newPoint);
		live->toShade(value == 2);
	}
	if(live->type() == PLAYER_TYPE)
	{
		AccountInfoVo* vo = RoleManage::Instance()->accountInfo();
		PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
		if(vo && live->_id == vo->accountId)
		{
			oldPoint = ccp(info->playerBaseInfo.x, info->playerBaseInfo.y);
		}
		else
		{
			oldPoint = _sceneProxy->getOtherPlayerPos(live->_id) ;
		}
	}
	else if(live->type() == NPC_TYPE)
	{
		oldPoint = _sceneProxy->getNPCPos(live->_id) ;
	}
	if(live->type() == NPC_TYPE)
	{
		_sceneProxy->setNPCPos(live->_id, newPoint);
	}
	value = _sceneProxy->checkTilePoint(newPoint);
	live->toShade(value == 2);
}

void SceneListenerMediator::walkStartHandler(CCNode* n, void* data)
{
	std::vector<CCMD110Node> scenePath = changeToCCMD110Node(*((std::vector<CCPoint>*)data));
	CCMD110 ccmd110;
	//std::vector<CCPoint>::iterator iter = scenePath.begin();
	/*for(; iter != scenePath.end(); ++iter)
	{
	CCMD110Node node;
	node.a_x = iter->x;
	node.b_y = iter->y;
	ccmd110.a_path.push_back(node);
	}*/
	ccmd110.a_path = scenePath;
	CCLog("player start move %d point", scenePath.size());
	GameServerSocket* pSocket = GameServerSocket::getInstance();
	if(pSocket)
		pSocket->sendMessage(&ccmd110);

	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(!info)
		return;

	if(info->playerBaseInfo._lev < 15)
	{
		//sendNotification(TaskFollowMediator.ROLE_STOP_TIMING, false);
	}
	else
	{
		//sendNotification(FitnessMediator.IS_ROLE_STOP, false);
	}
}

std::vector<CCMD110Node> SceneListenerMediator::changeToCCMD110Node(std::vector<CCPoint>& path)
{
	std::vector<CCMD110Node> newPath;
	std::vector<CCPoint>::iterator iter = path.begin();
	for(; iter != path.end(); ++iter)
	{
		CCPoint point = *iter;

		CCPoint p = TileUtil::Instance()->changePixsToTile(ccp(iter->x, iter->y));
		CCMD110Node obj;
		obj.a_x = int16(p.x);
		obj.b_y = int16(p.y);
		newPath.push_back(obj);
	}
	return newPath;
}

void SceneListenerMediator::walkStartNodeHandler(CCNode* n, void* data)
{
	std::vector<CCPoint>* d = (std::vector<CCPoint>*)data;
	std::vector<CCPoint> scenePath = changeToMapPoint(*d);

	std::vector<CCPoint>::iterator iter = scenePath.begin();
	CCMD114 obj;
	obj.a_x = int16(iter->x);
	obj.b_y = int16(iter->y);
	CCLog("player move to (%d,%d) and go to (%f,%f)", obj.a_x, obj.b_y,  scenePath[1].x, scenePath[1].y);

	GameServerSocket::getInstance()->sendMessage(&obj);
}

void SceneListenerMediator::tradeWalkStartNodeHandler(CCNode* n, void* data)
{
	std::vector<CCPoint>* d = (std::vector<CCPoint>*)data;
	std::vector<CCPoint> scenePath = changeToMapPoint(*d);

	std::vector<CCPoint>::iterator iter = scenePath.begin();
	CCMD0F0 obj;
	obj.a_x = int16(iter->x);
	obj.b_y = int16(iter->y);
	CCLog("trade player move to (%d,%d) and go to (%f,%f)", obj.a_x, obj.b_y,  scenePath[1].x, scenePath[1].y);

	GameServerSocket::getInstance()->sendMessage(&obj);
}

void SceneListenerMediator::walkPathChangeHandler(CCNode* n, void* data)
{
	CCPoint* p = (CCPoint*)data;
	CCPoint point = TileUtil::Instance()->changePixsToTile(*p);
	CCMD115 obj;
	obj.a_x = int16(point.x);
	obj.b_y = int16(point.y);

	GameServerSocket* pSocket = GameServerSocket::getInstance();
	if(pSocket)
		pSocket->sendMessage(&obj);
}

void SceneListenerMediator::clickPlayerHandler(CCNode* n, void* data)
{
	//this.sendNotification(PlayerMediator.STARTUP_PLAYER_UI, e.param);
}

void SceneListenerMediator::cancelPlayerHandler(CCNode* n, void* data)
{
	//this.sendNotification(PlayerMediator.REMOVE_VIEW);
}

void SceneListenerMediator::createPlayerFinish(CCNode* n, void* data)
{
	playerMoveHandler((SCMD111*)data);
}

void SceneListenerMediator::createTradePlayerFinish(CCNode* n, void* data)
{
	sendNotification(Facade_Command, AppFacade_SCENEPROXY_COMMAND, (char*)data, SceneProxyCommand::MOVE_TRADEPLAYER);
}

void SceneListenerMediator::playerViewGetHandler(SCMD11A* cmd)
{
	sendNotification(Facade_Command, AppFacade_SCENEPROXY_COMMAND, (char*)cmd, SceneProxyCommand::ADD_PLAYER);
}

void SceneListenerMediator::tradeplayerViewGetHandler(SCMD0F1* cmd)
{
	sendNotification(Facade_Command, AppFacade_SCENEPROXY_COMMAND, (char*)cmd, SceneProxyCommand::CREAT_TRADEPLAYER);
}

void SceneListenerMediator::creatTradeHandler(SCMD12D* cmd)
{
	sendNotification(Facade_Command, AppFacade_SCENEPROXY_COMMAND, (char*)cmd, SceneProxyCommand::ADD_TRADEPLAYER);
}

void SceneListenerMediator::tradeplayerViewOutHandler(SCMD0F2* cmd)
{
	//CCLog("playerViewOutHandler");
	sendNotification(Facade_Command, AppFacade_SCENEPROXY_COMMAND, (char*)cmd, SceneProxyCommand::REMOVE_TRADEPLAYER);
}

/**
* relocation role position
* @param param
* 
*/		
void SceneListenerMediator::resetLocation(SCMD11C* cmd)
{
	if(!cmd)
		return;

	CCPoint point = ccp(cmd->a_x, cmd->b_y);
	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	
	if(!info)
		return;

	info->playerBaseInfo.x = point.x;
	info->playerBaseInfo.y = point.y;
	CCPoint pos = TileUtil::Instance()->changeTileToPixs(point);
	sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, NULL, SceneMediator::ROLE_STOP);
	sendNotification(Facade_Command, AppFacade_SCENEPROXY_COMMAND, (char*)(&pos), SceneProxyCommand::ROLE_POS_CHANGE);
}

void SceneListenerMediator::findElementHandler(CCNode* n, void* data)
{
	FindVo* findVo = (FindVo*)data;
	findElement(findVo);
}

void SceneListenerMediator::findElement(FindVo* findVo)
{
	if(!_sceneProxy || !findVo || !_sceneProxy->isSceneOpened(findVo->_sceneId))
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("COM633").c_str());
		return;
	}
	if(_fightProxy && _fightProxy->battleId != 0 )
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("COM634").c_str());
		return;
	}

	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(!info)
		return;

	SceneVo* sceneVo = SceneManager::Instance()->getSceneDic(info->playerBaseInfo._mapId);

	if(!sceneVo)
		return;

	if(sceneVo->type == SceneType::COPY)
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("COM635").c_str());
		return;
	}

	
	//int newTaskId = 0;
	FindVo newFindVo;
	//if(newTaskId > 0 && newTaskId <= 100)
	//{
	//	newFindVo = MapManage::Instance()->changeFindVoHandler(*findVo);
	//}
	//else
	//{
	//	newFindVo = *findVo;
	//}

	newFindVo = MapManage::Instance()->changeFindVoHandler(*findVo);

	if(newFindVo._sceneId == info->playerBaseInfo._mapId)
	{
		if(newFindVo._type == TaskType::EXIT)
		{
			sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*) &(newFindVo._npcId), SceneMediator::ROLE_TO_EXIT);
			MapManage::Instance()->findPath(MapManage::Instance()->nextFindVo());
		}
		else if(newFindVo._npcId>0)
		{
			sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*) &(newFindVo._npcId), SceneMediator::ROLE_TO_NPC);
		}
		else
		{
			Message::Instance()->show("Current point is the dest point");
		}
	}
	else
	{
		MapManage::Instance()->findPath(newFindVo);
		if(newFindVo._isShowWorldMap)
		{
			//Doyang 20120717
			int i = newFindVo._sceneId;
			GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::SHOW_UI_MAP, &i);
		}
		else
		{
			triggerExit(NULL, (void*)(&(newFindVo._sceneId)));
		}
	}
}

void SceneListenerMediator::roleMoveHandler(SCMD11B* cmd)
{
	if(cmd)
		gotoScene(cmd->a_type, cmd->b_id);
}


void SceneListenerMediator::gotoScene(int type, int id)
{
	switch(type)
	{
	case EventType::STORY:
		if (!g_pGlobalManage->_isInFight/* && g_pGlobalManage->getIsStorySystemOpen()*/)
		{
			sendNotification(Facade_Mediator,AppFacade_SCENESTORY_PROXY_CHANGE,(char*)(&id),SceneStoryMediator::ROLE_MOVETOTARGET_STARTSTORY);
		}
		break;
	case EventType::ANIMATION:
		break;
	case EventType::PVE:
		sendNotification(Facade_Proxy, AppFacade_FIGHT_PROXY_CHANGE, (char*)(&id), SceneFightProxyCommand::INIT_PVE_SCENEVO);
		break;
	case EventType::PVP:
		sendNotification(Facade_Proxy, AppFacade_FIGHT_PROXY_CHANGE, (char*)(&id), SceneFightProxyCommand::INIT_PVP_SCENEVO);
		break;
	}
}

void SceneListenerMediator::playerMoveHandler(SCMD111* cmd)
{
	if(cmd == NULL)
		return;

	AccountInfoVo* info = RoleManage::Instance()->accountInfo();
	if(info == NULL)
		return;

	if(cmd->a_AccountId == info->accountId)
		return;

	sendNotification(Facade_Command, AppFacade_SCENEPROXY_COMMAND, (char*)cmd, SceneProxyCommand::MOVE_PLAYER);	
}

void SceneListenerMediator::tradeplayerMoveHandler(SCMD12F* cmd)
{
	if(cmd == NULL)
		return;

	AccountInfoVo* info = RoleManage::Instance()->accountInfo();
	if(info == NULL)
		return;

	//if(cmd->a_AccountId == info->accountId)
	//	return; 

	sendNotification(Facade_Command, AppFacade_SCENEPROXY_COMMAND, (char*)cmd, SceneProxyCommand::MOVE_TRADEPLAYER);
}

void SceneListenerMediator::playerViewInHandler(SCMD112* cmd)
{
	//CCLog("playerViewInHandler");
	//SCMD112OR11A
	sendNotification(Facade_Command, AppFacade_SCENEPROXY_COMMAND, (char*)cmd, SceneProxyCommand::ADD_PLAYER);

}

void SceneListenerMediator::playerViewOutHandler(SCMD113* cmd)
{
	//CCLog("playerViewOutHandler");
	sendNotification(Facade_Command, AppFacade_SCENEPROXY_COMMAND, (char*)cmd, SceneProxyCommand::REMOVE_PLAYER);
}

void SceneListenerMediator::roleMapSkip(SCMD118* cmd)
{
	struct Data
	{
		int sceneId;
		void* window;
		Data()
		{
			sceneId = 0;
			window = NULL;
		}
	};

	Data d;
	d.sceneId = 0;
	d.window = NULL;

	GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_TEAM_ROOM, (void*)(&d));
	sendNotification(Facade_Command, AppFacade_SCENEPROXY_COMMAND, (char*)cmd, SceneProxyCommand::MAP_SKIP);

	g_pGlobalManage->setIsInWordMap(false);
	g_pGlobalManage->showAllUI(true);

	
	if ((SceneManager::Instance()->getCurMapType() == SceneType::CITY) && ViewManager::getInstance()->mainNavigate)
	{
		ViewManager::getInstance()->mainNavigate->hideOutMap();
	}

	if ((SceneManager::Instance()->getCurMapType() != SceneType::CITY) )
	{
		NewHandView::Instance()->clearArrowRectangle(); //onMainNavigateChange(false);
		NewhandManager::Instance()->touchNextEvent(503);
		NewhandManager::Instance()->setNewHandStateByType(LevLimitConst::Limit_ChallegeCopy , NewhandManager::Flag_Close);
		NewhandManager::Instance()->setNewHandStateByType(LevLimitConst::Limit_Entrance , NewhandManager::Flag_Close);
	}
}

	
void SceneListenerMediator::initProcess(SCMD11D* cmd)
{
	sendNotification(Facade_Command, AppFacade_SCENEPROXY_COMMAND, (char*)cmd, SceneProxyCommand::INIT_PROCESS);
	if(g_pGlobalManage && g_pGlobalManage->_isEnterGame == false)
		g_pGlobalManage->_isEnterGame = true;
	continueFindPath();

	//jae note 20120718 
	if ( g_pLoginManage->_pLoginView )
	{
		if ( g_pLoginManage->_pLoginView->getParent() )
		{
			g_pLoginManage->_pLoginView->removeFromParentAndCleanup(true);
		}
	 	g_pLoginManage->_pLoginView->release();
		g_pLoginManage->_pLoginView = 0;


		g_pGlobalManage->d2 = Timer::millisecondNow();
		CCLog("-----------------loading begin to progress 4 use: %d ,%f s",
			(g_pGlobalManage->d2-g_pGlobalManage->d1), (g_pGlobalManage->d2-g_pGlobalManage->d1)*0.001 );

		g_pGlobalManage->m_bLoadingOver = true;
	}
}

void SceneListenerMediator::continueFindPath()
{
	if(MapManage::Instance()->isAutoFindPath == true)
	{
		FindVo findVo = MapManage::Instance()->findVo();
		if(findVo._type == TaskType::EXIT)
		{
			sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)(findVo._npcId), SceneMediator::ROLE_TO_EXIT);
			//if(_mapManage.nextFindVo)
			//{
				MapManage::Instance()->findPath(MapManage::Instance()->nextFindVo());
			//}
		}
		else if(findVo._npcId > 0)
		{
			sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)(&(findVo._npcId)), SceneMediator::ROLE_TO_NPC);
		}
		else
		{
			MapManage::Instance()->cancelAutoPath();
		}
	}
}

void SceneListenerMediator::addProcess(SCMD120* cmd)
{
	CCLog("addProcess");
	sendNotification(Facade_Command, AppFacade_SCENEPROXY_COMMAND, (char*)cmd, SceneProxyCommand::ADD_PROCESS);
}

/**
* pve 
* @param param
* 
*/		
void SceneListenerMediator::pveFightStart(SCMD131* cmd)
{
	//this.sendNotification(MainUIMediator.SET_QUIT_BTN_ENABLED, false);
	if(g_pGlobalManage)
		g_pGlobalManage->isReport = false;
	sendNotification(Facade_Command, AppFacade_FIGHT_PROXY_CHANGE, (char*)cmd, SceneFightProxyCommand::INIT_PVE_DATA);
	//sendNotification(Facade_Mediator, AppFacade_SCENEWORLD_MEDIATOR, NULL, SceneWorldMediator::REMOVE_WORLD_SCENE);kevinchange0817
}

void SceneListenerMediator::pveReportFightStart(SCMD135* cmd)
{
	if(g_pGlobalManage)
		g_pGlobalManage->isReport = false;
	sendNotification(Facade_Command, AppFacade_FIGHT_PROXY_CHANGE, (char*)cmd, SceneFightProxyCommand::INIT_PVE_DATA);
	sendNotification(Facade_Mediator, AppFacade_SCENEWORLD_MEDIATOR, NULL, SceneWorldMediator::REMOVE_WORLD_SCENE);
}

/**
	* pvp 
	* @param param
	* 
	*/		
void SceneListenerMediator::pvpFightStart(SCMD13C* cmd)
{
	//Begin chenjian 20121019
	if(g_pGlobalManage)
		g_pGlobalManage->isReport = false;
	//End chenjian 20121019

	sendNotification(Facade_Command, AppFacade_FIGHT_PROXY_CHANGE, (char*)cmd, SceneFightProxyCommand::INIT_PVP_SCENEVO);
	sendNotification(Facade_Command, AppFacade_FIGHT_PROXY_CHANGE, (char*)cmd, SceneFightProxyCommand::INIT_PVP_DATA);
//	sendNotification(Facade_Mediator, AppFacade_SCENEWORLD_MEDIATOR, NULL, SceneWorldMediator::REMOVE_WORLD_SCENE);kevinchange0817
}

void SceneListenerMediator::updateRole(SCMD139* cmd)
{
}

void SceneListenerMediator::worldProcess(SCMD124* cmd)
{
	sendNotification(Facade_Command, AppFacade_SCENEPROXY_COMMAND, (char*)cmd, SceneProxyCommand::ADD_SCENE_PROCESS);
}

	
void SceneListenerMediator::playerLevelUp(SCMD35D* cmd)
{
	if(ViewManager::getInstance()->scene())
	{
		ViewManager::getInstance()->scene()->levUpEffect(cmd->a_accountId);
	}
}

void SceneListenerMediator::merAttributeChange(SCMD35F* cmd)
{
	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(!info)
		return;

	if(info->playerBaseInfo.id == cmd->a_id)
	{
		//info->playerBaseInfo._maxHp = cmd->b_maxHp;
		//info->playerBaseInfo._hp = cmd->b_maxHp;
		//info->figureBaseInfo.stamina = cmd->j_sta;
		//info->figureBaseInfo.strength = cmd->h_str;
		//info->figureBaseInfo.intellect = cmd->i_int;
		//info->figureBaseInfo.plus_int = cmd->l_plusInt;
		//info->figureBaseInfo.plus_sta = cmd->m_plusSta;
		//info->figureBaseInfo.plus_str = cmd->k_plusStr;

		info->figureBaseInfo.mAttack = cmd->e_DmagicAttack;
		info->figureBaseInfo.mDefense = cmd->g_DmagicDefend;
		info->figureBaseInfo.pDefense = cmd->f_DphsicsDefend;
		info->figureBaseInfo.pAttack = cmd->d_DphsicsAttack;
		info->playerBaseInfo._maxHp = cmd->b_maxHp;
		info->playerBaseInfo._hp = cmd->b_maxHp;
		info->figureBaseInfo.stamina = cmd->j_sta;
		info->figureBaseInfo.strength = cmd->h_str;
		info->figureBaseInfo.intellect = cmd->i_int;
		info->figureBaseInfo.plus_int = cmd->l_plusInt;
		info->figureBaseInfo.plus_sta = cmd->m_plusSta;
		info->figureBaseInfo.plus_str = cmd->k_plusStr;
		info->figureBaseInfo.sp_int = cmd->o_sp_Int;
		info->figureBaseInfo.sp_sta = cmd->p_sp_Sta;
		info->figureBaseInfo.sp_str = cmd->n_sp_Str;

		// LH20130118
		RoleManage::Instance()->updateMercenaryEx(cmd->a_id , info);
	}
	else
	{
		PlayerInfoVo * merc = RoleManage::Instance()->getMercenary(cmd->a_id);
		if(!merc)
			return;
		//merc->playerBaseInfo._maxHp = cmd->b_maxHp;
		//merc->playerBaseInfo._hp = cmd->b_maxHp;
		//merc->figureBaseInfo.stamina = cmd->j_sta;
		//merc->figureBaseInfo.strength = cmd->h_str;
		//merc->figureBaseInfo.intellect = cmd->i_int;
		//merc->figureBaseInfo.plus_int = cmd->l_plusInt;
		//merc->figureBaseInfo.plus_sta = cmd->m_plusSta;
		//merc->figureBaseInfo.plus_str = cmd->k_plusStr;

		merc->figureBaseInfo.mAttack = cmd->e_DmagicAttack;
		merc->figureBaseInfo.mDefense = cmd->g_DmagicDefend;
		merc->figureBaseInfo.pDefense = cmd->f_DphsicsDefend;
		merc->figureBaseInfo.pAttack = cmd->d_DphsicsAttack;
		merc->playerBaseInfo._maxHp = cmd->b_maxHp;
		merc->playerBaseInfo._hp = cmd->b_maxHp;
		merc->figureBaseInfo.stamina = cmd->j_sta;
		merc->figureBaseInfo.strength = cmd->h_str;
		merc->figureBaseInfo.intellect = cmd->i_int;
		merc->figureBaseInfo.plus_int = cmd->l_plusInt;
		merc->figureBaseInfo.plus_sta = cmd->m_plusSta;
		merc->figureBaseInfo.plus_str = cmd->k_plusStr;
		merc->figureBaseInfo.sp_int = cmd->o_sp_Int;
		merc->figureBaseInfo.sp_sta = cmd->p_sp_Sta;
		merc->figureBaseInfo.sp_str = cmd->n_sp_Str;

		// LH20121020
		RoleManage::Instance()->updateMercenaryEx(cmd->a_id , merc);

	}
	

	//// update figure view
	//FigureMainView * fMainView = ViewManager::getInstance()->figureView;//Jae note:error when strenghen equipment
	//if (fMainView&&(fMainView->_figureV)&&fMainView->_figureV->getIsVisible())
	//{
	//	if (fMainView->_figureV->_attrLayer)
	//	{
	//		fMainView->_figureV->_attrLayer->loadItems();
	//	}
	//	if (g_pFigureScrollView && g_pFigureScrollView->getIsVisible())
	//	{
	//		g_pFigureScrollView->showEquipInfo();//Jae add:error in when update equip
	//	}
	//}
}

void SceneListenerMediator::walkCompleteHandler(CCNode* n, void* data)
{
	if(data == NULL)
		return;

	CCPoint* pos = (CCPoint*)data;
	CCPoint point = TileUtil::Instance()->changePixsToTile(*pos);

	CCMD114 s;
	s.a_x = (int16)(point.x);
	s.b_y = (int16)(point.y);

	CCLog("Player move to the last point (%d, %d)", s.a_x, s.b_y);

	GameServerSocket* pSocket = GameServerSocket::getInstance();
	if (pSocket)
		pSocket->sendMessage(&s);

	//if(g_pGlobalManage->isOnMeditation())
	//{
		//sendNotification(MeditationMediator.MEDITATION_MOVE_END);
	//}

	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(!info)
		return;

	if(info->playerBaseInfo._lev < 15)
	{
		//sendNotification(TaskFollowMediator.ROLE_STOP_TIMING, true);
	}
	else
	{
		//sendNotification(FitnessMediator.IS_ROLE_STOP, true);
	}
}