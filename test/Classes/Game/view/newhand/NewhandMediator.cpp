#include "NewhandMediator.h"
#include "model/newhand/NewhandManager.h"
#include "model/task/TaskProxy.h"
#include "model/player/RoleManage.h"
#include "events/GameDispatcher.h"
#include "events/TaskEvent.h"
#include "manager/ViewManager.h"
#include "../task/components/TaskStrConcat.h"
#include "model/newhand/vo/TestNewhand.h"
#include "model/newhand/vo/NewhandConst.h"
#include "../dialog/DialogMediator.h"
#include "../task/components/TaskType.h"
#include "components/LeaderAlert.h"
#include "manager/GlobalManage.h"
#include "components/NewHandHelpView.h"
#include "../scene/components/story/callback/StoryFollowTipsAction.h"
#include "../fight/callback/fightCallBackTipsAction.h"
#include "model/scene/SceneManager.h"
#include "model/scene/vo/SceneType.h"

NewhandMediator::NewhandMediator()
{
	_count = 0;
	_buttonInit = false;
	_pNewhandManager = NewhandManager::Instance();
	_pNewhandView = NewHandView::Instance();
	//ViewManager::getInstance()->_helpView = new NewHandHelpView();
}

void NewhandMediator::handleNotification( int M2Vcmd, char* data )
{
	switch(M2Vcmd)
	{
	case CAN_TASKFOLLOW_TIP:
		//canTaskTrigger();
		// Not used in our version.
		// Yangliangjie
		break;

	case OWN_TASKFOLLOW_TIP:
		// Not used in web version 20120418.
		// Yangliangjie
		break;

	case INIT_BUTTONS:
		{
			_count++;
			if(_count==5){
				initButtonsHandle();
				_buttonInit = true;
			}
		}
		break;
			
	case FIGHT_LEADER:
		/*LeaderAlert.show(note.getBody().info);
		if(ViewManager.getInstance().mainNavigate){
			ViewManager.getInstance().mainNavigate.showButtonGlow(note.getBody().btn);
		}*/
		break;

	default:
		break;
	}
}

void NewhandMediator::startEventListener()
{
	GameDispatcher *_dispatcher = GameDispatcher::getInstance();
	_dispatcher->addEventListener(GameDispatcher::TEST_NEW_HAND, this, callfuncND_selector(NewhandMediator::testNewHand));
	_dispatcher->addEventListener(GameDispatcher::CAN_TASK_DATA_CHANGE, this, callfuncND_selector(NewhandMediator::canTaskTrigger));
	_dispatcher->addEventListener(GameDispatcher::REC_TASK_DATA_CHANGE, this, callfuncND_selector(NewhandMediator::ownTaskTrigger));
	_dispatcher->addEventListener(TaskEvent::RECEIVE, this, callfuncND_selector(NewhandMediator::receiveTaskTrigger));
	_dispatcher->addEventListener(TaskEvent::SUBMIT, this, callfuncND_selector(NewhandMediator::submitTaskTrigger));
	_dispatcher->addEventListener(GameDispatcher::CRYSTAL_LEVEL_CHANGE, this, callfuncND_selector(NewhandMediator::cryLevTrigger));
	_dispatcher->addEventListener(GameDispatcher::NEWHAND_TIPS_LEVEL , this ,callfuncND_selector(NewhandMediator::newHandTipsByLevel));

	//_dispatcher->addEventListener(GameDispatcher::RESET_NEWHELP_VIEW , ViewManager::getInstance()->_helpView ,callfuncND_selector(NewHandHelpView::resetView));

	
	PlayerBaseVo *pPlayerBaseInfo = &RoleManage::Instance()->roleInfo()->playerBaseInfo;
	if(pPlayerBaseInfo)
	{
		pPlayerBaseInfo->addEventListener(LiveThingVo::CHANGELEV, this, callfuncND_selector(NewhandMediator::roleLevTrigger));
	}
	//_roleManager.roleInfo.playerBaseInfo.addEventListener(LiveThingVo.CHANGELEV, roleLevTrigger);	//监听角色等级更新
}

void NewhandMediator::initButtonsHandle()
{
   // return;
	TaskProxy *pTaskProxy = (TaskProxy *) g_pFacade->retrieveProxy(AppFacade_TASK_PROXY);
	if(!pTaskProxy) return;

	vector<int> taskArr = pTaskProxy->getFinishOrRecvTask();
	std::list<StepVo *> voArr;

	vector<int>::iterator taskIt;
	std::list<StepVo *> arr;
	for(taskIt = taskArr.begin(); taskIt != taskArr.end(); ++ taskIt)
	{
		int id = *taskIt;
		arr = _pNewhandManager->getRcvTaskStepVo(id);
		voArr.splice(voArr.end(), arr);

		arr = _pNewhandManager->getSmtTaskStepVo(id);
		voArr.splice(voArr.end(), arr);
	}

	int lev = RoleManage::Instance()->roleLev();
	for(int i=0; i<=lev; ++i)
	{
		arr = _pNewhandManager->getLevelStepVo(9900 + i);
		voArr.splice(voArr.end(), arr);
	}

	struct Data 
	{
		std::list<StepVo *> voArr;
		bool isTween;
	};
	Data *data = new Data();
	data->voArr = voArr;
	data->isTween = false;

	sendHandle(this, data);
    std::vector<TaskVo *> canlist = _taskProxy->getCanTasks();
    std::vector<TaskVo *> reclist = _taskProxy->getAllRecTask();
	canTaskTrigger(this, &canlist);
	ownTaskTrigger(this, &reclist);
	startEventListener();
}

void NewhandMediator::sendHandle( CCNode *pNode, void *data )
{
	//Doyang 20120727	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::WALK_COMPLETE,0);
	Scene *pScene = ViewManager::getInstance()->_scene;
	if(pScene && pScene->_role && pScene->_role->poseState)
	{
		pScene->_role->poseState->state(SceneConst::STAND);
	}

	struct Data 
	{
		std::list<StepVo *> voArr;
		bool isTween;
        /*
		~Data()
		{
			for (std::list<StepVo *>::iterator it = voArr.begin(); it != voArr.end(); it++)
			{
				StepVo *tmp = *it;
				SAFE_DELETE(tmp);
			}
			voArr.clear();
		}
         */
	};
	Data *sData = (Data *) data;
	//ViewManager *pViewManager = ViewManager::getInstance();
	std::list<StepVo *>::iterator it;

	for(it = sData->voArr.begin(); it != sData->voArr.end(); ++ it)
	{
		StepVo *pStep = *it;
		if(!pStep)
			continue;


		if(pStep->btnId >= 300)
		{
			movieToAddButton(pStep, sData->isTween);
		}
		else if(pStep->btnId >= 200)
		{
			if(sData->isTween)
			{
				////sendNotification(DialogMediator.SET_AUTO_POP, false); 
				//ModuleLoaderManage.getInstance().load(ResourceName.CHAPTER_PATH, LoadLevel.HIGH, 
				//	DisplayObjectManager.showChapter, vo.btnSit);
			}
		}
		else if(pStep->btnId >= 100)
		{
			if(sData->isTween)
			{
				crystalUpdateInfo(pStep);
			}
		}
		else if(pStep->btnId >= 70)
		{
			continue;
		}
		else if(pStep->btnId >= 50)
		{
			/*if(viewMng.cdList){
				var cdtype:int = NewhandConst.getCDType(vo.btnId);
				if(cdtype!=-1)
					viewMng.cdList.addCdItems(cdtype, vo.btnSit);
			}*/
/*			if ( ViewManager::getInstance()->cdList )
			{
				int cdtype = NewhandConst::Instance()->getCDType(pStep->btnId);
				ViewManager::getInstance()->cdList->_typeVec.push_back(cdtype);
			}*/			
		}
		else if(pStep->btnId >= 30)
		{
			/*if(viewMng.smallMapUI){
			viewMng.smallMapUI.addButton(vo.btnId, vo.btnSit, isTween);
			}*/
		}
		else if(pStep->btnId >= 0)
		{
			movieToAddButton(pStep, sData->isTween);
		}
	}
    
    
    for (std::list<StepVo *>::iterator it = sData->voArr.begin(); it != sData->voArr.end(); it++)
    {
        StepVo *tmp = *it;
        SAFE_DELETE(tmp);
    }
    sData->voArr.clear();
    CC_SAFE_DELETE(sData);
}

void NewhandMediator::canTaskTrigger( CCNode *pNode, void *data )//std::vector<TaskVo *> canTaskList )
{
	if(!data)
	{
		return;
	}

	std::vector<TaskVo *> canTaskList = *(std::vector<TaskVo *> *) data;
	/*if(!_taskFollowView)
		_taskFollowView = (facade.retrieveMediator(TaskFollowMediator.NAME) as TaskFollowMediator).view;*/

	std::vector<TaskVo *>::iterator it;
	for(it = canTaskList.begin(); it != canTaskList.end(); ++it)
	{
		TaskVo *pTask = *it;
		if(pTask->_id == 1)
		{
			_pNewhandManager->_isNewAcount = true;
		}

		ScriptVo *pScript = _pNewhandManager->getCanTaskScript(pTask->_id);
		if(pScript){
			/*if(_taskFollowView)
			_taskFollowView.taskType = 1;
			if(GlobalManage.getInstance().isInFight){
			_handManager.addCallBack(0, _newHandView.testScript, [script]);
			}
			else{
			_newHandView.testScript(script);
			}*/
			struct Data 
			{
				Data()
				{
					pScript = 0;
					finished = false;
				}
				ScriptVo *pScript;
				bool finished;
			};
			Data *data = new Data();
			data->pScript = pScript;
			data->finished = false;
			_pNewhandView->testScript(this, data);
			return;
		}	                                                         
	}
}

void NewhandMediator::ownTaskTrigger( CCNode *pNode, void *data )//std::vector<TaskVo *> recTaskList )
{
	if(!data)
	{
		return;
	}
	std::vector<TaskVo *> recTaskList = *(std::vector<TaskVo *> *) data;

	ScriptVo *pScript;
//	bool finish = false;

	std::vector<TaskVo *>::iterator it;
	for(it = recTaskList.begin(); it != recTaskList.end(); ++ it)
	{
		TaskVo *pTask = *it;
		if(TaskStrConcat::checkTaskFinish(pTask->_taskTip))
		{
			pScript = _pNewhandManager->getFinTaskScript(pTask->_id);
//			finish = true;
		}
		else
		{
			pScript = _pNewhandManager->getOwnTaskScript(pTask->_id);
		}

		if(pScript)
		{
			/*if(_taskFollowView)
			_taskFollowView.taskType = 0;*/
			struct Data 
			{
				Data()
				{
					pScript = 0;
					finished = false;
				}
				ScriptVo *pScript;
				bool finished;
			};
			Data* sData = new Data();
			sData->pScript = pScript;
			sData->finished = false;
			if(g_pGlobalManage->_isInFight)
			{
				NewhandManager::Instance()->addCallBack(0,
					(CCNode *)_pNewhandView,
					callfuncND_selector(NewHandView::testScript),
					sData);
			}
			else
			{
				_pNewhandView->testScript(this, sData);
			}
			return;
		}
	}
}

void NewhandMediator::receiveTaskTrigger( CCNode *pNode, void *data )
{
	if(!data)
	{
		return;
	}

	TaskEvent *pTaskEvent = (TaskEvent *) data;
	if(!pTaskEvent)
	{
		return;
	}
    
    int id = pTaskEvent->id;

//    CC_SAFE_DELETE(pTaskEvent);
    
	if(_buttonInit){
		std::list<StepVo *> list = _pNewhandManager->getRcvTaskStepVo(id);
		if(list.size() > 0)
		{
			struct Data
			{
				Data()
				{
					isTween = false;
				}
				std::list<StepVo *> voArr;
				bool isTween;
			};
			Data *data = new Data();
			data->voArr = list;
			data->isTween = true;
			if(g_pGlobalManage->_isInFight)
			{
				NewhandManager::Instance()->addCallBack(0, 
					this,
					callfuncND_selector(NewhandMediator::sendHandle),
					data);
			}
			else{
				sendHandle(this, data);
			}
		}
	}
	//Doyang 20120712
	TestNewhand *pTestNewhand = new TestNewhand("rcvTask", NULL, id);
	_pNewhandView->eventTrigger(pTestNewhand);
	CC_SAFE_DELETE(pTestNewhand);
	
}

void NewhandMediator::submitTaskTrigger( CCNode *pNode, void *data )
{
	if(!data)
	{
		return;
	}

	TaskEvent *pTaskEvent = (TaskEvent *) data;
	if(!pTaskEvent)
	{
		return;
	}
    
    int id = pTaskEvent->id;
    
    //CC_SAFE_DELETE(pTaskEvent);

	if(_buttonInit){
		std::list<StepVo *> list = _pNewhandManager->getSmtTaskStepVo(id);
		if(list.size() > 0)
		{
			struct Data
			{
				Data()
				{
					isTween = false;
				}
				std::list<StepVo *> voArr;
				bool isTween;
			};
			Data *data = new Data();
			data->voArr = list;
			data->isTween = true;
			if(g_pGlobalManage->_isInFight)
			{
				NewhandManager::Instance()->addCallBack(0, 
					this,
					callfuncND_selector(NewhandMediator::sendHandle),
					data);
			}
			else{
				sendHandle(this, data);
			}
		}
	}
	//Doyang 20120712
	TestNewhand *pTestNewhand = new TestNewhand("smtTask", NULL, id);
	_pNewhandView->eventTrigger(pTestNewhand);
	CC_SAFE_DELETE(pTestNewhand);
}

void NewhandMediator::cryLevTrigger( CCNode *pNode, void *data )
{
	if(!data)
	{
		return;
	}

	struct Data
	{
		int type;
		int lev;
	};
	Data *pData = (Data *) data;
	if(!pData)
	{
		return;
	}

	//if(_pNewhandManager->_nextEventId == NewhandConst::EVENT_CRY_WIND && 
	//		pData->type == CrystalType::CRYSTAL_FENG)
	if((!_pNewhandManager->_nextEventIdList.empty()) 
		&& (_pNewhandManager->_nextEventIdList.front() == NewhandConst::EVENT_CRY_WIND)
		&& pData->type == CrystalType::CRYSTAL_FENG)
	{
		//Doyang 20120712
		TestNewhand *pTestNewhand = new TestNewhand("evt", NULL, _pNewhandManager->_nextEventIdList.front());
		_pNewhandView->eventTrigger(pTestNewhand);
		CC_SAFE_DELETE(pTestNewhand);
	}
	/* 水晶升级触发newhandStep配置开启功能 */
	int index = pData->type * 100 + pData->lev;
	std::list<StepVo *> stepArr = _pNewhandManager->getLevelStepVo(index);
	if(stepArr.size() > 0){
		struct Data 
		{
			std::list<StepVo *> voArr;
			bool isTween;
		};
		Data *sData = new Data();
		sData->voArr = stepArr;
        sData->isTween = true;

		sendHandle(this, sData);
	}
    //if (pData)
    //    SAFE_DELETE(pData)//kevinchange0810	jae0813
}

void NewhandMediator::roleLevTrigger( CCNode *pNode, void *data )
{
	if(!data)
	{
		return;
	}

	RoleManage *pRoleManager = RoleManage::Instance();
	int index = 9900 + pRoleManager->roleLev();
	std::list<StepVo *> list = _pNewhandManager->getLevelStepVo(index);
	if(list.size() > 0)
	{

		struct Data 
		{
			std::list<StepVo *> voArr;
			bool isTween;
		};
		Data *sData = new Data();
		sData->voArr = list;
		sData->isTween = true;

		sendHandle(this, sData);
	}
	// 监控幻龙塔和世界Boss银矿战的开启,让传送门高亮
	if(pRoleManager->roleLev() == 40 || pRoleManager->roleLev() == 45){
		//this.sendNotification(MainUIMediator.SET_CONVEY_HIGHLIGHT,true);
	}

}

void NewhandMediator::testNewHand( CCNode *pNode, void *data )
{
	if(!data)
	{
		return;
	}


	TestNewhand *pNewhand = (TestNewhand *) data;
	if(!pNewhand)
	{
		return;
	}

	if(pNewhand->type=="addBtn" || (pNewhand->type=="evt" && pNewhand->pScript))
	{
		struct Data 
		{
			Data()
			{
				pScript = 0;
				finished = false;
			}
			ScriptVo *pScript;
			bool finished;
		};
		Data *data = new Data();
		data->pScript = pNewhand->pScript;
		data->finished = false;
		
		_pNewhandView->testScript(this, data);
	}
	else
	{
		_pNewhandView->eventTrigger(pNewhand);
	}
}

void NewhandMediator::movieToAddButton( StepVo *pStep, bool isTween )
{
	if(!pStep)
	{
		return;
	}

	if(isTween && pStep->param.size() > 2)
	{//有图片演示
		sendNotification(Facade_Mediator, AppFacade_NPCDIALOGUE_PROXY_CHANGE, NULL, DialogMediator::SET_AUTO_POP); 
		//ModuleLoaderManage.getInstance().load(ResourceName.TUTOR_PATH, LoadLevel.HIGH, paperPop, vo);

		// callback handler
		if (SceneManager::Instance()->getCurMapType() != SceneType::CITY)
		{
			SceneProxy * pSceneProxy = (SceneProxy *)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
			if (pSceneProxy)
			{
				pSceneProxy->_callbacks.push_back((BaseAction *)new fightCallBackTipsAction(pStep));
			}
		}
		else if (g_pGlobalManage->getisInFight())
		{
			FightProxy * pFightProxy = (FightProxy *)g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
			if (pFightProxy)
			{
				pFightProxy->_bData._callbacks.push_back((BaseAction *)new fightCallBackTipsAction(pStep));
			}
		}
		else
		{
			this->paperPop(pStep);
		}
	}
	else
	{//只开启按钮，没有图片演示
		addButton(pStep, isTween);
	}
}

void NewhandMediator::addButton( StepVo *pStep, bool isTween )
{
	if(ViewManager::getInstance() && pStep)
	{
		if(pStep->btnId >= 320)
		{
			//开启次导航按钮
			if(ViewManager::getInstance()->_secNavigate)
			{
				ViewManager::getInstance()->_secNavigate->addButton(pStep->btnId,
					pStep->btnSit,
					isTween);
			}
		}
		else if (pStep->btnId >= 1)
		{
			//开启主导航按钮
			if(ViewManager::getInstance()->mainNavigate)
			{
				ViewManager::getInstance()->mainNavigate->addButton(pStep->btnId,
					pStep->btnSit,
					isTween);
			}
		}

	}
}

void NewhandMediator::newHandTipsByLevel(CCNode *pNode, void *data)
{
	StepVo *pStep = (StepVo *)data;
	if (!pStep)
	{
		return;
	}	
	paperPop(pStep);
}

void NewhandMediator::paperPop( StepVo *pStep )
{
	// stop walking
	/*
	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::WALK_COMPLETE,0);
	if (ViewManager::getInstance()->_scene)
	{
		ViewManager::getInstance()->_scene->roleStopMove();
	}
	*/
	
	if(!pStep 
		|| pStep->param.size() < 2)
	{
		return;
	}
	int picId = atoi(pStep->param[2].c_str());//图片id
	int type = picId== 1 ? 4 : 5;//图片1是招募伊莎贝尔
	char picChar[10];
	sprintf(picChar, "%d", picId);
	string picStr;
	picStr = picChar;
	//Doyang 20120725
	StepVo *pCloneStepVo = new StepVo();;
	pCloneStepVo->btnId = pStep->btnId;
	pCloneStepVo->btnSit = pStep->btnSit;
	pCloneStepVo->id = pStep->id;
	pCloneStepVo->info = pStep->info;
	pCloneStepVo->param.assign(pStep->param.begin(), pStep->param.end());
	pCloneStepVo->trigger.assign(pStep->trigger.begin(), pStep->trigger.end());
	if (pCloneStepVo->btnId == -1)
	{
		LeaderAlert::show(picStr, type, true, NULL, NULL, NULL);
	}
	else
	{
		LeaderAlert::show(picStr, type, false, this, callfuncND_selector(NewhandMediator::afterMovie), pCloneStepVo);
	}
	
	// close pop
	{
		if (ViewManager::getInstance()->dialogView
			&& ViewManager::getInstance()->dialogView->getisPop())
		{
			ViewManager::getInstance()->dialogView->setisPop(false);
		}		
	}
}

void NewhandMediator::afterMovie( CCNode *pNode, void *data )
{
	StepVo *pStep = (StepVo *) data;
	if(!pStep)
		return;
	char tmp[1] = {0}; // LH0713
	sendNotification(Facade_Mediator, AppFacade_NPCDIALOGUE_PROXY_CHANGE, /*new char[1]*/(char *)tmp, DialogMediator::SET_AUTO_POP);  // LH0713
	if(pStep->btnId != 0 )
	{
		addButton(pStep, true);
	}
	if(pStep->param.size() == 5){//甚至还有寻路
		FindVo *pFindVo = new FindVo();
		pFindVo->_sceneId = atoi(pStep->param[3].c_str());
		pFindVo->_npcId = atoi(pStep->param[4].c_str());
		pFindVo->_type = TaskType::NPC;
		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::FIND_ELEMENT, pFindVo);
	}

	//Doyang 20120725
	CC_SAFE_DELETE(pStep);
}

void NewhandMediator::crystalUpdateInfo( StepVo *pStep )
{

}






