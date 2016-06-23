#include "TaskMediator.h"
#include "manager/ViewManager.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "manager/LayerManager.h"
#include "manager/GlobalManage.h"
#include "utils/ScaleUtil.h"
#include "components/TaskUtil.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "model/player/RoleManage.h"

// Task panel open
void TaskMediator::openTaskView()
{
	if(!_pTaskView)
	{
		cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
		_pTaskView = TaskView::initWithRect(CCRectMake(0, 0, POSX(960), POSX(640)));

		_pTaskView->initCanTree(_pTaskProxy->_canTaskList);
		_pTaskView->initReceivedTree(_pTaskProxy->_receivedTaskList);
		openTaskHandler();
		create();
		_pTaskView->addEventListener(TaskUtil::FIND_ELEMENT, _pTaskView, callfuncND_selector(TaskMediator::findElement));
		/*_taskView.updateEntrFinishNum(_taskProxy.weekTopLev, _taskProxy.finishEntrustNum, _taskProxy.entrustLim);*/

		//ViewManager::getInstance()->taskView = _pTaskView;
	}
	else
	{
		openTaskHandler();
	}
	_pTaskView->refresh();
}

void TaskMediator::openTaskHandler()
{
	//_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_INCREASE_PRICE,1);
	if(_pTaskView->getisPop())
	{
		_pTaskView->setisPop(false);
		/*_pTaskView->removeFromParentAndCleanup(true);
		_pTaskView = 0;*/
		//g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID());
	}
	else
	{
		_pTaskView->setisPop(true);
 		//_pTaskView->release();
		//g_pGlobalManage->setCurFocusGID(LayerManager::windowLayer->getMyFocusGID());
	}
	//_pTaskView->setisPop(!_pTaskView->getisPop());

	//Open before they decide whether you have opened entrust task

	//if(_taskView.isPop && NewhandManager.getInstance().isOpenButton(73)){
	//	_taskView.openWeiTuoTask();
	//}
}

// Create data content
void TaskMediator::create()
{
	/*if(_taskView){
	var canDic:Dictionary = _taskProxy.getCanTasks();
	var recDic:Dictionary = _taskProxy.getAllRecTask();
	var entrDic:Dictionary = _taskProxy.getAllEntrustTask();

	layoutEntrustData(entrDic);
	layoutCanData(canDic);
	layoutRecData(recDic);
	}*/
	if(_pTaskView && _pTaskProxy)
	{
		layoutRecData(_pTaskProxy->_receivedTaskList);
	}
}

TaskMediator::TaskMediator():_pTaskView(0),_pTaskProxy(0)
{
	_pTaskProxy = (TaskProxy *)g_pFacade->retrieveProxy(AppFacade_TASK_PROXY);
}

TaskMediator::~TaskMediator()
{

}

void TaskMediator::layoutCanData( std::vector<TaskVo *> &taskList )
{
	if(_pTaskView)
	{
		_pTaskView->initCanTree(taskList);
		_pTaskView->refresh();
	}

	if (ViewManager::getInstance()->_taskUIView)
	{
		ViewManager::getInstance()->_taskUIView->_canTaskList = taskList;
		ViewManager::getInstance()->_taskUIView->resetScrollView();
	}
	
}

void TaskMediator::handleNotification( int M2Vcmd, char* data )
{
	switch(M2Vcmd)
	{
	case TASK_VIEW_POP:
		openTaskView();
		break;

	default:
		break;
	}
}

void TaskMediator::layoutRecData( std::vector<TaskVo *> &taskList )
{
	if(_pTaskView)
	{
		_pTaskView->initReceivedTree(taskList);
		//Doyang 20120710
		//_pTaskView->refresh();
	}
}

void TaskMediator::findElement( CCNode *pNode, void *data )
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
		int a = 0;
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_FIGURE, &a);
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_BAG, &a);
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
		int a = 0;
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_BAG, &a);
		/*if( !(ViewManager.getInstance().bagView && ViewManager.getInstance().bagView.isPop)){
			_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_BAG));
		}*/
		return;
	}else if(str == "open_strength")
	{
		int a = 0;
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_STRENG, &a);
		/*if( !(ViewManager.getInstance().mainStrengView && ViewManager.getInstance().mainStrengView.isPop)){
			_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_STRENG));
		}*/
		return;
	}else if(str == "open_recruit")
	{
		int a = 0;
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_RECRUIT, &a);
		/*if( !(ViewManager.getInstance().recruitView && ViewManager.getInstance().recruitView.isPop)){
			_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_RECRUIT));
		}*/
		return;
	}else if(str == "open_formation")
	{
		int a = 0;
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_FORMATION, &a);
		/*if( !(ViewManager.getInstance().formationView && ViewManager.getInstance().formationView.isPop)){
			_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_FORMATION));
		}*/
		return;
	}else if(str == "open_skill")
	{
		int a = 0;
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_UPSKILL, &a);
		/*if( !(ViewManager.getInstance().skillView && ViewManager.getInstance().skillView.isPop)){
		_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_UPSKILL));
		}*/
		return;
	}else if(str == "open_crystal")
	{
		int a = 0;
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_CRYSTAL, &a);
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
		int a = 0;
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_FIGURE, &a);
		/*if( !(ViewManager.getInstance().figureView && ViewManager.getInstance().figureView.isPop)){
		_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_FIGURE));
		}*/
		return;
	}else if(str == "open_impose")
	{
		int a = 0;
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_LEVY, &a);
		/*if( !(ViewManager.getInstance().levyView && ViewManager.getInstance().levyView.isPop)){
		_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_LEVY));
		}*/
		return;
	}else if(str == "open_skill")
	{
		int a = 0;
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_FIGURE, &a);
		/*if( !(ViewManager.getInstance().skillView && ViewManager.getInstance().skillView.isPop)){
			_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_FIGURE));
		}*/
		return;
	}else if(str == "open_vip")
	{
		int a = 0;
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_VIP, &a);
		/*if( !(ViewManager.getInstance().vipView && ViewManager.getInstance().vipView.isPop)){
			_dispatcher.dispatchEvent(new ParamEvent(GameDispatcher.SHOW_UI_VIP));
		}*/
		return;
	}
	else if(str == "open_friend")
	{
		int a = 0;
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_FRIEND, &a);
		/*if( !(ViewManager.getInstance().friendView && ViewManager.getInstance().friendView.isPop)){
		_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_FRIEND));
		}*/
		return;
	}
	else if(str == "open_dialy")
	{
		int a = 0;
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_DAILY, &a);
		/*if( !(ViewManager.getInstance().dailyView && ViewManager.getInstance().dailyView.isPop)){
			_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_DAILY));
		}*/
		return;
	}
	else if(str == "open_arena")
	{
		int a = 0;
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_ARENA, &a);
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
		int a = 0;
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_GUILD, &a);
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
		int a = 0;
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_TASK, &a);
		/*if( !(ViewManager.getInstance().taskView && ViewManager.getInstance().taskView.isPop)){
		_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_TASK));
		}*/
		return;
	}
	
 	//ÈÎÎñÑ°Â·

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


