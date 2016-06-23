#include "SceneStoryMediator.h"
#include "../../model/scene/vo/StoryScript.h"
#include "../../model/com/ResourceManage.h"
#include "../../model/com/vo/ResourceVo.h"
#include "../../../com/utils/loader/LoadLevel.h"
#include "../../manager/SourceCacheManage.h"
#include "../../manager/ViewManager.h"
#include "components/StoryScene.h"
#include "../load/LoadStorySceneMediator.h"
#include "../../model/scene/vo/StoryElement.h"
#include "../../util/TileUtil.h"
#include "../../control/scene/SceneStoryProxyCommand.h"
#include "model/scene/fight/sweeper/PassbyStory.h"
#include "manager/LayerManager.h"
#include "manager/GlobalManage.h"
#include "SceneListenerMediator.h"
#include "../dialog/DialogMediator.h"
#include "manager/layer/TipsLayer.h"

SceneStoryMediator::SceneStoryMediator()
{
	_storyVo = 0;
	_storyScene = 0;
	_dispatcher->addEventListener(GameDispatcher::OUT_STROY,this, callfuncND_selector(SceneStoryMediator::outStoryHandler));
}

SceneStoryMediator::~SceneStoryMediator()
{

}

void SceneStoryMediator::handleNotification( int M2Vcmd, char* data )
{
	switch(M2Vcmd) 
	{
	case ROLE_MOVETOTARGET_STARTSTORY:
		tweenToTargetStartStory(*(int*)data);
		break;
	case ADDPLAYER:
		addPlayer(data);
		break;
	case REMOVEPLAYER:
		removePlayer(data);
		break;
	case ADDNPC:
		addNPC(data);
		break;
	case REMOVENPC:
		removeNPC(data);
		break;
	case ADDITEM:
		addItem(data);
		break;
	case REMOVEITEM:
		removeItem(data);
		break;
	case INTO_STORY:
		intoStory(data);
		break;
	case OUT_STORY:
		outStory(data);
		break;
	case SHOW_NEXT:
		showNext(data);
		break;
	case STORY_SHORTCUT:
		mapShortcut();
		break;
	}
}

StoryScene * SceneStoryMediator::getStoryScene()
{
	return _storyScene;
}


void SceneStoryMediator::tweenToTargetStartStory(int storyID)
{
	if (g_pGlobalManage->_isInFight || !g_pGlobalManage->getIsStorySystemOpen())
	{
		return;
	}
	//addEventListener(int flag, CCNode* tar, SEL_CallFuncND selector)
	/*
	//  
	var callback:Function = function(e:Event):void{
		_dispatcher.removeEventListener(GameDispatcher.STORY_CALLBACK, callback);
		facade.sendNotification(AppFacade.TRIGGER_STORY, id);
	};
	_dispatcher.addEventListener(GameDispatcher.STORY_CALLBACK, callback);

	//			EnterStorySceneMgr.getInstance().gotoStoryScene(id);

	new PassbyStory(id).sweep();
	*/

	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::WALK_COMPLETE,0);

	PassbyStory * pPassBy = new PassbyStory(storyID);
	pPassBy->sweep();

	sendNotification(Facade_Command,AppFacade_SCENESTORY_PROXY_CHANGE,0,SceneStoryProxyCommand::JOIN_ELEMENT);
	//sendNotification(Facade_Mediator, AppFacade_SCENELISTENER_MEDIATOR,0, SceneListenerMediator::START_SCENE_LISTENER);

	CC_SAFE_DELETE(pPassBy); // LH0711
}

// 
void SceneStoryMediator::intoStory(char * data)
{
	GameDispatcher::getInstance()->addEventListener(GameDispatcher::STORY_FOLLOW_CALLBACK,this,callfuncND_selector(SceneStoryMediator::storyCallback));

	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::WALK_COMPLETE,0);
	/// if current story need to load UI?
	if((_storyProxy->getStoryVo())&&(inspectElements(&_storyProxy->getStoryVo()->script)))
	{
		//ModuleLoaderManage.getInstance().load(ResourceName.DRAMA_PATH, LoadLevel.HIGH, loadStoryFace);
		loadStoryFace(); 
	}
	else
	{
		loadStoryFace(); 
	}

	//
	if(ViewManager::getInstance()->mainNavigate)
	{
		ViewManager::getInstance()->mainNavigate->showVScrollAndTaskUIView(false);
	}
}

void SceneStoryMediator::loadStoryFace()
{
	if((_storyProxy->getStoryVo())&&(inspectScripts(&_storyProxy->getStoryVo()->script)))
	{
		//ModuleLoaderManage.getInstance().load(ResourceName.DRAMA_FACE_PATH, LoadLevel.FIRST, buildStoryScene);
		buildStoryScene();
	}
	else
	{
		buildStoryScene();
	}
}

// 
bool SceneStoryMediator::inspectElements(std::vector<StoryScript>* script)
{
	bool needLoad = false;
	std::vector<StoryScript>::iterator iter = script->begin();
	while(iter!=script->end())
	{
		StoryScript storyScript = script->front();
		if(storyScript.dir == 0 || storyScript.dir == 1)
		{
			needLoad = true;
			break;
		}
		++iter;
	}
	return needLoad;
}

bool SceneStoryMediator::inspectScripts(std::vector<StoryScript>* script)
{
	bool needLoad = false;
	std::vector<StoryScript>::iterator iter = script->begin();
	while(iter!=script->end())
	{
		StoryScript storyScript = script->front();
		if(storyScript.resid>1000)
		{
			needLoad = true;
			continue;
		}
		else if(storyScript.resid>0 && storyScript.resid<=1000)
		{
			//ResourceVo *pResourceVo = ResourceManage::Instance()->getRes(1/*ResType.SKILL_TYPE*/, storyScript.resid);
			//if(pResourceVo)
			//{
			//	SourceCacheManage::Instance()->loadModel(pResourceVo->getSkillUrl(),LoadLevel::LOW,0.1f,true);
			//}
		}
		++iter;
	}
	return needLoad;
}

void SceneStoryMediator::buildStoryScene()
{
	// 
	//_dispatcher->dispatchEvent(GameDispatcher::INTO_STORY,this);

	Scene * scene = ViewManager::getInstance()->_scene;
	SceneInfoVo * pInfoVo = _sceneProxy->sceneInfoVo();
	if (!pInfoVo)	{return;}
	StoryVo * pStoryVo = _storyProxy->getStoryVo();
	if (!pStoryVo){return;}

	_storyScene = new StoryScene(*scene, *pStoryVo, pInfoVo);
	
	// 
	_storyScene->addEventListener(StoryScene::SHOW_NEXT,this,callfuncND_selector(SceneStoryMediator::getNext));

	if(pStoryVo->id == 1012)
	{
		_storyScene->showNewhandLeader();
	}

	//sendNotification(Facade_Mediator,AppFacade_SCENESTORY_PROXY_CHANGE,0,LoadStorySceneMediator::SHOW_PROCESS);

}

void SceneStoryMediator::outStoryHandler(char * data)
{
	outStory(data);
}

void SceneStoryMediator::outStory(char * data)
{
	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::STORY_CALLBACK,0);

	sendNotification(Facade_Mediator, AppFacade_SCENELISTENER_MEDIATOR, (char*)data, SceneListenerMediator::START_SCENE_LISTENER);
	
	if (_storyScene)
	{
		_storyScene->dispose();
	}

	if (g_pGlobalManage)
	{
		g_pGlobalManage->isInStory = false;
		g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID());
	}

	// 20120620
	// Doyang.
	// Add this instead of REMOVE_STORY_SCENE
	char tmp[1] = {0}; // LH0713
	sendNotification(Facade_Mediator, AppFacade_NPCDIALOGUE_PROXY_CHANGE, (char *)tmp, DialogMediator::SET_AUTO_POP); 

	//
	if(ViewManager::getInstance()->mainNavigate)
	{
		ViewManager::getInstance()->mainNavigate->showVScrollAndTaskUIView(true);
	}
}

void SceneStoryMediator::addPlayer(char * data)
{
	struct _INFO_
	{
		PlayerBaseVo info;
		int vis;
	} Info;
	_INFO_ *pInfo = (_INFO_ *)data;
	if(!_storyScene){return;}
	Player *play = _storyScene->addPlayerHandler((char *)&pInfo->info);

	//Player *play = _storyScene->BaseScene::addPlayerHandler(&pInfo->info);

	play->setIsVisible((pInfo->vis == 1) ? true : false);

	//play->release(); // LH0709
}

void SceneStoryMediator::removePlayer(char * data)
{
	_storyScene->removePlayer(*(int *)data);
}

void SceneStoryMediator::addNPC(char * data)
{
	struct _INFO_
	{
		NPCVo info;
		int vis;
	} Info;
	_INFO_ *pInfo = (_INFO_ *)data;
	if(!_storyScene){return;}
	MapNPC *npc = _storyScene->addNPC((char *)&pInfo->info);
	npc->setIsVisible((pInfo->vis == 1) ? true : false);

	//npc->release(); // LH0709
}

void SceneStoryMediator::removeNPC(char * data)
{
	_storyScene->removeNPC(*(int*)data);
}

void SceneStoryMediator::addItem(char * data)
{
	struct _INFO_
	{
		ItemVo info;
		int vis;
	} Info;
	_INFO_ *pInfo = (_INFO_ *)data;
	if(!_storyScene){return;}
	Item *item = _storyScene->addItem((char *)&pInfo->info);
	item->setIsVisible((pInfo->vis == 1) ? true : false);

	//item->release(); // LH0709
}

void SceneStoryMediator::removeItem(char * data)
{
	_storyScene->removeItem(*(int *)data);
}

void SceneStoryMediator::showNext(char * data)
{
	StoryScript *storyNode = (StoryScript*)data;
	storyNode->type = _storyProxy->getType(storyNode->index);  //  
	storyNode->id = _storyProxy->getId(storyNode->index);		// 

	if( storyNode->tox!=0 && storyNode->toy!=0)
	{
		CCPoint focusPos = TileUtil::Instance()->changePixsToTile(_sceneProxy->_focusPos);
		storyNode->_tox = storyNode->tox ;
		storyNode->_toy = storyNode->toy ;
		storyNode->move = true;
	}
	_storyScene->showNext(*storyNode);
}

void SceneStoryMediator::getNext(char *data)
{
	sendNotification(Facade_Command,AppFacade_SCENESTORY_PROXY_CHANGE,data,SceneStoryProxyCommand::SHOW_NEXT);
}

//
void SceneStoryMediator::mapShortcut()
{
	if(this->getStoryScene()) 
	{
		this->getStoryScene()->dispatchEvent(0,0/*new MouseEvent(MouseEvent.MOUSE_DOWN)*/);
	}
}

void SceneStoryMediator::storyCallback(CCNode * pNode , void * data)
{
	StoryProxy * pStoryProxy = (StoryProxy *)g_pFacade->retrieveProxy(AppFacade_SCENESTORY_PROXY_CHANGE);
	if (pStoryProxy)
	{
		std::list<IAction *> callbackList = pStoryProxy->storyCallbackActionList;
		while (!callbackList.empty())
		{
			BaseAction *pAction = (BaseAction *) callbackList.front();
			if (pAction)
			{
				pAction->doAction();
				pAction->delAction(callbackList.front());
				callbackList.pop_front();
				//CC_SAFE_DELETE(pAction);
			}
		}
		callbackList.clear();
	}
}