#include "TaskFollowMediator.h"
#include "manager/LayerManager.h"
#include "manager/ViewManager.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "../purchase/PurchaseMediator.h"
#include "../vip/VipMediator.h"
#include "../newhand/NewhandMediator.h"
#include "components/TaskAutoFindNpc.h"
#include "manager/GlobalManage.h"
#include "components/TaskUtil.h"
#include "manager/PopEventName.h"
#include "PopContainer.h"
#include "components/TaskUIView.h"

TaskFollowMediator::TaskFollowMediator()
{
	_pTaskProxy = (TaskProxy *) g_pFacade->retrieveProxy(AppFacade_TASK_PROXY);
	GameDispatcher::getInstance()->addEventListener(GameDispatcher::TASK_AUTO_FIND_NPC,
		this, 
		callfuncND_selector(TaskFollowMediator::autoFindNpc));

	GameDispatcher::getInstance()->addEventListener(TaskFollowMediator::SHOW_TASK_FOLLOW_LIST,
		this,
		callfuncND_selector(TaskFollowMediator::showTaskFollowList));
	GameDispatcher::getInstance()->addEventListener(TaskFollowMediator::DISMISS_TASK_FOLLOW_LIST,
		this,
		callfuncND_selector(TaskFollowMediator::dismissTaskFollowList));

	GameDispatcher::getInstance()->addEventListener(PopContainer::OPEN_CONTAINER,
		this,
		callfuncND_selector(TaskFollowMediator::dismissTaskFollowList));
	_pFollowView = NULL;
}

TaskFollowMediator::~TaskFollowMediator()
{

}

void TaskFollowMediator::addToStage()
{
	_pFollowView = new TaskFollowView();
	if(_pFollowView && _pFollowView->init())
	{
		_pFollowView->initData(_pTaskProxy->_receivedTaskList);
	//	//LayerManager::sceneUILayer->addChild(_pFollowView);
	//	//Doyang 20120717
	//	//_pFollowView->release();

		ViewManager::getInstance()->taskFollowView = _pFollowView;

		_pFollowView->addEventListener(TaskUtil::FIND_ELEMENT, _pFollowView, callfuncND_selector(TaskFollowMediator::findElement));
	}

	//// test
	/*PurchaseMediator *pPurchaseMediator = new PurchaseMediator();
	pPurchaseMediator->openPurchaseView();*/
	/*VipMediator *pVipMediator = new VipMediator();
	pVipMediator->popHandler();*/

	sendNotification(Facade_Mediator, AppFacade_NEWHAND_MEDIATOR, 0, NewhandMediator::INIT_BUTTONS);


	// LH20121026 new task UI
	/*if (_pFollowView)
	{
		_pFollowView->setIsVisible(false);
	}*/
	TaskUIView * pTaskView = new TaskUIView();
	if (pTaskView)
	{
		ViewManager::getInstance()->_taskUIView = pTaskView;
		pTaskView->init();
		pTaskView->_recTaskList = _pTaskProxy->_receivedTaskList;
		pTaskView->_canTaskList = _pTaskProxy->_canTaskList;
		pTaskView->resetScrollView();
		LayerManager::sceneUILayer->addChild(pTaskView,1);
		pTaskView->release();
	}
	
}

void TaskFollowMediator::refRecTask( std::vector<TaskVo *> &recList )
{
	//Doyang 20120711
	/*_pFollowView->_recList = recList;
	_pFollowView->refresh();*/

	//LH20121026
	TaskUIView * pTaskUIView = ViewManager::getInstance()->_taskUIView;
	if (pTaskUIView)
	{
		pTaskUIView->_recTaskList = recList;
		pTaskUIView->resetScrollView();
	}
}

void TaskFollowMediator::handleNotification( int M2Vcmd, char* data )
{
	switch(M2Vcmd)
	{
	case ADD_TO_STAGE:
		addToStage();
		break;

	default:
		break;
	}
}

void TaskFollowMediator::autoFindNpc( CCNode *pNode, void *data )
{
	if(!data)
		return;

	_autoFindTaskVo = (TaskVo *) data;
	if(!_autoFindTaskVo)
		return;

	if(_autoFindTaskVo && _autoFindTaskVo->_type != 3 && _pFollowView)
	{
		/*TimerManage.getInstance().remove(func);
		TimerManage.getInstance().add(1600,func);*/
		func();
	}
}

void TaskFollowMediator::func()
{
	if(RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId == 1001 
		&& g_pGlobalManage->_isInFight)
	{
		// 对和妮卡战斗的任务做特殊处理
		//TimerManage.getInstance().remove(func);
		//TimerManage.getInstance().add(5000,func2);// 5000ms 为最快结束战斗并退出战斗场景的时间，立即结束战斗除外
		func2();
	}
	else
	{
		//findElement(new ParamEvent(TaskUtil.FIND_ELEMENT, TaskAutoFindNpc.getInstance().taskFollowStr(_autoFindTaskVo)));
        string str = TaskAutoFindNpc::Instance()->taskFollowStr(_autoFindTaskVo);
		findElement(NULL, &str);
		/*TimerManage.getInstance().remove(func);*/
	}
}

void TaskFollowMediator::func2()
{
	if(RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId == 1001  && g_pGlobalManage->_isInFight){
		// 5000ms后，玩家爱点不点战斗结果面板上的“确定”，程序表示没办法，只能每200ms判断一次玩家有没有退出战斗场景
		/*TimerManage.getInstance().remove(func2);
		TimerManage.getInstance().add(200,func2);*/
	}
	else{
		/*TimerManage.getInstance().remove(func2);
		TimerManage.getInstance().add(1600,func);*/
	}
}

void TaskFollowMediator::findElement( CCNode *pNode, void *data )
{
	if(g_pGlobalManage->_isInFight || g_pGlobalManage->isInStory) return ;

	if(!data)
		return;

	string str = * (string*)data;
			
	/*if(!GlobalManage.getInstance().canMove){
		Alert.show(LangManager.getText("TSK071"));
		return;
	}*/
	
	/*var param:String = e.param as String;*/
	
	if(str == "open_4_equip")
	{
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_FIGURE, NULL);
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_BAG, NULL);
		/*if( !(ViewManager.getInstance().figureView && ViewManager.getInstance().figureView.isPop)){
		_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_FIGURE));
		}
		if( !(ViewManager.getInstance().bagView && ViewManager.getInstance().bagView.isPop)){
		_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_BAG));
		}*/
		return;
	}
	else if(str == "open_bag")
	{
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_BAG, NULL);
		/*if( !(ViewManager.getInstance().bagView && ViewManager.getInstance().bagView.isPop)){
			_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_BAG));
		}*/
		return;
	}else if(str == "open_strength")
	{
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_STRENG, NULL);
		/*if( !(ViewManager.getInstance().mainStrengView && ViewManager.getInstance().mainStrengView.isPop)){
			_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_STRENG));
		}*/
		return;
	}else if(str == "open_recruit")
	{
		if (ViewManager::getInstance()->_scene
			&& ViewManager::getInstance()->_scene->getIsCanDialogPop(/*npcID*/6) )
		{
			GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_RECRUIT, NULL);
		}
		
		/*if( !(ViewManager.getInstance().recruitView && ViewManager.getInstance().recruitView.isPop)){
			_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_RECRUIT));
		}*/
		return;
	}else if(str == "open_formation")
	{
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_FORMATION, NULL);
		/*if( !(ViewManager.getInstance().formationView && ViewManager.getInstance().formationView.isPop)){
			_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_FORMATION));
		}*/
		return;
	}else if(str == "open_skill")
	{
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_UPSKILL, NULL);
		/*if( !(ViewManager.getInstance().skillView && ViewManager.getInstance().skillView.isPop)){
		_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_UPSKILL));
		}*/
		return;
	}else if(str == "open_crystal")
	{
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_CRYSTAL, NULL);
		/*if( !(ViewManager.getInstance().crystalView && ViewManager.getInstance().crystalView.isPop)){
			_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_CRYSTAL));
		}*/
		return;
	}
//	else if(str == "open_train")){
//		if( !(ViewManager.getInstance().trainView && ViewManager.getInstance().trainView.isPop)){
//			_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_TRAIN));
//		}
//		return;
//	}
	else if(str == "open_foster")
	{
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_FIGURE, NULL);
		/*if( !(ViewManager.getInstance().figureView && ViewManager.getInstance().figureView.isPop)){
		_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_FIGURE));
		}*/
		return;
	}else if(str == "open_impose")
	{
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_LEVY, NULL);
		/*if( !(ViewManager.getInstance().levyView && ViewManager.getInstance().levyView.isPop)){
		_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_LEVY));
		}*/
		return;
	}else if(str == "open_skill")
	{
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_FIGURE, NULL);
		/*if( !(ViewManager.getInstance().skillView && ViewManager.getInstance().skillView.isPop)){
			_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_FIGURE));
		}*/
		return;
	}else if(str == "open_vip")
	{
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_VIP, NULL);
		/*if( !(ViewManager.getInstance().vipView && ViewManager.getInstance().vipView.isPop)){
			_dispatcher.dispatchEvent(new ParamEvent(GameDispatcher.SHOW_UI_VIP));
		}*/
		return;
	}
	else if(str == "open_friend")
	{
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_FRIEND, NULL);
		/*if( !(ViewManager.getInstance().friendView && ViewManager.getInstance().friendView.isPop)){
		_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_FRIEND));
		}*/
		return;
	}
	else if(str == "open_dialy")
	{
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_DAILY, NULL);
		/*if( !(ViewManager.getInstance().dailyView && ViewManager.getInstance().dailyView.isPop)){
			_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_DAILY));
		}*/
		return;
	}
	else if(str == "open_arena")
	{
		//GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_ARENA, NULL);
		/*_dispatcher.dispatchEvent(new ParamEvent(GameDispatcher.SHOW_UI_ARENA));*/
		return;
	}
	else if(str == "open_farm")
	{
		//GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_RESOURCE_FIELD, NULL);
		/*_dispatcher.dispatchEvent(new ParamEvent(GameDispatcher.SHOW_RESOURCE_FIELD));*/
		return;
	}
	else if(str == "open_guild")
	{
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_GUILD, NULL);
		/*if(RoleManage::Instance()->accountInfo().guild){
			if( !(ViewManager.getInstance().guildView && ViewManager.getInstance().guildView.isPop)){
				_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_GUILD));
			}
		}
		else{
			if( !(ViewManager.getInstance().guildPreView && ViewManager.getInstance().guildPreView.isPop)){
				_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_GUILD));
			}
		}*/
		return;
	}
	else if(str == "open_task")
	{
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_TASK, NULL);
		/*if( !(ViewManager.getInstance().taskView && ViewManager.getInstance().taskView.isPop)){
		_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_TASK));
		}*/
		return;
	}
	
 	//任务寻路

	std::vector<int> valuelist;
	int comma_n = 0;
	do
	{
		int tmp = 0;
		comma_n = str.find( "," );
		if( -1 == comma_n )
		{
			tmp = atoi(str.substr(0, str.length()).c_str());
			valuelist.push_back( tmp );
			break;
		}
		tmp = atoi(str.substr( 0, comma_n ).c_str());
		str.erase( 0, comma_n+1 );
		valuelist.push_back( tmp );
	}
	while(true);

	if(valuelist.size() < 3)
		return;
	
	int type = valuelist[0];
	int sceneId = valuelist[1];
	int npcId = valuelist[2];
	
	FindVo findVo;
	findVo._type = type;
	findVo._sceneId = sceneId;
	findVo._npcId = npcId;

	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::FIND_ELEMENT, &findVo);
}

void TaskFollowMediator::showTaskFollowList( CCNode *pNode, void *data )
{
	/*if(!_pFollowView)
		return;

	_pFollowView->showTaskFollowLayer();*/
}

void TaskFollowMediator::dismissTaskFollowList( CCNode *pNode, void *data )
{
	/*if(!_pFollowView)
		return;

	_pFollowView->dismissTaskFollowLayer();*/
}
