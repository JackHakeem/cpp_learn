#include "SceneFightMediator.h"
#include "control/AppFacade.h"
#include "control/battle/SceneFightProxyCommand.h"
#include "model/battle/FightProxy.h"
#include "view/scene/layer/FightLayer.h"
#include "socket/command/c13/CCMD138.h"
#include "manager/BattleManager.h"
#include "manager/ViewManager.h"
#include "manager/LayerManager.h"
#include "model/scene/vo/EventType.h"
#include "manager/PopManage.h"
#include "manager/GlobalManage.h"
#include "../scene/components/Scene.h"
#include "socket/command/s11/SCMD11F.h"
#include "model/scene/vo/BattleType.h"
#include "manager/TouchLayerEnum.h"

#include "model/skill/SkillManager.h"
#include "utils/EffectHelps.h"
#include "utils/Timer.h"
#include "manager/CDManage.h"
#include "manager/sound/SoundManager.h"
#include "../worldBoss/components/DeathView.h"
#include "../worldBoss/WorldBossMediator.h"
#include "events/GameDispatcher.h"
#include "model/player/RoleManage.h"
#include "../newhand/components/NewHandHelpView.h"


SceneFightMediator::SceneFightMediator()
{
	_fightProxy = (FightProxy*)g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
	enginer = NULL;
	fightLayer = NULL;
	rate = 0;
	_fightScene = NULL;
}
void SceneFightMediator::handleNotification(int M2Vcmd, char* data)
{   
	
	switch(M2Vcmd)
	{
	case INTO_FIGHT:
		loadWarRes();
		break;
	case FIGHT_START:
		playEffect();
		break;
	case ABORT_FIGHT:
		abortFight();
		break;
	default:
		break;
	}
}

/**
	*  Loading combat resources
	*/		
void SceneFightMediator::loadWarRes()
{
	//ModuleLoaderManage.getInstance().load(ResourceName.WAR_PATH, LoadLevel.HIGH, warPathLoaded);

	g_pGlobalManage->_isInFight = true;

  	configFightScene();
}


 
/**
	* Create battle scene. This is only an loading UI, began to protected reliably against detective
	*/		
void SceneFightMediator::configFightScene()
{
	//FightLayer::getInstance()->initUI();
	if(_fightScene)
	{
		_fightScene->dispose();
		_fightScene->release();
		_fightScene = 0;
		//delete _fightScene;
	}


	//if(g_pPopManage)kevinchange
	//	g_pPopManage->handleCloseHandler();

	_fightScene = new FightScene();

	ViewManager::getInstance()->_fightScene = _fightScene;
	if(LayerManager::battleLayer)
		LayerManager::battleLayer->addChild(_fightScene);


	_fightScene->release();//jae note 

	_fightProxy->fightLayerCreate = true;
	cocos2d::CCLog("fightLayerCreate = true");

	// LH0728 hide all popcontainers and UI
	if (g_pPopManage)
	{
		g_pPopManage->handleCloseHandler();
	}
	g_pGlobalManage->showAllUI(false); // should be called after "g_pPopManage->handleCloseHandler();"

//	SoundManager::Instance()->playBattleBgSound(); // LH20120812 战斗背景音乐开始

	// world boss by longhui 20120920
	int curMapID = RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId;
	if (curMapID ==  1208)
	{
		if (ViewManager::getInstance()->_pWBMainView )
		{
			DeathView * pDeathView = (DeathView * )ViewManager::getInstance()->_pWBMainView->getChildByTag(WorldBossMainView::TAG_DeathView);
			if (pDeathView)
			{
				pDeathView->runCD();
			}
		}
	}

    CCLog("3.......................");
	_fightProxy->showProcess();
}

void SceneFightMediator::playEffect()
{
    CCLog("1.......................");
	if(! _fightProxy->getIsCanPlay() )
	{  //Here again judgment has been two finished loading
				 
		CCLog("getIsCanPlay == false..............................");
		return;
	}
	if(_fightProxy && (!_fightProxy->playAgain))
	{
		loadWarFormation();
	}
    CCLog("2.......................");
	play();
}

void SceneFightMediator::loadWarFormation()
{
	if(!_fightScene)
		return;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	_fightScene->loadWarFormation(_fightProxy->formation, POSX(192), - POSX(130), 1, 0.8, 0.4);
	_fightScene->loadWarFormation(_fightProxy->oppositeFormation, - POSX(192+20), POSX(60), 1, 0.8, 0.4);
}

void SceneFightMediator::addBattleContent(char* data)
{
	//SCMD132
 	sendNotification(Facade_Command, AppFacade_FIGHT_PROXY_CHANGE, (char*)data, SceneFightProxyCommand::ADD_FIGHTPACK);
}

//The combat animation began to play
void SceneFightMediator::play()
{
	enginer = BattleEnginer::getInstance();
	enginer->_fightPack = &_fightProxy->fightPack;
	enginer->_fightRet = &_fightProxy->_fightRet;

	enginer->_fightReward = &_fightProxy->_fightReward;
	enginer->_battleReport = &_fightProxy->_battleReport;
	enginer->_id = _fightProxy->id;
	enginer->_type = _fightProxy->id != 0 ? EventType::PVE : EventType::PVP;
//	enginer->_rate=this->rate;

	//load all useful skill effect
	DWORD d1 = Timer::millisecondNow();
		CCLog("-------------------SKILL0813 begin: %d", d1);

//
////Begin Kenfly 20121108 : modify, load async
//	BitmapMovieClip* movieClip = NULL;
//	int effectCounter = 0;
//	std::vector<SCMD132>::iterator it_Round;
//	for (it_Round = enginer->_fightPack->begin(); it_Round != enginer->_fightPack->end(); it_Round++)
//	{
//		SCMD132& it_Round_Info = *it_Round;
//		for (std::vector<SCMD132::SCMD132Node1>::iterator it_SCMD132Node1 = it_Round_Info.c_Actions.begin(); it_SCMD132Node1 != it_Round_Info.c_Actions.end(); it_SCMD132Node1++)
//		{
//			//读取发起攻击播放的技能
//			SCMD132::SCMD132Node1& it_SCMD132Node1_Info = *it_SCMD132Node1;
//			
//			if (it_SCMD132Node1_Info.c_skill == 1)//反击不LOAD
//				continue;
//			SkillVo* m_skill = SkillManager::Instance()->getSkill(it_SCMD132Node1_Info.c_skill);
//			if (m_skill)
//			{
//				movieClip = EffectHelps::getSkillEffectMC(m_skill->resId, m_skill->acttime);
//				CC_SAFE_RELEASE(movieClip);
//			}
//		}
//	}
//	
//	movieClip = EffectHelps::getSkillEffectMC(200, 0.07f);//
//	CC_SAFE_RELEASE(movieClip);
//	movieClip = EffectHelps::getSkillEffectMC(201, 0.07f);
//	CC_SAFE_RELEASE(movieClip);
//	movieClip = EffectHelps::getSkillEffectMC(202, 0.07f);
//	CC_SAFE_RELEASE(movieClip);
//	movieClip = EffectHelps::getSkillEffectMC(203, 0.07f);
//	CC_SAFE_RELEASE(movieClip);
//	movieClip = EffectHelps::getSkillEffectMC(204, 0.1f);
//	CC_SAFE_RELEASE(movieClip);
////End Kenfly 20121108 


//Begin Kenfly 20121108 : modify, load async
/*	BitmapMovieClip* movieClip = NULL;
	int effectCounter = 0;
	std::vector<SCMD132>::iterator it_Round;
	for (it_Round = enginer->_fightPack->begin(); it_Round != enginer->_fightPack->end(); it_Round++)
	{
		SCMD132& it_Round_Info = *it_Round;
		for (std::vector<SCMD132::SCMD132Node1>::iterator it_SCMD132Node1 = it_Round_Info.c_Actions.begin(); it_SCMD132Node1 != it_Round_Info.c_Actions.end(); it_SCMD132Node1++)
		{
			//读取发起攻击播放的技能
			SCMD132::SCMD132Node1& it_SCMD132Node1_Info = *it_SCMD132Node1;
			
			if (it_SCMD132Node1_Info.c_skill == 1)//反击不LOAD
				continue;
			SkillVo* m_skill = SkillManager::Instance()->getSkill(it_SCMD132Node1_Info.c_skill);
			if (m_skill)
			{
				movieClip = EffectHelps::getSkillEffectMC(m_skill->resId, m_skill->acttime);
				CC_SAFE_RELEASE(movieClip);
			}
		}
	}
	
	movieClip = EffectHelps::getSkillEffectMC(200, 0.07f);//
	CC_SAFE_RELEASE(movieClip);
	movieClip = EffectHelps::getSkillEffectMC(201, 0.07f);
	CC_SAFE_RELEASE(movieClip);
	movieClip = EffectHelps::getSkillEffectMC(202, 0.07f);
	CC_SAFE_RELEASE(movieClip);
	movieClip = EffectHelps::getSkillEffectMC(203, 0.07f);
	CC_SAFE_RELEASE(movieClip);
	movieClip = EffectHelps::getSkillEffectMC(204, 0.1f);
	CC_SAFE_RELEASE(movieClip);
//End Kenfly 20121108 
*/

	DWORD d2 = Timer::millisecondNow(); 
		CCLog("-----------------SKILL0813 end. %d ,%f s", d2, d2*0.001 );
		CCLog("-----------------SKILL0813 use: %d ,%f s", (d2-d1), (d2-d1)*0.001 );
	//
	cocos2d::CCLog("enginer->execute()");
	enginer->execute();
}

void SceneFightMediator::abortFight()
{
	g_pGlobalManage->setisInFight( false ); 
	_fightProxy->_fightSceneCreate = false;

	/*
	int8 type = 1;
	type = _fightProxy->fightRet->c_win > 0 ? 1 : 0;
	CCMD138 *pCCMD138 = new CCMD138(type);

	_wSocket->sendMessage(pCCMD138);*/
	//int type = _fightProxy->_fightRet.c_win >= 0 ? 1 : 0;
	int type = _fightProxy->_winMark >= 0 ? 1 : 0;  // add by LH 0731
	g_pBattleManager->sendBattleStopHandler(type);


	// new hand tips
	int curMapID = RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId;
	if ((!type) && (curMapID == 1054))
	{
		int id = 22005;
		if (!ViewManager::getInstance()->_helpView)
		{
			ViewManager::getInstance()->_helpView = new NewHandHelpView();
			_dispatcher->addEventListener(GameDispatcher::RESET_NEWHELP_VIEW ,
				ViewManager::getInstance()->_helpView ,callfuncND_selector(NewHandHelpView::resetView));
		}
		
		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::RESET_NEWHELP_VIEW ,(void *)&id);

		//
		/*
		if (ViewManager::getInstance()->_pVScrollUI)
		{
			if (ViewManager::getInstance()->_pVScrollUI->getIsHide())
			{
				ViewManager::getInstance()->_pVScrollUI->clickHideVscroll();
			}
		}
		*/

	}
}

//// dungeron award gift
////void SceneFightMediator::dungeonAward( SCMD376& param )
//{
//	_fightProxy->_hasDungonAward = true;
//	CCSize cs = CCDirector::sharedDirector()->getWinSizeInPixels();
//	_fightProxy->dungeonAward = DungeonAwardAction::DungeonAwardActionWithRect( 
//		CCRectMake( cs.width/2-POSX(220/2), cs.height/2-POSX(260/2), POSX(220), POSX(260) )
//		);
//	if ( LayerManager::sceneUILayer && _fightProxy->dungeonAward )
//	{
//		_fightProxy->dungeonAward->initDungeonAwardActionVo( param );
//		LayerManager::sceneUILayer->addChild( _fightProxy->dungeonAward );
//	}
//	//_fightProxy._bData._callbacks.push(new DungeonAwardAction(param));
//}

void SceneFightMediator::addBattleFinish(char* data)
{
	//SCMD133
	sendNotification(Facade_Command, AppFacade_FIGHT_PROXY_CHANGE, data, SceneFightProxyCommand::ADD_FIGHTRET);
}

void SceneFightMediator::addFollowProcess(char * data)
{
	SCMD11F * cmd = (SCMD11F *)data;
	if(cmd->a_type == BattleType::PLAN_PROC_TYPE_DIALOG && g_pGlobalManage->getIsStorySystemOpen())
	{
		_fightProxy->_bData._tailStoryAction = new FightFollowStoryAction(cmd->b_id);
	}
}

void SceneFightMediator::fightOutHandler(int type, int battleType)
{	
	if (!enginer)//kevin0827
	{
		enginer = BattleEnginer::getInstance();
		enginer->_fightPack = &_fightProxy->fightPack;
		enginer->_fightRet = 0;

		enginer->_fightReward = 0;
		enginer->_battleReport = 0;
		enginer->_id = _fightProxy->id;
		enginer->_type = _fightProxy->id != 0 ? EventType::PVE : EventType::PVP;	

		ActionHandler::getInstance()->switchUpdate(false);
		ActionHandler::getInstance()->dispose();
		enginer->stop();
	}


	if( enginer )
	{
		enginer->dispose();
		enginer = 0;
	}



	if(_fightScene)
	{
		/*_fightScene.removeEventListener(FightScene.NORMAL_PLAY, normalPlay);
		_fightScene.removeEventListener(FightScene.SPEED_PLAY, speedPlay);
		_fightScene.removeEventListener(FightEnd.REPLAY, fightPlayAgain);
		_fightScene.removeEventListener(FightEnd.COPY_REPORT, copyReport);*/
		//delete _fightScene;
		if ( _fightScene->getParent() )
		{
			//CCTouchDispatcher::sharedDispatcher()->removeDelegate(_fightScene);
			_fightScene->dispose();
		//	_fightScene->release();
			_fightScene->getParent()->removeChild( _fightScene, true );
		}
		//_fightScene->release();
		_fightScene = 0;
		ViewManager::getInstance()->_fightScene = 0;
	}

	//var useTrigger:Boolean = 2>_roleManage.accountInfo.team; 
	//EnterCombatSceneMgr.getInstance().quitCombatScene(useTrigger);
	//SoundManager::Instance()->stopBattleBgSound(); // LH20120812 战斗背景音乐结束

	

	// world boss
	int curMapID = RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId;
	if (curMapID == 1208)
	{
		WorldBossMediator * pWBMediator = (WorldBossMediator *)g_pFacade->retrieveMediator(AppFacade_WorldBoss_Mediator);
		if (pWBMediator)
		{
			if (ViewManager::getInstance()->_pWBMainView )
			{
				DeathView * pDeathView = (DeathView * )ViewManager::getInstance()->_pWBMainView->getChildByTag(WorldBossMainView::TAG_DeathView);
				if (pDeathView)
				{
					pWBMediator->showDeathView(pDeathView->_isInCD);
				}
			}
		}
	}	
}
