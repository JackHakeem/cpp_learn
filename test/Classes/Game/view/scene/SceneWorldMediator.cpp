#include "SceneWorldMediator.h"
#include "events/GameDispatcher.h"
#include "SceneMediator.h"
#include "manager/layer/MapManage.h"
#include "model/scene/vo/SceneType.h"
#include "socket/command/c11/CCMD116.h"
#include "model/scene/SceneManager.h"
#include "manager/RenderManage.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "Message.h"
#include "model/player/vo/AccountInfoVo.h"
#include "model/player/RoleManage.h"
#include "model/scene/vo/FuncExitVo.h"
#include "manager/LayerManager.h"
#include "manager/ViewManager.h"
#include "manager/PopEventName.h"
#include "manager/GlobalManage.h"
#include "components/MainScene.h"
#include "model/dungeonEntrys/DungeonEntrysManage.h"
#include "Alert.h"
#include "utils/ValuesUtil.h"
#include "model/newhand/vo/TestNewhand.h"
#include "../GameView.h"


SceneWorldMediator::SceneWorldMediator()
{
	_worldScene = NULL;
	_sceneVoid = 0;

	GameDispatcher::getInstance()->addEventListener(GameDispatcher::SHOW_UI_MAP, this, callfuncND_selector(SceneWorldMediator::showMap));
	//GameDispatcher::getInstance()->addEventListener(GameDispatcher::SHOW_UI_MAP, this, callfuncND_selector(SceneWorldMediator::showMap));
	GameDispatcher::getInstance()->addEventListener(GameDispatcher::TRIGGER_EXIT, this, callfuncND_selector(SceneWorldMediator::triggerExit));
	GameDispatcher::getInstance()->addEventListener(GameDispatcher::BACK_TOWN, this, callfuncND_selector(SceneWorldMediator::backTown));
}
void SceneWorldMediator::handleNotification( int M2Vcmd, char* data )
{
	switch(M2Vcmd)
	{
	case CREATE_WORLD_SCENE:
		createWorldSceneHandle();
		break;
	case CLOSE_WORLD_SCENE:
		closeWorldScene();
		break;
	case REMOVE_WORLD_SCENE:
		returnPreMap();
		break;
	case INIT_PROGRESS:
		{
			int id = *((int*)data);
			resetLayerStar(id);
			break;
		}
	case WORLDBOSS_VISIBLE:
		if(_worldScene)
		{
			/*int id = *((int*)data);
			WorldExit* worldBossExit = _worldScene->getExit(id);
			if(worldBossExit)
			{
				worldBossExit->openExit();
			}*/
		}
		break;
	case WORLDBOSS_TIPS:
		/*var param:Object = notification.getBody();
		if(_worldScene)
		{
			var worldBossExit1:WorldExit = _worldScene.getExit(param.mapID);
			if(worldBossExit1){
				var tips:String = param.tips;
				worldBossExit1.setTips(tips);
			}
		}*/
		break;

	default:
		break;
	}

}

void SceneWorldMediator::showMap(CCNode* n, void* data)
{
	if(data == NULL)
	{
		MapManage::Instance()->cancelAutoPath();
		sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, NULL, SceneMediator::ROLE_STOP);
	}
	int i = 0;
	if(data)
	{
		i = *(int *) data;
	}

	if(_sceneProxy && _sceneProxy->_sceneInfoVo
		&& _sceneProxy->_sceneInfoVo->type == 2)
	{
		int cityId = i == 0 ? DungeonEntrysManage::Instance()->getCityIDByMapID(_sceneProxy->_sceneInfoVo->id) : i;
		CCMD116 ccmd116;
		ccmd116.triggerId = (int16)cityId;
		GameServerSocket * pSocket = GameServerSocket::getInstance();
		if(pSocket)
		{
			//LayerManager::loadingPic->socketWait_old(WMSG_WORLD_MAP_SKIP);
			pSocket->sendMessage(&ccmd116);
		}
	}
	else
		createWorldSceneHandle();
}

void SceneWorldMediator::startListener()
{
	if(_worldScene)
	{
		_worldScene->addEventListener(SceneConst::MAP_BG_INIT, this, callfuncND_selector(SceneWorldMediator::addExit));
		_worldScene->addEventListener(SceneConst::ROLE_MOVE, this, callfuncND_selector(SceneWorldMediator::roleMove));
		_worldScene->addEventListener(SceneConst::TRIGGER_EXIT, this, callfuncND_selector(SceneWorldMediator::triggerExit));
		_worldScene->addEventListener(SceneConst::SHOW_CHILD_SCENE, this, callfuncND_selector(SceneWorldMediator::showChildScene));
		_worldScene->addEventListener(SceneConst::CHILD_EXIT_CLICK, this, callfuncND_selector(SceneWorldMediator::childExitClick));
	}
}

void SceneWorldMediator::childExitClick(CCNode* n, void* data)
{
	if(_worldScene && data)
	{
		currElement._otherInfos[0] = *((int*)data);
		_worldScene->roleMoveElement(&currElement);
	}
}

void SceneWorldMediator::addExit(CCNode* n, void* data)
{
	std::vector<SceneVo*> array = SceneManager::Instance()->getWorldSceneDic();
	for(std::vector<SceneVo*>::iterator iter = array.begin();
		iter != array.end(); ++iter)
	{
		//CCLog("-----------map id:%d, resId:%s, x:%d, y:%d", (*iter)->id, (*iter)->resid.c_str(), (*iter)->x, (*iter)->y);
		if(*iter == NULL)
			continue;

		ExitVo element;
		element._id = (*iter)->id;
		element._resId =  (*iter)->resid;
		element.x =  (*iter)->x;
		element.y = (*iter)->y;
		element._name = (*iter)->name;
		element.isPid = true;
		element.otherInfos.push_back((*iter)->id);
		element.isOpend = _sceneProxy->isSceneOpened((*iter)->id);
		element.isCity = (*iter)->type == SceneType::CITY;
		//element.isDuplicate = (*iter)->id > 1200;
		if(_worldScene && ((element.isOpend && (*iter)->type != SceneType::COPY) || element.isCity))
			_worldScene->addExit(&element);
	}
	char type[] = "world";
	TestNewhand *pNewhand = new TestNewhand(type,0,0);
	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::TEST_NEW_HAND, (void*)pNewhand);
	CC_SAFE_DELETE(pNewhand);
	addRole();
	findExit();
}

void SceneWorldMediator::addRole()
{
	if(_worldScene)
		_worldScene->addRole();
}

void SceneWorldMediator::returnPreMap()
{
	closeWorldScene();
	RenderManage::Instance()->start();
}

void SceneWorldMediator::triggerExit(CCNode* n, void* data)
{
	if(!data)
		return;

	if(_worldScene && _worldScene->isTeamRoomPop())
	{
		return;
	}

	//PopManage::
	//PopUpManager.closeAllWindows();   // close all Alert window

	//StageProxy.ReDrawSrceen();

	int triggerId = *((int*)data);
	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(!info)
		return;

	if(triggerId == info->playerBaseInfo._mapId)
	{
		if(g_pGlobalManage->isOnBusiness())
		{
			g_pGlobalManage->_isOnBusiness = false;
			//Message::Instance()->show("paoshang, cannot return to the priv window");
		}

		{
			returnPreMap();//new hand guild
			/*struct Data
			{
				std::string type;
				int id;
				Data()
				{
					id = 0;
				}
			};

			Data d;
			d.type = "map";*/
			//Doyang 20120712
			TestNewhand *pTestNewhand = new TestNewhand("map", NULL, 0);
			GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::TEST_NEW_HAND, 
				 pTestNewhand);
			CC_SAFE_DELETE(pTestNewhand);
		}
		return;
	}

	SceneVo* sceneVo = SceneManager::Instance()->getSceneDic(triggerId);
	AccountInfoVo * accinfo = RoleManage::Instance()->accountInfo();

	if(!sceneVo || !accinfo)
		return;

	if(accinfo->team == 0)
	{
		CCMD116 ccmd116;
		ccmd116.triggerId = (int16)triggerId;

		GameServerSocket * pSocket = GameServerSocket::getInstance();
		if(pSocket)
		{
			//LayerManager::loadingPic->socketWait_old(WMSG_WORLD_MAP_SKIP);
			pSocket->sendMessage(&ccmd116);
		}

		//sendNotification(TraderMediator.CLOSE);
	}
	else if(accinfo->team == 1)
	{
		captainExit(sceneVo);
	}
	else if(accinfo->team == 2)
	{ 
		memberExit(sceneVo);
	}
}

void SceneWorldMediator::captainExit(SceneVo* sceneVo)
{
	if(!sceneVo)
		return;

	switch(sceneVo->type)
	{
	case SceneType::STORY:
		Message::Instance()->show("Non Team not allowed to enter story");
		break;

	case SceneType::COPY:
		{
			CCMD116 ccmd116;
			ccmd116.triggerId = (int16)(sceneVo->id);

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
			if(!info)
				break;

			SceneVo* vo = SceneManager::Instance()->getSceneDic(info->playerBaseInfo._mapId);
			if(!vo)
				break;

			if(vo->type == SceneType::CITY)
			{
				CCMD116 ccmd116;
				ccmd116.triggerId = (int16)(sceneVo->id);

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
				Alert* alert = new Alert();
				if(alert)
					addChild(alert);
				alert->addStr(ValuesUtil::Instance()->getString("SCE030").c_str(), ccc3(254, 189, 0));
				_sceneVoid = sceneVo->id;
				alert->addButton(ValuesUtil::Instance()->getString("CF001").c_str(), this, menu_selector(SceneWorldMediator::okFunc));
				alert->addButton(ValuesUtil::Instance()->getString("CF002").c_str(), this, menu_selector(SceneWorldMediator::cancelFunc));
				alert->centerShow();
				alert->release();
				/*Alert.show(LangManager.getText("SCE030"), "", 1, okFunc, null, null, null, null, null, 0);
				function okFunc():void{
					_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_MAP_ENTER, new Int16(sceneVo.id));
				}
				this.sendNotification(TraderMediator.CLOSE);*/
			}
			break;
		}
	}
}

void SceneWorldMediator::okFunc()
{
	CCMD116 ccmd116;
	ccmd116.triggerId = (int16)(_sceneVoid);

	GameServerSocket * pSocket = GameServerSocket::getInstance();
	if(pSocket)
	{
		//LayerManager::loadingPic->socketWait_old(WMSG_WORLD_MAP_SKIP);
		pSocket->sendMessage(&ccmd116);
	}
}

void SceneWorldMediator::cancelFunc()
{

}

void SceneWorldMediator::memberExit(SceneVo* sceneVo)
{
	if(!sceneVo)
		return;

	switch(sceneVo->type)
	{
	case SceneType::STORY:
		Message::Instance()->show(ValuesUtil::Instance()->getString("SCE031"));
		break;

	case SceneType::COPY:
		Message::Instance()->show(ValuesUtil::Instance()->getString("SCE032"));
		break;

	case SceneType::CITY:
		{
			PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
			if(!info)
				break;

			SceneVo* svo = SceneManager::Instance()->getSceneDic(info->playerBaseInfo._mapId);
			if(!svo)
				return;

			if(svo->type == SceneType::CITY)
			{
				CCMD116 ccmd116;
				ccmd116.triggerId = (int16)(sceneVo->id);

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
				Message::Instance()->show(ValuesUtil::Instance()->getString("SCE033"));
			}
			break;
		}
	}
}

void SceneWorldMediator::backTown(CCNode* n, void* data)
{
	FindVo findVo;
	//FuncExitVo* funcExitVo = NULL;
	//int d = *((int*)data);
	//switch(d)
	//{
	//case EventAlert::RECRUIT_TYPE:
	//	{
	//		findVo._type= TaskType::NPC;
	//		findVo._sceneId = 1001;
	//		findVo._npcId = 1;
	//		funcExitVo = FuncExitManager::Instance()->getFuncExit(FuncExitManager::TYPE_FIGHT, _crystalProxy->getCrystalLev(CrystalType::CRYSTAL_MAIN) );
	//		if(funcExitVo)
	//		{
	//			findVo._sceneId = funcExitVo->mapId;
	//			findVo._npcId = funcExitVo->npcId;
	//		}
	//		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher.FIND_ELEMENT, (void*)(&findVo));
	//		//_dispatcher.dispatchEvent(new ParamEvent(GameDispatcher.FIND_ELEMENT, findVo));
	//		break;
	//	}
	//case EventAlert::FIGHT_TYPE:

	//	break;
	//} 
}


void SceneWorldMediator::createWorldSceneHandle()
{
	//ModuleLoaderManage.getInstance().load(ResourceName.WORLD_SKIN_PATH, LoadLevel.HIGH, createWorldScene);

	createWorldScene();
}

void SceneWorldMediator::createWorldScene()
{
	if(_worldScene == NULL)
	{
		_worldScene = new WorldScene();

	}

	/*if(!LayerManager::worldLayer)
	LayerManager::worldLayer = new WorldLayer();*/
	if(LayerManager::worldLayer != _worldScene)
		LayerManager::worldLayer = _worldScene;

	if(LayerManager::worldLayer->getParent() == NULL)
	{
		//MainScene::Instance()->addChild(LayerManager::worldLayer, 10000);
		if (g_pGameView) // modify by LH 0727
		{
			g_pGameView->addChild(LayerManager::worldLayer, 120);
		}
		
		_worldScene->release();//jae
	}

	//if(_worldScene->getParent() == NULL)
	//	LayerManager::worldLayer->addChild(_worldScene);

	g_pGlobalManage->setCurFocusGID(LayerManager::worldLayer->getMyFocusGID());

	startListener();

	std::string url = "assets/mapassets/scene/worldfront/map.jpg";

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	_worldScene->buildScene(size.width,
							size.height,
							0,
							0,
							0,
							url,
							ccp(size.width / 2, size.height / 2));

	_worldScene->dispatchEvent(SceneConst::BUILD, NULL);
	_worldScene->dispatchEvent(SceneConst::MAP_BG_INIT, NULL);
	ViewManager::getInstance()->worldScene = _worldScene;
}

void SceneWorldMediator::findExit()
{
	if(MapManage::Instance()->isAutoFindPath == true)
	{
		FindVo findVo = MapManage::Instance()->findVo();
		SceneVo* sceneVo = SceneManager::Instance()->getSceneDic(findVo._sceneId);
		if(!sceneVo)
			return;

		int id = 0;
		if(sceneVo->pid == 0)
		{
			id = sceneVo->id;
		}
		else
		{
			id= sceneVo->pid;
		}
		_worldScene->showChildSceneAutoFindPath(id);
	}
}

void SceneWorldMediator::roleMove(CCNode* n, void* data)
{
	if(!data)
		return;

	struct Data
	{
		CCPoint endPoint;
		float ranger;
		Data()
		{
			ranger = 0.0f;
		}
	};
	Data* d = (Data*)data;

	CCPoint endScenePoint = d->endPoint;
	std::vector<CCPoint> scenePath;
	scenePath.push_back(endScenePoint);
	if(_worldScene)
		_worldScene->movePath(scenePath);
}

void SceneWorldMediator::showChildScene(CCNode* n, void* data)
{
	if(!data)
		return;

	struct Data
	{
		bool auto1;
		IElement* element;
		Data()
		{
			auto1 = false;
			element = NULL;
		}
	};

	Data* d = (Data*)data;
	bool auto1 = d->auto1;
	IElement* element = d->element;

	if(!element)
		return;

	if(element->_id == 0)
	{
		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::INTO_SILVERMINE, NULL);
		return;
	}

	currElement = *element;
	SceneVo* sceneVo = SceneManager::Instance()->getSceneDic(element->_id);
	if(!sceneVo)
		return;

	if(sceneVo->type == SceneType::COPY)
	{
		if(_worldScene)
			_worldScene->isTeamRoomPop(true);
		struct Data
		{
			int sceneId;
			BaseScene* scene;
			Data()
			{
				sceneId = 0;
				scene = NULL;
			}
		};
		Data d;
		d.sceneId = element->_id;
		d.scene = _worldScene;
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_TEAM_ROOM, (void*)(&d));
		return;
	}

	struct Data1
	{
		std::string type;
		int id;
		Data1()
		{
			id = 0;
		}
	};

	std::vector<int>* array = SceneManager::Instance()->getChildByPid(element->_id);
	if(array && array->size() > 0)
	{
		if(auto1)
		{
			currElement._otherInfos[0] = MapManage::Instance()->_findVo._sceneId;
			if(_worldScene)
				_worldScene->roleMoveElement(&currElement);
			
			/*Data1 d;
			d.type = "child";
			d.id =  element->_id;*/
			//Doyang 20120712
			TestNewhand *pTestNewhand = new TestNewhand("child", NULL, element->_id);
			GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::TEST_NEW_HAND, 
				pTestNewhand);
			CC_SAFE_DELETE(pTestNewhand);
			return;
		}
		
		
		std::vector<WorldExitData> _array;
		for(std::vector<int>::iterator iter = array->begin();
			iter != array->end(); ++iter)
		{
			bool state = _sceneProxy->isSceneOpened(*iter);
			/*int areaStar = PerfectManager::Instance()->getMapStarLev(id);
			if(areaStar==-1)
			{
				_wSocket.sendMessage(SocketCMDConst::CMSG_WORLD_PROCESS_GET_PERFECT, new Int16(id));
			}*/

			if(state)
			{
				sceneVo = SceneManager::Instance()->getSceneDic(*iter);
				if(sceneVo)
				{
					WorldExitData d;
					d.id = sceneVo->id;
					d.name = sceneVo->name;
					d.state = 1;
					_array.push_back(d);
				}
			}
		}
		if(_worldScene)
			_worldScene->showChildSceneHandle(_array, currElement);
		/*Data1 d1;
		d1.id = element->id();
		d1.type = "child";*/
		//Doyang 20120712
		TestNewhand *pTestNewhand = new TestNewhand("child", NULL, element->id());
		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::TEST_NEW_HAND, 
			pTestNewhand);
		CC_SAFE_DELETE(pTestNewhand);
	}
	else
	{
		if(_worldScene)
			_worldScene->roleMoveElement(element);
	}
}

SceneWorldMediator::~SceneWorldMediator()
{

}

void SceneWorldMediator::resetLayerStar(int childId)
{
	/*if(_worldScene)
	{
		int areaStar = PerfectManager::instance()->(childId);
		_worldScene->setChildExitStarLev(childId, areaStar);
	}*/
}

void SceneWorldMediator::closeWorldScene()
{
	if(_worldScene != NULL)
	{
		_worldScene->dispose();
		dispose();
		ViewManager::getInstance()->worldScene = NULL;
	}
}

void SceneWorldMediator::dispose()
{
	if(_worldScene)
	{
		_worldScene->removeEventListener(SceneConst::MAP_BG_INIT);
		_worldScene->removeEventListener(SceneConst::ROLE_MOVE);
		_worldScene->removeEventListener(SceneConst::TRIGGER_EXIT);
		_worldScene->removeEventListener(SceneConst::SHOW_CHILD_SCENE);
		_worldScene->removeEventListener(SceneConst::CHILD_EXIT_CLICK);
	}
}

void SceneWorldMediator::onClearCD()
{
	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::CLEAR_FIGHT_CD, NULL);
}

void SceneWorldMediator::onCancelAdd()
{

}

void SceneWorldMediator::selectChildScene(CCNode* n, void* data)
{
	int id = *((int*)data);
	currElement._otherInfos[0] = id;
}

void SceneWorldMediator::returnFromWorldScene()
{
	if(_worldScene)
		_worldScene->onReturnButtonDown(NULL);
}


void SceneWorldMediator::roleMoveElement(IElement* element)
{
	if(_worldScene)
		_worldScene->roleMoveElement(element);
}