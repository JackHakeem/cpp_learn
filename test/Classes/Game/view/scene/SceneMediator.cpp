#include "view/scene/SceneMediator.h"
#include "model/scene/vo/SceneInfoVo.h"
#include "view/scene/components/MainScene.h"
#include "manager/LayerManager.h"
#include "SceneListenerMediator.h"
#include "manager/ViewManager.h"
#include "control/scene/SceneCommand.h"
#include "util/TileUtil.h"
#include "manager/RenderManage.h"
#include "events/GameDispatcher.h"
#include "manager/GlobalManage.h"
#include "../map/MapMediator.h"
#include "../mainUI/MainUIMediator.h"
#include "model/scene/vo/SceneType.h"
#include "../smallMap/SmallMapMediator.h"
#include "SceneWorldMediator.h"
#include "manager/CDManage.h"
#include "Message.h"
#include "model/player/RoleManage.h"
#include "model/newhand/NewhandManager.h"
#include "manager/PopManage.h"
#include "model/newhand/vo/TestNewhand.h"
#include "manager/LangManager.h"
#include "../newhand/components/LeaderAlert.h"
#include "view/fight/interfaces/BaseAction.h"
#include "model/battle/FightProxy.h"
#include "../BaseMediator.h"
//#include "manager/sound/SoundManager.h"
#include "manager/sound/SoundManager.h"

#include "model/scene/NPCManager.h"
#include "model/player/RoleManage.h"
#include "manager/SourceCacheManage.h"

#include "view/loading/LoadingView.h"
#include "manager/LayerManager.h"
#include "model/scene/MonsterManager.h"
#include "control/wordBoss/WorldBossCmd.h"
//#include "model/honor/vo/HonorGoodVo.h"
//#include "model/honor/vo/HonorScheduleManage.h"
#include "model/honor/vo/HonorGoodVo.h"
#include "model/honor/vo/HonorScheduleManage.h"
#include "model/honor/HonorProxy.h"
#include "model/scene/SceneManager.h"
#include "model/scene/ExitManager.h"
#include "socket/command/c12/CCMD12C.h"
#include "../mainUI/components/MainNavigate.h"

SceneMediator::SceneMediator()
{
	_scene = 0;
	_storyScene = 0;
	_dungeonView = 0;

	if(g_pFacade)
		_taskProxy = (TaskProxy *) g_pFacade->retrieveProxy(AppFacade_TASK_PROXY);

	_dispatcher = GameDispatcher::getInstance();

	//_fightProxy = (FightProxy *)g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
}

SceneMediator::~SceneMediator()
{
	//if(_scene)
	//{
	////	delete _scene;
	//	_scene->removeFromParentAndCleanup(true);//jae
	//	_scene->dispose();
	//	_scene->release();
	//	_scene = 0;
	//}

// 	if(_storyScene)
// 		delete _storyScene;
}

void SceneMediator::addToLayer()
{
	MainScene::Instance()->addChild(_scene, -100);
	_scene->release();//jae
	//MainScene::Instance()->addChild(_storyScene, -99);

}

void SceneMediator::handleNotification(int M2Vcmd, char* data)
{
	switch(M2Vcmd) 
	{
		case STARTUP_GAME_SCENE:
			startGameScene();
			break;
		case BUILD_SCENE:
			buildScene(data);
			break;
		case ADDROLE:
			addRole(data);
			break;
		case ADDPLAYER:
			addPlayer(data);
			break;
		case ADDPTRADELAYER:
			addTradePlayer(data);
			break;
		case REMOVEPLAYER:
			removePlayer(data);
			break;
		case REMOVETRADERPLAYER:
			removeTradePlayer(data);
			break;
		case MOVEPLAYER:
			movePlayer(data);
			break;
		case MOVETRADEPLAYER:
			moveTradePlayer(data);
			break;
		case MOVEPLAYERADJUST:
			movePlayerAdjust(data);
			break;
		case ADDNPC:
			addNPC(data);
			break;
		case REMOVENPC:
			removeNPC(data);
			break;
		case UPDATEEXIT:
			updateExit(data);
			break;
		case ADDEXIT:
			addExit(data);
			break;
		case REMOVEEXIT:
			removeExit(data);
			break;
		case ADDSTATUE:
			addStatue(data);
		case ROLE_POS_CHANGE:
			rolePosChange(data);
			break;
		case FOCUS_POS_CHANGE:
			focusPosChange(data);
			break;
		case ROLE_STOPANDNPC_MOVE:
			roleStopAndNPCMove(data);
			break;
		case ROLE_STOP:
			roleStop(data);
			break;
		case REMOVE_FIGHT_SCENE:
			removeFightScene(data);
			break;
		case REMOVE_ARMY_SCENE:
			removeArmyScene(data);
			break;
		case ADD_STORY_SCENE:
			addStoryScene(data);
			break;
		case REMOVE_STORY_SCENE:
			removeStoryScene(data);
			break;
		case MOVE_ROLE:
			roleMove(data);
			break;
		case ROLE_MOVE_PATH:
			roleMoveByPath(data);
			break;
		case MOVE_NPC:
			npcMove(data);
			break;
		case ROLE_TO_NPC:
			roleToNPC(data);
			break;
		case ROLE_TO_EXIT:
			roleToExit(data);
			break;
		case CANCEL_CLICK_TARGET:
			cancelClickTarget();
			break;
		case NPC_ICO_CHANGE:
			updateIco(data);
			break;
		//case MEDITATION_FIND_PATH:
		//	meditationFindPath();
		//	break;
		case INIT_RED_PROCESS_ID:
			_scene->initRedProgress(data);
			break;
	}
}

void SceneMediator::buildScene(char* data)
{
	if(!_scene || !_sceneProxy)
		return;

	CCLog("------------------Loading Resource begin.");	// Jae

	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(!info)
		return;
	std::vector<int> array = NPCManager::Instance()->getNpcsByMapId(info->playerBaseInfo._mapId);

	if(!_sceneProxy)
		return;

	DWORD d1(0), d2(0);
	if ( g_pGlobalManage->_isChangeScene )
	{
		CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_RGBA4444 );
		d1 = Timer::millisecondNow();
		CCLog("-------------------loading NPC Resource begin: %d");

		g_pGlobalManage->NumberOfSprites( array.size() + 16*2 );
		g_pGlobalManage->loadOneProgress( 16 );
		//g_pGlobalManage->m_nNumberOfLoadedSprites += array.size(); //Kenfly 20121112
		char _assetURL[128];

		//Begin Kenfly 20121106 : modify
		for(std::vector<int>::iterator iter = array.begin();
			iter != array.end(); ++iter)
		{
			NPCVo* npcVo = NPCManager::Instance()->getNPC(*iter);
			if(!npcVo)
				continue;

			//BitmapMovieClip* movieClip = NULL;
			//if(  npcVo->_isMonster ||
			//	(npcVo->action==SceneConst::FIGHT) || (npcVo->action==SceneConst::STORY) )
			//{
			//	movieClip = SourceCacheManage::Instance()->loadModel(
			//		_assetURL, npcVo->_resId, 0.2f, true, true);
			//	//if ( movieClip && !movieClip->animationStand[3] )
			//	//{
			//	//	SourceCacheManage::Instance()->reLoadModel(
			//	//		movieClip, _assetURL, npcVo->_resId, 0.2f );
			//	//}
			//}
			//else
			//{
			//	movieClip = SourceCacheManage::Instance()->loadPvrNormal(
			//		_assetURL, npcVo->_resId, BitmapMovieClip::ACTION_STAND, npcVo->state, 0.2f, true, true);
			//}
			//if (movieClip)
			//{
			//	movieClip->dispose(true);
			//}
			//CC_SAFE_DELETE( movieClip );

			++g_pGlobalManage->m_nNumberOfLoadedSprites;
		}

		/////////////////monster
		
		std::list<GMProgressVo*> arrayMonster =
			MonsterManager::Instance()->getGroupMonsterByMapId(info->playerBaseInfo._mapId);
		//g_pGlobalManage->loadOneProgress( arrayMonster.size());
		for(std::list<GMProgressVo*>::iterator iter = arrayMonster.begin();
			iter != arrayMonster.end(); ++iter)
		{
			if(!(*iter))
				continue;

			//if((*iter)->mgId == 0)
			//{
			//	continue;
			//}
			//NPCVo* npcVo = MonsterManager::Instance()->getMonsterGroup((*iter)->mgId);
			//if(!npcVo)
			//	continue;

			//sprintf( _assetURL, "assets/res/%d", npcVo->_resId);

			//BitmapMovieClip* movieClip = NULL;
			//movieClip = SourceCacheManage::Instance()->loadModel(
			//	_assetURL, npcVo->_resId, 0.2f, true, true);
			//if (movieClip)
			//{
			//	movieClip->dispose(true);
			//}
			//CC_SAFE_DELETE( movieClip );

			g_pGlobalManage->loadOneProgress( 1 );
		}

		////////////////monster end
		//End Kenfly 20121106

		d2 = Timer::millisecondNow();
		CCLog("-----------------loading NPC Resource end. %d ,%f s", d2, d2*0.001 );
		CCLog("-----------------loading NPC Resource use: %d ,%f s", (d2-d1), (d2-d1)*0.001 );

		sprintf( _assetURL, "assets/res/%d", info->playerBaseInfo.cloth);
		//Begin Kenfly 20121110 : modify, load async

		//BitmapMovieClip* m = new BitmapMovieClip();
		//m->loadModelAsync(_assetURL, info->playerBaseInfo.cloth, 0.1f);
		////BitmapMovieClip* m = SourceCacheManage::Instance()->loadModel(
		////	_assetURL, info->playerBaseInfo.cloth, 0.1f, true);
		//if (m)
		//{
		//	m->dispose(true);
		//}
		//CC_SAFE_DELETE( m );

		//End Kenfly 20121110
		
		CCLog("------------------Loading Resource end.");	// Jae
		CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_Default );


		if (ViewManager::getInstance()->_secNavigate)
			ViewManager::getInstance()->_secNavigate->removeBtnAward();

		if(_sceneProxy->sceneInfoVo()->type == SceneType::STORY) 
		{
			HonorGoodVo* vo = HonorScheduleManage::Instance()->getAwardByMap(_sceneProxy->sceneInfoVo()->id);
			if (ViewManager::getInstance()->_secNavigate && vo)
			{
				HonorProxy* _honorProxy = (HonorProxy*)g_pFacade->retrieveProxy(AppFacade_HONOR_PROXY_CHANGE);
				map<int, HonorObject*>::iterator it = _honorProxy->_honorList.find(vo->honorsid);
				if ( it != _honorProxy->_honorList.end() )
				{
					HonorObject* obj = it->second;
					if (obj->award == 0)
					{
						ViewManager::getInstance()->_secNavigate->addButtonAward();
					}
				}
			}
		}				
	}
	sendNotification(Facade_Mediator, AppFacade_SCENELISTENER_MEDIATOR, (char*)data, SceneListenerMediator::START_SCENE_LISTENER);
	//char* mapName = data;
	SceneInfoVo* sceneInfoVo = _sceneProxy->sceneInfoVo();
	if(!sceneInfoVo)
		return;

	//// world boss hide menu
	//if ( sceneInfoVo->type == SceneType::WORLD_BOSS )
	//{
	//	// notify newhand
	//	MainNavigate* navigage = (MainNavigate*)LayerManager::sceneUILayer->getChildByTag(
	//		SceneUILayer::SceneUILayerTAG_MainUIMediator);
	//	CCMenu* pMainButtonMenu = (CCMenu*)navigage->getChildByTag(MainNavigate::MainNavigateTAG_menubtn);
	//	pMainButtonMenu->setIsVisible(false);
	//	pMainButtonMenu->setIsTouchEnabled(false);
	//}

	//Begin Kenfly 20130115 : memory leak, move before build scene, delete in sourcecachemanage.
	if(g_pPopManage)
		g_pPopManage->handleCloseHandler();

	_scene->dispatchEvent(SceneConst::BUILD, NULL); 
	_scene->dispatchEvent(SceneConst::MAP_BG_INIT, NULL);
	//End Kenfly 20130115

	d1 = Timer::millisecondNow();;
	CCLog("-------------------before build scene: %d",  d1);
	std::string path = sceneInfoVo->sceneRoot+"front/";
	_scene->buildScene(sceneInfoVo->width,
		sceneInfoVo->height,
		sceneInfoVo->type,
		sceneInfoVo->offsetX,
		sceneInfoVo->offsetY,
		path,
		_sceneProxy->_focusPos
	);
	//g_pGlobalManage->loadOneProgress( 16 );
	d2 = Timer::millisecondNow();
	CCLog("-------------------after build scene: %d", d2 );
	CCLog("-------------------build scene use: %f s", (d2-d1)*0.001 );

	//SoundManager.getInstance().roleMapChangeHandler(); 

	//		
	//PopManage.getInstance().popBackAllView();
	//		
	//if(ViewManager.getInstance().smallMapUI){
	//	ViewManager.getInstance().smallMapUI.setMapName(mapName);
	//}

	LoadingView* pLoadingView = (LoadingView*)LayerManager::tipsLayer->getChildByTag( TipsLayer::WindowLayerTAG_Loading );
	if ( pLoadingView )
	{
		pLoadingView->removeFromParentAndCleanup( true );
	}

	CCLog("-------------------1: %d",  Timer::millisecondNow());
	sendNotification(Facade_Mediator, AppFacade_MapMediator, (char*)(&data), MapMediator::CLOSE_MAP);
	CCLog("-------------------2: %d",  Timer::millisecondNow());
	//sendNotification(Facade_Mediator, AppFacade_MainUIMediator, (char*)(&data), MainUIMediator::STARTUP_CD_LIST);
	sendNotification(Facade_Mediator, AppFacade_MainUIMediator, (char*)(&data), MainUIMediator::STARTUP_SEC_NAV);
	sendNotification(Facade_Mediator, AppFacade_MainUIMediator, (char*)(&data), MainUIMediator::STARTUP_TOKEN_BAR);
	CCLog("-------------------3: %d",  Timer::millisecondNow());
	if(sceneInfoVo->type == SceneType::COPY)
	{
		sendNotification(Facade_Mediator, AppFacade_MainUIMediator, (char*)(&data), MainUIMediator::ADD_QUIT_COPY_BTN);
		int i = true;
		sendNotification(Facade_Mediator, AppFacade_SmallMapMediator, (char*)(&i), SmallMapMediator::LOCK_STATE);

		/*if(_teamProxy.sCMD328)
		{
			sendNotification(TeamMediator.TEAM_CALLBACK);
		}*/
		
	}
	//Begin Kenfly 20121130
	if (sceneInfoVo->type == SceneType::STORY)
	{
		int id = sceneInfoVo->id;
		sendNotification(Facade_Mediator, AppFacade_MainUIMediator, (char*)(&id), MainUIMediator::STARTUP_REPORT_UI);
	}
	else
	{
		sendNotification(Facade_Mediator, AppFacade_MainUIMediator, NULL, MainUIMediator::CLOSE_REPORT_UI);
	}

	if (ViewManager::getInstance()->_secNavigate)
	{
		ViewManager::getInstance()->_secNavigate->setIsShowCenterTopItems(sceneInfoVo->type == SceneType::CITY);
	}
	//End Kenfly 20121130

	//else{
	//	sendNotification(SmallMapMediator.LOCK_STATE, false );
	//	sendNotification(MainUIMediator.CLOSE_TEAM_UI, true);	
	//}
	//if(GameManager.getInstance().parameters.guest ==1)
	//{
	//	sendNotification(RegisterMediator.REGISTER_POP);
	//}
	//		

	//Doyang 20120712
	TestNewhand *pTestNewhand = new TestNewhand("map", NULL, 0);
	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::TEST_NEW_HAND, pTestNewhand);
	CC_SAFE_DELETE(pTestNewhand);
	//LayerManager.chatLayer.visible = true;
	//LayerManager.sceneUILayer.visible = true;
	if(sceneInfoVo->id == 1001 && NewhandManager::Instance()->_isNewAcount)
	{
		//NewhandManager::Instance()->_isNewAcount = false;
		if(ViewManager::getInstance()->_roleUI)
		{
			ViewManager::getInstance()->_roleUI->setGold(RoleManage::Instance()->accountInfo()->gold());
		}
		//string info = LangManager::getText("SCE034");

		LeaderAlert::show("", 3, true, NULL, NULL, NULL); // deleted byLH 20121129

		// pop login award panel // byLH 20121129
		/*
		if (ViewManager::getInstance()->_secNavigate)
		{
			ViewManager::getInstance()->_secNavigate->popUIHandlerLoginReward(0);
		}
		*/
	}
	
	
	
	// 通知世界Boss系统当前地图ID
	sendNotification(Facade_Command , AppFacade_WorldBoss_Command , (char *)&sceneInfoVo->id , WorldBossCmd::MAP_SKIP);
	
	CCLog("-------------------4: %d",  Timer::millisecondNow());
}

void SceneMediator::raiseCityName(char* data)
{
	if(!g_pFacade)
		return;

	SceneProxy* _sceneProxy = (SceneProxy*)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
	if(!_sceneProxy || !_sceneProxy->_sceneInfoVo)
		return;
	int id = _sceneProxy->_sceneInfoVo->id;
	sendNotification(Facade_Mediator, AppFacade_MainUIMediator, (char*)(&id), MainUIMediator::STARTUP_SCENE_NAME);
}

//change the scene
void SceneMediator::startGameScene()
{	 
	RenderManage::Instance()->stop();
	if(_scene == NULL)
	{
		_scene = new Scene();
		//_scene = new StoryScene();
		LayerManager::sceneLayer = _scene;
		//LayerManager::storyLayer = _storyScene;
		addToLayer();
		if(g_pGlobalManage)
			g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID());
		//sendNotification(Facade_Mediator, AppFacade_SCENELISTENER_MEDIATOR, NULL, SceneListenerMediator::SCENE_STARTBGCOMPLETE);
		ViewManager::getInstance()->_scene = _scene;
		if(_scene)
			_scene->addEventListener(SceneConst::RAISE_CITY_NAME, this, callfuncND_selector(SceneMediator::raiseCityName));

 	}
	else{
 		//DisplayObjectManager.clearAchieve();
		sendNotification(Facade_Mediator, AppFacade_SCENELISTENER_MEDIATOR, NULL, SceneListenerMediator::REMOVE_SCENE_LISTENER);
	}

	//this.facade.sendNotification(AppFacade.GAME_SCENE); change to the next
	if(g_pFacade && g_pGlobalManage->_isChangeScene)//jae no
	{
		SceneCommand* cmd = (SceneCommand*)g_pFacade->retrieveController(AppFacade_SCENE_COMMAND);
		if(cmd)
		{
			cmd->excute(0, NULL);
		}
	}
	//sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, _sceneInfoVo.name.c_str(), SceneMediator::BUILD_SCENE);
	CCLog("-------------------before SCENE_CHANGE: %d",  Timer::millisecondNow());
	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::SCENE_CHANGE, NULL);
	CCLog("-------------------after SCENE_CHANGE: %d",  Timer::millisecondNow());

	// background music switch
	if (SoundManager::Instance()->getIsSoundOpen())
	{
		SoundManager::Instance()->roleMapChangeHandler(true);
	}

	int mapId = RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId;
	SceneVo* pSceneVo = SceneManager::Instance()->getSceneDic(mapId); // map name
	// reset copy map name
	if (RoleManage::Instance()->roleInfo())
	{
		if (ViewManager::getInstance()->mainNavigate && pSceneVo)
		{
			ViewManager::getInstance()->mainNavigate->setMapName(pSceneVo->name);
		}
	}

	// show taskuiview and vscrollview

	

}

void SceneMediator::closeWorldScene()
{
	sendNotification(Facade_Mediator, AppFacade_SCENEWORLD_MEDIATOR, NULL, SceneWorldMediator::CLOSE_WORLD_SCENE);
	//this.facade.sendNotification(SceneWorldMediator.REMOVE);
}

void SceneMediator::addRole(char* data)
{
	if(_scene)
		_scene->addRole();
}

void SceneMediator::movePlayer(char* data)
{
	if(!data || !_scene)
		return;

	struct Data
	{
		int id;
		std::vector<CCPoint>* path;
	};
	Data* d = (Data*)data;

	if(_scene)
		_scene->playerMove(d->id, *(d->path));
}

void SceneMediator::addPlayer(char* data)
{
	if(!data || !_scene)
		return;

	PlayerBaseVo* vo = (PlayerBaseVo*)data;
	_scene->addPlayerHandler(vo);
}

void SceneMediator::removePlayer(char* data)
{
	if(!data || !_scene)
		return;

	int accid = *((int*)data);
	_scene->removePlayer(accid);
}

void SceneMediator::removeTradePlayer(char* data)
{
	if(!data || !_scene)
		return;

	int accid = *((int*)data);
	_scene->removeTradePlayer(accid);
}

void SceneMediator::removeNPC(char* data)
{
	if(!data || !_scene)
		return;

	int id = *((int*)data);
	_scene->removeNPC(id);
}

void SceneMediator::showNPC(char* data, bool val)
{
	if(!data || !_scene)
		return;

	int id = *((int*)data);
	_scene->showNPC(id, val);
}

void SceneMediator::NPCName(int id, const char* name)
{
	if(!_scene)
		return;

	_scene->NPCName(id, name);
}

void SceneMediator::NPCColor(char* data, cocos2d::ccColor3B color)
{
	if(!data || !_scene)
		return;

	int id = *((int*)data);
	_scene->NPCColor(id, color);
}


void SceneMediator::updateExit(char* data)
{
	if(!data || !_scene)
		return;

	struct Data
	{
		int id;
		ExitVo* exitVo;
	};
	Data* d = (Data*)data;
	int id = d->id;
	ExitVo* vo = d->exitVo;

	_scene->setExitVo(id, vo);
}

void SceneMediator::addExit(char* data)
{
	if(!data || !_scene)
		return;

	ExitVo* vo = (ExitVo*)data;
	_scene->addExit(vo);
}

void SceneMediator::removeExit(char* data)
{
	if(!data || !_scene)
		return;

	int id = *((int*)data);
	_scene->removeExit(id);
}

void SceneMediator::rolePosChange(char* data)
{
	if(_scene)
		_scene->rolePosChangeHandler(_sceneProxy->rolePos());
}

void SceneMediator::focusPosChange(char* data)
{
	if(_scene)
		_scene->focusPosChangeHandler(_sceneProxy->focusPos());
}

void SceneMediator::roleStopAndNPCMove(char* data)
{
	if(!data || !_scene)
		return;

	struct Data
	{
		int id;
		int type;
		Data()
		{
			id = 0;
			type = 0;
		}
	};

	Data* d = (Data*)data;
	_scene->roleStopAndNPCMove(d->id, d->type);

}

void SceneMediator::roleStop(char* data)
{
	if(!data || !_scene)
		return;

	cancelClickTarget();
	_scene->roleStop();
}

void SceneMediator::removeFightScene(char* data)
{
	if(!_scene)
		return;

	_scene->rmFightScene();
	//DisplayObjectManager.clearChildren(LayerManager.battleLayer);
	//_scene->setLayersVisible(true, RoleManage::Instance()->roleOpe());

	RenderManage::Instance()->start();
	
	if(_sceneProxy && _sceneProxy->_sceneInfoVo
		&& _sceneProxy->_sceneInfoVo->type != SceneType::COPY 
		&& _sceneProxy->_sceneInfoVo->type != SceneType::WORLD_BOSS)
	{
		bool i = false;
		sendNotification(Facade_Mediator, AppFacade_SmallMapMediator, (char*)(&i), SmallMapMediator::LOCK_STATE);
	}

	if(_fightProxy->_bData._tailStoryAction && g_pGlobalManage->getIsStorySystemOpen())
	{
		_dispatcher->addEventListener( GameDispatcher::STORY_CALLBACK, this, callfuncND_selector(SceneMediator::onTailStoryCallback) );
		_fightProxy->_bData._tailStoryAction->doAction();
		_fightProxy->_bData._tailStoryAction->release();
		_fightProxy->_bData._tailStoryAction = 0;

		//fightOutCallback();
	}
	else
	{
		fightOutCallback();
	}

	//// 清空战斗内容 
	//clearBattle();
}

void SceneMediator::onTailStoryCallback(CCNode*, void*)
{	
	fightOutCallback();
	_dispatcher->removeEventListener(GameDispatcher::STORY_CALLBACK);
}

void SceneMediator::fightOutCallback()
{	
	std::vector<BaseAction*> &cbs = _fightProxy->_bData._callbacks;
	for (std::vector<BaseAction*>::iterator it = cbs.begin(); it != cbs.end(); it++)
	{
		// Doyang 20120710
		BaseAction *pAction = (BaseAction *) *it;
		if(pAction)
		{
			// fight-> story ,then play after story
			/*
			if (g_pGlobalManage->isInStory)
			{
				StoryProxy * pStoryProxy = (StoryProxy *)g_pFacade->retrieveProxy(AppFacade_SCENESTORY_PROXY_CHANGE);
				if (pStoryProxy)
				{
					pStoryProxy->storyCallbackActionList.push_back(pAction);
				}
			}
			else
			*/
			{
				pAction->doAction();
				CC_SAFE_DELETE(pAction);
			}

		}
		//(*it)->doAction();
	}
	cbs.clear();

	_fightProxy->battleId = 0;
	/*if (cbs.size())
	{
	std::vector<BaseAction*>::iterator it = cbs.begin();
	while (it != cbs.end())
	{
	it = cbs.erase(it);
	}	
	}*/


	GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::BATTLE_CALLBACK, 0 );

	// 清空战斗内容  temp!
	clearBattle();


	//新手引导的内容，如果遇到战斗，改到战斗之后回调
	NewhandManager::Instance()->touchCallBack(0);
	//if ( _fightProxy->dungeonAward )
	//{
	//	_fightProxy->dungeonAward->doAction();
	//}
	//_fightProxy->dungeonAward = 0;
	/*PopUpManager.setAllWindowVisible(true);

	if(_fightProxy.fightNewMerc !=null){
		if(_crystalProxy.getCrystalLev(CrystalType.CRYSTAL_MAIN) > 15 )
		{
			var mercId:int = _fightProxy.fightNewMerc.a_mercId.value;
			var figureCfgVo:FigureCfgBaseVo = FigureBaseManage.getInstance().getMercBase(mercId);

			
		}
		_fightProxy.fightNewMerc = null;
	}

	if(_fightProxy.honorId >0 )
	{

		if(_scene)
			_scene.playerHonor(_fightProxy.honorId, _honorProxy.LastTotalPoint, _honorProxy.TotalPiont);
		_fightProxy.honorId = 0 ;
	}

	_fightProxy.battleId = 0;

	if(_fightProxy.scmdArr.length>0 ){
		for each(var obj:Object in _fightProxy.scmdArr){
			if(obj.param){
				obj.fun(obj.param);
			}
			else{
				obj.fun();
			}
		}
		_fightProxy.scmdArr = [];
	}

	if( GlobalManage.getInstance().isReport == false)
	{
		FightEndLead.precisionTips(_fightProxy);
		if(_fightProxy.fightRet && _fightProxy.fightRet.b_type.value == BattleType.BATTLE_TYPE_PVE)
		{ 
			cdEnergyHandler();   
		}
	}

	_fightProxy.clear();
	GlobalManage.getInstance().isInFight = false; 

	if(_roleManage.accountInfo.team == 1)
	{
		_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_TEAM_BATTLE_END);
	}

	if(GlobalManage.getInstance().isOnBusiness)
	{
		GlobalManage.getInstance().isOnBusiness = true;
	}

	NewhandManager.getInstance().touchCallBack(0);*/
}

int SceneMediator::changeSceneTipsPopCallBack()
{
	int count = 0;
	SceneProxy * pSceneProxy = (SceneProxy *)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
	if (pSceneProxy)
	{
		std::vector<BaseAction*> &cbs = pSceneProxy->_callbacks;
		count = cbs.size();
		for (std::vector<BaseAction*>::iterator it = cbs.begin(); it != cbs.end(); it++)
		{
			BaseAction *pAction = (BaseAction *) *it;
			if(pAction)
			{
				{
					pAction->doAction();
					CC_SAFE_DELETE(pAction);
				}
			}
		}
		cbs.clear();
	}
	return count;
}

void SceneMediator::removeArmyScene(char* data)
{
	/*LayerManager.sceneUILayer.visible = true;
	showUILayer(removeArmySceneHandler);*/
}

void SceneMediator::removeArmySceneHandler()
{
	/*GlobalManage.getInstance().gameView.addChild(LayerManager.newhandLayer);
	_scene.setLayersVisible(true, _roleManage.roleOpe());
	DisplayObjectManager.clearChildren(LayerManager.effectLayer);
	DisplayObjectManager.clearChildren(LayerManager.battleLayer);
	RenderManage.getInstance().start(); 
	sendNotification(SmallMapMediator.LOCK_STATE, false);
	sendNotification(ArmyMediator.CALLBACK_AFTER_FIGHT);

	GlobalManage.getInstance().isInFight = false; 
	GlobalManage.getInstance().isInArmyFight = false;

	PopUpManager.setAllWindowVisible(true);*/

}

void SceneMediator::showUILayer()
{
	/*var tweens:Array = [];
	var tweenLite:TweenLite
	for(var i:int=0; i<LayerManager.sceneUILayer.numChildren; i++)
	{
	var display:DisplayObject = LayerManager.sceneUILayer.getChildAt(i);
	trace(display.name);
	tweenLite = Utils.show(display);
	if(tweenLite)tweens.push(tweenLite);
	}
	if(tweens.length>0 )
	{
	var tweenGroup:TweenGroup = new TweenGroup(tweens);
	tweenGroup.align = TweenGroup.ALIGN_START;
	tweenGroup.onComplete = func;
	if(param)tweenGroup.onCompleteParams = [param]; 

	}
	else
	{
	if(param)
	func(param);
	else
	func();
	}*/
}

void SceneMediator::addStoryScene(char* data)
{
	/*PopManage.getInstance().popBackAllView();
	PopManage.getInstance().removeKeyListener();
	LayerManager.sceneUILayer.visible = false;
	LayerManager.chatLayer.visible = false;

	_scene.addStoryScene(obj as StoryScene);
	_scene.setLayersVisible(false);*/
}

void SceneMediator::removeStoryScene(char* data)
{
	/*GlobalManage.getInstance().gameView.addChild(LayerManager.newhandLayer);

	_scene.rmStoryScene();

	sendNotification(SmallMapMediator.LOCK_STATE, false);
	sendNotification(DialogMediator.SET_AUTO_POP, true);
	_storyProxy.dispose();

	GlobalManage.getInstance().isInStory = false;

	if(GlobalManage.getInstance().isInFight == true)
	{
	fightOutCallback();		
	}
	else{
	PopUpManager.setAllWindowVisible(true);
	}*/
}

void SceneMediator::updateIco(char* data)
{
	if(!data || !_scene || !_taskProxy)
		return;
	std::list<int> npcList = *(std::list<int> *)data;

	std::list<int>::iterator it;
	for(it = npcList.begin(); it != npcList.end(); ++it)
	{
		int npcId = *it;
		int state = _taskProxy->getIcoByNPC(npcId);
		MapNPC *pNpc = (MapNPC *) _scene->getNPC(npcId);
		if(pNpc)
		{
			pNpc->icon(state);
		}
	}
	//struct NpcList
	//{
	//	int *pNpcs;
	//	int length;
	//};
	//NpcList *pNpcList = (NpcList *) data;
	//for(int i=0; i<pNpcList->length; ++i)
	//{
	//	int npcId = pNpcList->pNpcs[i];
	//	int state = _taskProxy->getIcoByNPC(npcId);
	//	MapNPC *pNpc = (MapNPC *) _scene->getNPC(npcId);
	//	if(pNpc)
	//	{
	//		pNpc->icon(state);
	//	}
	//	//_sceneProxy->
	//}

    //CC_SAFE_DELETE(data);
	//std::vector<int>* array = (std::vector<int>*)data;
	//std::vector<int>::iterator iter = array->begin();
	//for(; iter != array->end(); ++iter)
	//{
	//	int state = _taskProxy->getIcoByNPC(*iter);
	//	_scene->npcUpdateIcon(*iter, state);
	//	//sendNotification(SmallMapMediator.NPC_ICON_CHANGE,{id:npcid,Icon:state})
	//}
}

void SceneMediator::roleMove(char* data)
{
	if(g_pPopManage)
	{
//		g_pPopManage->setIsNeedClose(0 , false);
		g_pPopManage->handleCloseHandler();
	}

	if(!data || !_scene || !_sceneProxy)
		return;

	struct Data
	{
		CCPoint endPoint;
		float ranger;
		Data()
		{
			ranger = 0;
		}
	};
	Data* d = (Data*)(data);

	CCPoint endScenePoint = d->endPoint;
	float ranger = d->ranger;

	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(!info)
		return;

	PlayerBaseVo palyBaseInfo = info->playerBaseInfo;

	CCPoint startPoint = ccp( palyBaseInfo.x, palyBaseInfo.y);
	CCPoint endPoint = TileUtil::Instance()->changePixsToTile(endScenePoint);

	if( _sceneProxy->checkTilePoint(endPoint) == 1)
	{
		endPoint = _sceneProxy->findMinEndPoint(endPoint);
	}

	if(_sceneProxy->checkTilePoint(endPoint) == -1)
	{
		if(g_pGlobalManage && g_pGlobalManage->isOnMeditation())
		{
			meditationFindPath();
		}
		return;
	}

	std::vector<CCPoint> searchResults = _sceneProxy->findPath(startPoint, endPoint);
	if(searchResults.size() > 1)
	{
		std::vector<CCPoint> scenePath = changeToMapPath(searchResults);

		scenePath.pop_back();
		scenePath.push_back(TileUtil::Instance()->changeTileToPixs(endPoint));

		CCPoint end_p = scenePath[scenePath.size() - 1];
		CCPoint pre_p = scenePath[scenePath.size() - 2];

		float dis = sqrt((end_p.y - pre_p.y) * (end_p.y - pre_p.y) +  (end_p.x - pre_p.x) * (end_p.x - pre_p.x));
		if(dis > ranger)
		{
			float angle = atan2(end_p.y - pre_p.y , end_p.x - pre_p.x);
			CCPoint point = ccp(end_p.x - ranger * cos(angle),end_p.y - ranger * sin(angle));

			//delete start point
			std::vector<CCPoint>::iterator iter = scenePath.begin();
			scenePath.erase(iter);
			//
			scenePath.pop_back();
			scenePath.push_back(point);
		}
		else 
		{
			//delete start point
			std::vector<CCPoint>::iterator iter = scenePath.begin();
			scenePath.erase(iter);
			//delete the search end point
			scenePath.pop_back();
		}
		if(scenePath.size() > 0)
		{
			_scene->movePath(scenePath);
		}
	}
	else
	{
		if(g_pGlobalManage && g_pGlobalManage->isOnMeditation())
		{
			meditationFindPath();
		}
	}
}

void SceneMediator::roleMoveByPath(char* data)
{
	if(!data || !_scene)
		return;

	struct Data
	{
		float ranger;
		std::vector<CCPoint>* path;
		Data()
		{
			ranger = 0.0f;
		}
	};

	Data* d = (Data*)data;
	
	float ranger = d->ranger;
	std::vector<CCPoint>* scenePath = d->path;

	if(scenePath && scenePath->size() >= 2)
	{
		CCPoint end_p = (*scenePath)[scenePath->size() - 1];
		CCPoint pre_p = (*scenePath)[scenePath->size() - 2];
		float angle = atan2(end_p.y - pre_p.y , end_p.x - pre_p.x);
		CCPoint point = ccp(end_p.x - ranger * cos(angle),end_p.y - ranger * sin(angle));

		scenePath->pop_back();
		scenePath->push_back(point);
	}
	_scene->movePath(*scenePath);
}



void SceneMediator::npcMove(char* data)
{
	if(!data || !_scene || !_sceneProxy)
		return;

	struct Data
	{
		int id;
		float ranger;
		CCPoint startPoint;
		CCPoint endPoint;
	};
	Data* d = (Data*)data;

	CCPoint startPoint = d->startPoint;
	//float ranger = d->ranger;
	int npcId = d->id;
	CCPoint endPoint = d->endPoint;

	if( _sceneProxy->checkTilePoint(endPoint) == 1)
	{
		endPoint = _sceneProxy->findMinEndPoint(endPoint);
	}
	if(_sceneProxy->checkTilePoint(endPoint) == -1 )
		return;

	std::vector<CCPoint> path;
	path.push_back(TileUtil::Instance()->changeTileToPixs(endPoint));
	_scene->npcMovePath(npcId, path);
}

void SceneMediator::roleToExit(char* data)
{
	if(!data || !_scene )
		return;

	int id = *((int*)data);
	
	_scene->roleToExit(id);
}

void SceneMediator::movePlayerAdjust(char* data)
{
	if(!data || !_scene)
		return;

	struct Data
	{
		int id;
		float ranger;
		std::vector<CCPoint>* path;
	};
	Data* d = (Data*)data;
	if(!(d->path))
		return;

	float ranger = d->ranger;
	std::vector<CCPoint> scenePath = *(d->path);

	if(d->path->size() >= 2)
	{
		CCPoint end_p = (*(d->path))[scenePath.size() - 1];
		CCPoint pre_p = (*(d->path))[scenePath.size() - 2];
		float angle = atan2(end_p.y - pre_p.y , end_p.x - pre_p.x);
		CCPoint point = ccp(end_p.x - ranger * cos(angle), end_p.y - ranger * sin(angle));


		d->path->pop_back();
		d->path->push_back(point);
		_scene->playerMove(d->id, *(d->path));
	}
}

void SceneMediator::addNPC(char* data)
{
	if(!data || !_scene)
		return;

	struct Data
	{
		ccColor3B color;
		NPCVo* npcVo; 
	};
	Data* param = (Data*)data;
	MapNPC* npc = _scene->addNPC(param->npcVo);
	
	if(!npc)
		return;

	if(npc->_npcVo)
	{
		int state = _taskProxy->getIcoByNPC(npc->_npcVo->id);
		npc->icon( state );
	}

	if(npc->action() == SceneConst::FIGHT)
	{
		npc->color(param->color);
		//this.sendNotification(SmallMapMediator.ADD_MONSTER_HANDLER,{id:npc.id,color:obj.color});
	} 
	else if(npc->action() == SceneConst::WANDER)
	{
		npc->color(param->color);
	}

	if (npc->_id >= 9001 && npc->_id <= 9030)
		npc->setIsVisible(false);

	if(isHiddenNpc(npc->_id))
	{
		npc->setIsVisible(false);
	}
}

bool SceneMediator::isHiddenNpc(int npcId)
{
	bool isHidden = false;
	switch(npcId)
	{
	case 90:
		isHidden = true;
		break;
	case 91:
		isHidden = true;
		break;
	case 92:
		isHidden = true;
		break;
	case 93:
		isHidden = true;
		break;
	}

	return isHidden;
}

void SceneMediator::roleToNPC(char* data)
{
	if(!data || !_scene )
		return;

	int id = *((int*)data);
	_scene->roleToNPC(id);
}

void SceneMediator::cancelClickTarget()
{
	if(_scene)
		_scene->cancelClickTarget();
}

void SceneMediator::meditationFindPath()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	float randomX = rand() % 10 * screenSize.width / 10.0f;
	float randomY = rand() % 10 * screenSize.height / 10.0f;
	CCPoint pos = TileUtil::Instance()->changePixsToTile(ccp(randomX, randomY));
	CCPoint randomPoint = _scene->getElemenetPosition(pos.x, pos.y);
	randomPoint =  TileUtil::Instance()->changePixsToTile(randomPoint);

	if(_sceneProxy && _scene)
	{
		while(_sceneProxy->checkTilePoint(randomPoint)==1)
		{
			randomX = rand() % 10 * screenSize.width / 10.0f;
			randomY = rand() % 10 * screenSize.height / 10.0f;
			pos = TileUtil::Instance()->changePixsToTile(ccp(randomX, randomY));
			randomPoint = _scene->getElemenetPosition(pos.x, pos.y);
			randomPoint =  TileUtil::Instance()->changePixsToTile(randomPoint);
		}
	}
	cancelClickTarget();

	struct Data
	{
		CCPoint endPoint;
		float ranger;
		Data()
		{
			ranger = 0.0f;
		}
	} data;
	data.endPoint = randomPoint;
	data.ranger = 0.0f;
	roleMove((char*)(&data));
}

std::vector<CCPoint> SceneMediator::changeToMapPath(std::vector<CCPoint>& path)
{
	std::vector<CCPoint> newPath;
	std::vector<CCPoint>::iterator iter = path.begin();
	CCPoint p;
	for(; iter != path.end(); ++iter)
	{
		p = TileUtil::Instance()->changeTileToPixs(*iter);
		newPath.push_back(p);
	}
	return newPath;
}

void SceneMediator::cdEnergyHandler()
{
	int cdType = CDManage::Instance()->getLockBytype(CDManage::FIGHT);
	if(cdType == 1)
	{
		Message::Instance()->show("SCE038");
		//Alert.show(LangManager.getText("SCE038"),"", 0);
	}
	else
	{
		AccountInfoVo* info = RoleManage::Instance()->accountInfo();
		if(info)
		{
			int energy = info->_energy;
			//int token = TokenManager.getInstance().getNum(TokenManager.TOKEN_FIGHT);
			if(energy <= 0)
			//if(energy + token <= 0)
			{
				Message::Instance()->show("SCE039");
				//Alert.show(LangManager.getText("SCE039"),"", 0);
			}
		}
	}
}

void SceneMediator::addStatue(char* data)
{
	/*if(!_scene)
		return;
	_scene.addStatue(obj.id, obj.item);*/
}

void SceneMediator::clearBattle()
{
	_fightProxy->battleId = 0;
	_fightProxy->clear();   // 最后 清空fightProxy  
	g_pGlobalManage->_isInFight = false; 
}

void SceneMediator::addTradePlayer( char* data )
{
	if (!data)
	{
		return;
	}

	PlayerBaseVo* vo = (PlayerBaseVo*)data;
	if(!_scene)
	{		
		_sceneProxy->_traderplayerDic.insert(make_pair(vo->accountId, *vo));
		return;
	}

	_scene->addTradePlayerHandler(vo);
}

void SceneMediator::moveTradePlayer( char* data )
{
	if(!data || !_scene)
		return;

	struct Data
	{
		int id;
		std::vector<CCPoint>* path;
	};
	Data* d = (Data*)data;

	if(_scene)
		_scene->tradeplayerMove(d->id, *(d->path));
}
