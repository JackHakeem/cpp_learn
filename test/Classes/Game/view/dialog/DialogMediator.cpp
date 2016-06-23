#include "DialogMediator.h"
#include "manager/ViewManager.h"
#include "model/shop/vo/shopVo.h"
#include "model/shop/ShopManager.h"
#include "manager/PopEventName.h"
#include "util/TileUtil.h"
#include "../newhand/components/NewHandView.h"
#include "model/scene/SceneManager.h"
#include "model/player/RoleManage.h"
#include "model/scene/vo/SceneType.h"
#include "events/GameDispatcher.h"
#include "NewEAlert.h"
#include "manager/GlobalManage.h"

		///**
		// * Dialogue window display
		// * @param e
		// * 
		// */
		//private function showDialogue(e:ParamEvent):void{
		//	id = e.param.id;  
		//	ModuleLoaderManage.getInstance().load(ResourceName.DIALOG_PATH, LoadLevel.HIGH, dialogPop, id);
		//}
/**
* Dialog box open
*/	

DialogMediator::DialogMediator()
{
	id = 0;
	_state = 0;
	_dialogView = NULL;
	_sceneMediator = (SceneMediator*)g_pFacade->retrieveMediator(AppFacade_SCENE_MEDIATOR);
	_taskProxy = (TaskProxy *) g_pFacade->retrieveProxy(AppFacade_TASK_PROXY);
	GameDispatcher::getInstance()->addEventListener(PopEventName::SHOW_UI_DIALOGUE, this, callfuncND_selector(DialogMediator::showDialogue));
}

DialogMediator::~DialogMediator()
{

}

void DialogMediator::dialogPop( int npcId )
{
	//CCSize cs = CCDirector::sharedDirector()->getWinSizeInPixels();
	//_fightProxy->dungeonAward = DungeonAwardAction::DungeonAwardActionWithRect( 
	//	CCRectMake( cs.width/2-POSX(220/2), cs.height/2-POSX(260/2), POSX(220), POSX(260) )
	//	);
	//if ( LayerManager::sceneUILayer && _fightProxy->dungeonAward )
	//{
	//	SCMD376 s;
	//	memset( &s, 0, sizeof(s) );
	//	_fightProxy->dungeonAward->initDungeonAwardActionVo( s );
	//	LayerManager::sceneUILayer->addChild( _fightProxy->dungeonAward );
	//}

	//return;

	if (!_dialogView)
	{
		_dialogView = new DialogView();
		if(_sceneMediator)
		_sceneMediator->_scene->addEventListener(SceneConst::ROLE_POS_CHANGED, this, callfuncND_selector(DialogMediator::rolePosChangeHandler));
		ViewManager::getInstance()->dialogView = _dialogView;
		_dialogView->init();
	}

	if(!_dialogView->getisPop())
		createList(npcId);
}

void DialogMediator::createList( int npcId )
{
	NPCDialogueVo* _NPCDialogueVo = NULL;
	if (_dialogView)
	{
		_NPCDialogueVo = createNPCDialogueVo(npcId);
		if(_NPCDialogueVo)
			_dialogView->setData(_NPCDialogueVo);
	} 

	//showDialogue();
	_dialogView->setisPop(true);
	//NewHandView::Instance()->dialogPopTrigger(NULL);
	_dialogView->_autoPop = true;
	//_dispatcher.addEventListener(GameDispatcher.CAN_TASK_DATA_CHANGE, canTaskDataChangeHandler);

	GameDispatcher::getInstance()->addEventListener(GameDispatcher::CAN_TASK_DATA_CHANGE, this, callfuncND_selector(DialogMediator::newTaskToAutoPop));
	GameDispatcher::getInstance()->addEventListener(GameDispatcher::NEW_ALERT_CLOSE, this, callfuncND_selector(DialogMediator::newTaskToAutoPop));
	GameDispatcher::getInstance()->addEventListener(GameDispatcher::REC_TASK_DATA_CHANGE, this, callfuncND_selector(DialogMediator::recTaskDataChangeHandler));
}

NPCDialogueVo* DialogMediator::createNPCDialogueVo( int npcId )
{
	NPCDialogueVo* vo = new NPCDialogueVo();
	vo->npcId = npcId;
	vo->taskList = _taskProxy->getCanAndRecTasks(npcId);

	std::vector<TaskNodeVo *>::iterator iter = vo->taskList.begin();
	for (iter ; iter != vo->taskList.end() ; iter++)
	{
		CCLog("task id : %d" , (*iter)->_id);
		CCLog("task name : %s" ,(*iter)->_name.c_str());
		std::vector < DialogueNodeVo * >::iterator it = (*iter)->_list.begin();
		for (it ; it != (*iter)->_list.end() ; it++)
		{
			CCLog("text : %s" ,(*it)->_text.c_str());
		}
	}
	

	//Interactive dialog classification function
	ShopVo* shops  = ShopManager::Instance()->getShopsByNPCId( npcId );
	//var chatList:Array = [];
	//for each(var shopVo:ShopVo in shops){
	//	//Copies, nests open conditions: finish the appointed tasks, and configuration shopVo.otherinfos
	//	if(shopVo.type == DialogueType.ARMY || shopVo.type == DialogueType.COPY){
	//		var arr:Array = shopVo.otherinfos.split("|");
	//		if(arr.length>=2){
	//			var taskId:int = int(arr[1]);
	//			if(!_taskProxy.isTaskFinished(taskId)){
	//				continue;
	//			}
	//		}
	//	}//Judge all kinds of NPC function is open, with the united NewhandManager isOpenButton function judgment can
	//	else if(shopVo.type==DialogueType.RECRUIT && !NewhandManager.getInstance().isOpenButton(NewhandConst.ENABLE_RECRUIT)){
	//		continue;
	//	}
	//	else if(shopVo.type==DialogueType.APPOINT && !NewhandManager.getInstance().isOpenButton(NewhandConst.ENABLE_Appoint)){
	//		continue;
	//	}
	//	else if(shopVo.type==DialogueType.TRADER && !NewhandManager.getInstance().isOpenButton(NewhandConst.ENABLE_TRADER)){
	//		continue;
	//	}
	//	chatList.push(shopVo);
	//}
	vo->chatList.push_back( shops );

	return vo;
}

void DialogMediator::showDialogue(CCNode*n, void* data)
{
	//if(_dialogView)
	//	_dialogView->setisPop( true/*!_dialogView->getisPop()*/ );

	if(g_pGlobalManage->isInStory ||
		g_pGlobalManage->_isInFight)
	{
		return;
	}

	if(!data)
		return;

	id = *((int*)data);
	dialogPop(id);
}

void DialogMediator::rolePosChangeHandler(CCNode* n, void* data)
{
	if(!_sceneProxy)
		return;

	CCPoint rolePos = _sceneProxy->rolePos();
	NPCVo* npcVo = _sceneProxy->getClickNPC();
	if(npcVo == NULL)
		return;
	if((TileUtil::Instance()->changeXToPixs(npcVo->x) - rolePos.x)*
		(TileUtil::Instance()->changeXToPixs(npcVo->x) - rolePos.x)+
		(TileUtil::Instance()->changeYToPixs(npcVo->y) - rolePos.y)*
		(TileUtil::Instance()->changeYToPixs(npcVo->y) - rolePos.y) > 40000)
	{
		if(_dialogView)
		{
			_dialogView->setisPop(false);
			_dialogView->_npcId = 0;
			_dialogView->_autoPop = false;
		}
		GameDispatcher::getInstance()->removeEventListener(GameDispatcher::CAN_TASK_DATA_CHANGE);
		GameDispatcher::getInstance()->removeEventListener(GameDispatcher::NEW_ALERT_CLOSE);
		GameDispatcher::getInstance()->removeEventListener(GameDispatcher::REC_TASK_DATA_CHANGE);

		_sceneProxy->setClickNPC(0);
	}
}

void DialogMediator::newTaskToAutoPop(CCNode* n, void* data)
{
	/*if(ViewManager::_mainStrengView()->crystalView && ViewManager.getInstance().crystalView.isPop) return;*/
	tryAutoPopDialog();
}

void DialogMediator::tryAutoPopDialog()
{ 
	NewEAlert* oldTar = (NewEAlert*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_NewEAlert);
	if(_dialogView && _dialogView->_noStory && _dialogView->_autoPop && !oldTar){
		SceneVo *pSceneVo = SceneManager::Instance()->getSceneDic(RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId);
		if( pSceneVo->type == SceneType::CITY)
		{
			int npcId = _dialogView->npcId();
			std::vector<TaskVo *> canTaskList = _taskProxy->getCanTasks();

			std::vector<TaskVo *>::iterator it;
			for(it = canTaskList.begin(); it != canTaskList.end(); ++it)
			{
				TaskVo *pTask = *it;
				if(!pTask)
					continue;

				if((*pTask->_pNpcs.begin()) == npcId)
				{
					GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_DIALOGUE, &_dialogView->_npcId);
					break;
				}
			}
		}
	}
}

void DialogMediator::recTaskDataChangeHandler(CCNode* n, void* data)
{
	if(_dialogView && _dialogView->_noStory && _dialogView->_autoPop)
	{
		SceneVo *pSceneVo = SceneManager::Instance()->getSceneDic(RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId);
		if( pSceneVo->type == SceneType::CITY)
		{
			int npcId = _dialogView->npcId();
			std::vector<TaskVo *> recTaskList = *(std::vector<TaskVo *> *)data;

			std::vector<TaskVo *>::iterator it;
			for(it = recTaskList.begin(); it != recTaskList.end(); ++it)
			{
				TaskVo *pTask = *it;
				if(!pTask)
					continue;

				if(pTask->getFinishTaskNpc() == npcId)
				{
					GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_DIALOGUE, &_dialogView->_npcId);
				}
			}
		}
	}
}

bool DialogMediator::getIsPop()
{
	if(_dialogView)
		return _dialogView->getisPop();

	return false;
}

void DialogMediator::setAutoPop( bool isAutoPop )
{
	if(!_dialogView)
		return ;

	_dialogView->_noStory = isAutoPop;

	tryAutoPopDialog();
}


void DialogMediator::handleNotification( int M2Vcmd, char* data )
{
	switch(M2Vcmd)
	{
	case SET_AUTO_POP:
		setAutoPop(data != NULL);
		//CC_SAFE_DELETE(data);
		break;

	default:
		break;
	}
}
