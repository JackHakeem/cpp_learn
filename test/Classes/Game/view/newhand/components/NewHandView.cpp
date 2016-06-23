#include "NewHandView.h"
#include "model/player/RoleManage.h"
#include "model/newhand/vo/NewhandConst.h"
#include "manager/LayerManager.h"
#include "events/GameDispatcher.h"
#include "manager/PopManage.h"
#include "view/dialog/DialogMediator.h"
#include "utils/ScaleUtil.h"
#include "manager/PopEventName.h"
#include "view/task/TaskFollowMediator.h"
#include "NewHandHelpView.h"
#include "view/figure/components/FigureView.h"
#include "view/levy/LevyMediator.h"
#include "view/levy/components/GoldLevyPanel.h"
#include "view/arena/components/ArenaUI.h"
#include "view/ore/components/OreView.h"
#include "view/friend/components/FriendView.h"
#include "view/recruit/components/RecruitView.h"

NewHandView::NewHandView()
{
	//NewhandManager::Instance() = NewhandManager::Instance();
	_firstDlgScriptId = 0;
	_pViewManager = ViewManager::getInstance();
	_objectParentType = ObjectGlow::TYPE_1;
	_pNextScript = NULL;
	_pCurScript = NULL;
	_newhandTaskFollowId = 0;
	_newhandMainNavigateId = 0;
	GameDispatcher::getInstance()->addEventListener(PopContainer::CLOSE_CONTAINER,
		this,
		callfuncND_selector(NewHandView::sendPopCloseEvent));
	GameDispatcher::getInstance()->addEventListener(PopContainer::OPEN_CONTAINER,
		this,
		callfuncND_selector(NewHandView::sendPopOpenEvent));
	GameDispatcher::getInstance()->addEventListener(TaskFollowMediator::ON_TASK_FOLLOW_LIST_DISMISS,
		this,
		callfuncND_selector(NewHandView::onTaskFollowChange));
	GameDispatcher::getInstance()->addEventListener(TaskFollowMediator::ON_TASK_FOLLOW_LIST_SHOW,
		this,
		callfuncND_selector(NewHandView::onTaskFollowChange));
}

void NewHandView::testScript( CCNode *pNode, void *data )
{
	if(!pNode)

		return;

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
	Data *pData = static_cast<Data *>(data);//(Data *) data;

	if(!pData || !pData->pScript) return;

	// lh20120907
	int id = pData->pScript->id + 20000;
	if (!ViewManager::getInstance()->_helpView)
	{
		ViewManager::getInstance()->_helpView = new NewHandHelpView();
		GameDispatcher::getInstance()->addEventListener(GameDispatcher::RESET_NEWHELP_VIEW ,
			ViewManager::getInstance()->_helpView ,callfuncND_selector(NewHandHelpView::resetView));
	}
	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::RESET_NEWHELP_VIEW ,(void *)&id);

	_pCurScript = pData->pScript;
	NewhandManager::Instance()->_pCurScript = _pCurScript;
	/*var autoNext:Boolean = false;*/
	if(_pCurScript->clear > 0) 
	{
		clearArrowRectangle();
	}
	if(_pCurScript->clear > 1)
	{
		_firstDlgScriptId = 0;
	}

	if(pData->finished)
	{
		_firstDlgScriptId = 0;
		//if(_pop && _pop.key!=PopEventName.DIALOGUE){//ø…ÕÍ≥…»ŒŒÒ£¨∂® ±◊‘∂Øπÿ±’œ‡”¶µƒ√Ê∞Â
		//	_prePopKey = _pop.key;
		//	//TimerManage.getInstance().add(1401, autoClosePopContainer);
		//}
	} 

	CC_SAFE_DELETE(pData);

	if(_pCurScript->loc == "null")
	{
		//Ω· ¯Ãıº˛
		clearAll();
		return;
	} 
	//draw="11|10|18" -->> draw="arrow_dir|locType|typeId"
	int arrow_dir = _pCurScript->arrow;/*º˝Õ∑∑ΩœÚ*/
	int locType = _pCurScript->locType;/*Œª÷√±‡∫≈£¨œÍ«Èø¥NewhandConst.LOC_XXXX*/
	int typeId = _pCurScript->typeId;/*∂‘œÛid£¨∂‘”⁄»ŒŒÒ¿¥Àµ «»ŒŒÒid;∂‘”⁄∆‰À˚∂‘œÛ¿¥Àµ£¨”–Ãÿ∂®±‡∫≈£¨œÍ«Èø¥NewhandConst.ITEM_XXXX*/

	//int mapId = RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId;

	if(typeId != -1 && _pCurScript->trigger[0] != "canTask")
	{
		CCNode *pObject = getObject(locType, typeId, _pCurScript->loc);
		if(pObject){
			ObjectGlow *pGlow;
			if(locType == NewhandConst::LOC_TASK)
			{
				if(_pViewManager->taskFollowView)
				{
					_newhandTaskFollowId = _firstDlgScriptId = _pCurScript->id;
					/*GameDispatcher::getInstance()->addEventListener(TaskFollowMediator::ON_TASK_FOLLOW_LIST_DISMISS,
						this,
						callfuncND_selector(NewHandView::onTaskFollowChange));*/
					//_viewManager.taskFollowView.addEventListener(TaskFollowView.VISIBLE_CHANGE, onTaskFollowChange);
				}
			}
			else
			{
				if(_pViewManager->taskFollowView)
				{
					//GameDispatcher::getInstance()->removeEventListener(TaskFollowMediator::ON_TASK_FOLLOW_LIST_DISMISS);
					//_viewManager.taskFollowView.removeEventListener(TaskFollowView.VISIBLE_CHANGE, onTaskFollowChange);
				}
			}

			if(_pCurScript->loc == "map")
			{
				_objectParentType = ObjectGlow::TYPE_4;

				pGlow = new ObjectGlow(pObject, locType, NULL, arrow_dir,  _pCurScript->info, _pCurScript->isFlyEffect, CCPointZero);
				//LayerManager.newhandLayer.visible = mapId == _curScript.locId;
			}
			else if(_pCurScript->loc=="world")
			{
				if(_pViewManager->worldScene)
				{
					_objectParentType = ObjectGlow::TYPE_1;
					pGlow = new ObjectGlow(pObject, locType, _pViewManager->worldScene, arrow_dir,  _pCurScript->info, _pCurScript->isFlyEffect, CCPointZero);
				}
			}
			else if(_pCurScript->loc=="PASSIVE")
			{
				/*if(_pViewManager->passiveView){
					glow = new ObjectGlow(pObject, locType, view, arrow_dir,  _pCurScript->info, _pCurScript->isFlyEffect, _objectParentType);
				}*/
			}
			else if(_pCurScript->loc=="WIN")
			{
				/*CCNode *pParentNode = NewhandConst::Instance()->getItem(NewhandConst::ITEM_COM_WIN);
				if(pParentNode)
				{*/
					pGlow = new ObjectGlow(pObject, locType, NULL, arrow_dir,  _pCurScript->info, _pCurScript->isFlyEffect, CCPointZero);
				//}
			}
			else
			{
				// 20120703
				// Doyang.
				// cancel the cantask tips.
				pGlow = new ObjectGlow(pObject, locType, NULL, arrow_dir,  _pCurScript->info, _pCurScript->isFlyEffect, CCPointZero);

		//		var panel:PopContainer = PopManage.getInstance().getPopViewByName(_curScript.loc);
		//if(panel){
		//			glow = new ObjectGlow(ob, locType, panel, arrow_dir, _curScript.info);
		//			//∑Á÷ÆÀÆæßµ»£¨◊‘∂Ø—°‘Ò
		//			if(ob.name.search("_iconCy") != -1){
		//				(ob as MovieClip).dispatchEvent(new MouseEvent(MouseEvent.CLICK));
		//			}
		//		}
			}
			_paintArr.push_back(pGlow);
		}
	}

	////œ¬“ª≤Ω
	_pNextScript = NewhandManager::Instance()->getNewhandScript(_pCurScript->next_id);
	NewhandManager::Instance()->_pNextScript = _pNextScript;
	if(!_pNextScript) 
	{
		return;
	}
	
	/*if(autoNext) {
	testScript(_nextScript);
	return;
	}*/
	
	nextScriptTriggerHandle(_pNextScript->trigger[0]);
}

void NewHandView::nextScriptTriggerHandle( string trigger )
{
	string popName;
	if(trigger == "dlgNext")
	{
		/*var dlg:PopContainer = PopManage.getInstance().getPopViewByName("DIALOGUE");
		if(dlg){
			dlg.addEventListener(DialogView.DRAW_OPITEM, dlgNextTrigger);
		}*/
		this->dlgNextTrigger();
	}
	else if(trigger == "p")
	{
		if(_firstDlgScriptId == 0) 
		{
			_newhandMainNavigateId = _firstDlgScriptId = _pCurScript->id;
		}
		popName = _pNextScript->trigger[1];
		//_pop = PopManage.getInstance().getPopViewByName(popName);
		if(g_pPopManage->getCurPopNum() > 0)
		{
			//¥∞ø⁄“—æ≠¥Úø™¡À
			this->addEventListener(PopContainer::CLOSE_CONTAINER,
				this,
				callfuncND_selector(NewHandView::popCloseTrigger));
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
			data->pScript = _pNextScript;
			data->finished = false;
			testScript(this, data);
		}
		else
		{
			if(popName == "DIALOGUE")
			{
				GameDispatcher::getInstance()->addEventListener(PopEventName::DIALOGUE,
					this,
					callfuncND_selector(NewHandView::dialogPopTrigger));
			}
			else
			{
				this->addEventListener(PopContainer::OPEN_CONTAINER,
					this,
					callfuncND_selector(NewHandView::viewPopTrigger));
			}
		}
	}
	else if(trigger == "c")
	{
		popName = _pNextScript->trigger[1];
		
		this->addEventListener(PopContainer::CLOSE_CONTAINER,
			this,
			callfuncND_selector(NewHandView::popCloseTrigger));
	}
	else if(trigger == "imd")
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
		data->pScript = _pNextScript;
		data->finished = false;
		testScript(this, data);
	}
	else if(trigger == "world")
	{
		int targetMap = atoi(_pNextScript->trigger[1].c_str());/*æ≠π˝ ¿ΩÁ◊Ó÷’“™µΩ¥ÔµƒµÿÕº*/
		int mapId = RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId;
		if(mapId == targetMap)
		{
			ScriptVo *pNextScript = NewhandManager::Instance()->getMapScriptById(_pNextScript->next_id, targetMap);
			if(pNextScript)
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
				data->pScript = pNextScript;
				data->finished = false;
				testScript(this, data);
				return;
			}
		}
		_firstDlgScriptId = _pCurScript->id;
	}
	else if(trigger == "evt")
	{
		//NewhandManager::Instance()->_nextEventId = atoi(_pNextScript->trigger[1].c_str());

		int evtId = atoi(_pNextScript->trigger[1].c_str());
		std::list<int> evtIDList = NewhandManager::Instance()->_nextEventIdList;
		std::list<int>::iterator iter = evtIDList.begin();
		bool isExist = false;
		for (iter ; iter != evtIDList.end() ; iter++)
		{
			if (evtId == *iter)
			{
				isExist = true;
				break;
			}
		}
		if (!isExist)
		{
			NewhandManager::Instance()->_nextEventIdList.push_back(atoi(_pNextScript->trigger[1].c_str())) ;
		}
	}
}

void NewHandView::onTaskFollowChange(CCNode *pNode, void *data)
{
	// 20120611
	// Doyang, when dismiss taskFollowList, clear tips.

	// 20120706
	if(ViewManager::getInstance()->taskFollowView && ViewManager::getInstance()->taskFollowView->_isTaskListViewShowing)
	{
		// show
		if(_firstDlgScriptId!=0 && _firstDlgScriptId == _newhandTaskFollowId)
		{
			clearArrowRectangle();
			_pNextScript = NewhandManager::Instance()->getNewhandScript(_firstDlgScriptId);
			/*if(_pNextScript
			|| _pNextScript->trigger.size() < 2
			|| _pNextScript->trigger[1] == "DIALOGUE")
			{
			return;
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
			Data *sData = new Data();
			sData->pScript = _pNextScript;
			sData->finished = false;
			testScript(this, sData);
		}
	}
	else
	{
		// dismiss
		if(_firstDlgScriptId != _newhandMainNavigateId)
		{
			clearArrowRectangle();
		}
	}
}

void NewHandView::popCloseTrigger(CCNode *pNode, void *data)
{
	this->removeEventListener(PopContainer::CLOSE_CONTAINER);
	DialogMediator* pDialogMediator = (DialogMediator*)g_pFacade->retrieveMediator(AppFacade_NPCDIALOGUE_PROXY_CHANGE);
	if(!_pNextScript) 
	{
		return;
	}
	if(_pNextScript->trigger[0] == "c")
	{
		/* πÿ±’¥∞ø⁄¥•∑¢ */
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
		data->pScript = _pNextScript;
		data->finished = false;
		testScript(this, data);
		/* œ¬“ª≤Ω“ª∞„∂º «÷ª◊ˆ«Â≥˝ */
	}
	else if(pDialogMediator->getIsPop() 
		&& (_pNextScript->trigger[0] == "dlgNext"
		|| _pNextScript->trigger[0] == "rcvTask"
		|| _pNextScript->trigger[0] == "smtTask"))
	{
		clearArrowRectangle();
		_pCurScript = NULL;
		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::TASK_AUTO_REC_OR_SMT, 
			&_pNextScript->taskId);
	}
	else
	{
		//≤ª∞¥’’“˝µºπÿ±’(9.15◊¢£∫”–ø…ƒ‹ «¥Úø™∆‰À˚¥∞ø⁄µº÷¬±æ¥∞ø⁄πÿ±’£¨µ´ «»Áπ˚¥Úø™¥∞ø⁄ «‘§¡œ÷–£¨clear=2)
		clearArrowRectangle();
		_pCurScript = NULL;
		if(_firstDlgScriptId != 0)
		{
			_pNextScript = NewhandManager::Instance()->getNewhandScript(_firstDlgScriptId);
			_firstDlgScriptId = 0;
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
			data->pScript = _pNextScript;
			data->finished = false;
			testScript(this, data);
		}
	}
}

/**
* Each NPC dialog.
* 
*/		
void NewHandView::dlgNextTrigger()
{
	/*e.target.removeEventListener(DialogView.DRAW_OPITEM, dlgNextTrigger);*/
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
	data->pScript = _pNextScript;
	data->finished = false;
	testScript(this, data);
}

void NewHandView::dialogPopTrigger(CCNode *pNode, void *data)
{
	/*if(!data)
	return;*/


	/*TestNewhand *pData = (TestNewhand *) data;
	if(!pData)
		return;*/

	GameDispatcher::getInstance()->removeEventListener(PopEventName::DIALOGUE);

	this->addEventListener(PopContainer::CLOSE_CONTAINER,
		this,
		callfuncND_selector(NewHandView::popCloseTrigger));
	/*var dlg:DialogView = PopManage.getInstance().getPopViewByName("DIALOGUE") as DialogView;
	if(dlg){
		var npcId:int = dlg.npcId;
		if(_nextScript.trigger.length<3 || int(_nextScript.trigger[2])!= npcId) return;
		_dispatcher.removeEventListener(PopEventName["DIALOGUE"],dialogPopTrigger);
		dlg.addEventListener(PopContainer.CLOSE_CONTAINER, popCloseTrigger);
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
	Data *sData = new Data();
	sData->pScript = _pNextScript;
	sData->finished = false;

	testScript(this, sData);
}

void NewHandView::clearArrowRectangle()
{
	std::list<ObjectGlow *>::iterator it;
	for(it = _paintArr.begin(); it != _paintArr.end(); ++ it)
	{
		ObjectGlow *pGlow = (ObjectGlow *) *it;
		if(pGlow)
		{
			pGlow->stopAndClear();
		}
        CC_SAFE_DELETE(pGlow);
	}
	_paintArr.clear();
}

void NewHandView::clearAll()
{

	GameDispatcher::getInstance()->removeEventListener(PopEventName::DIALOGUE);

	_pCurScript = NULL;
	_pNextScript = NULL;
	_firstDlgScriptId = 0;
	//_evtName = "";
	NewhandManager::Instance()->_pCurScript = NULL;
	NewhandManager::Instance()->_pNextScript = NULL;
}

void NewHandView::eventTrigger( TestNewhand *pData )
{
	if(!_pCurScript || !_pNextScript) return;
	bool diff = _pNextScript->trigger[0] != pData->type;

	if(pData->type == "rcvTask" || pData->type == "smtTask")
	{
		this->removeEventListener(PopContainer::CLOSE_CONTAINER);
		if(diff)return;
		if(pData->id == atoi(_pNextScript->trigger[1].c_str()))
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
			data->pScript = _pNextScript;
			data->finished = false;
			testScript(this, data);
		}
	}
	else if(pData->type == "child")
	{
		if(diff)return;
		if(pData->id == atoi(_pNextScript->trigger[1].c_str()))
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
			data->pScript = _pNextScript;
			data->finished = false;
			testScript(this, data);
		}
	}
	else if(pData->type == "map")
	{
		int mapId = RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId;
		if(!diff && mapId == atoi(_pNextScript->trigger[1].c_str()))
		{
			//LayerManager::newhandLayer.setIsVisible(true);
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
			data->pScript = _pNextScript;
			data->finished = false;
			testScript(this, data);
		}
		else if(_pCurScript->locId == 0)
		{
			/* »Áπ˚–¬ ÷“˝µº’˝‘⁄world,»¥Ã¯◊™¡ÀµÿÕº£¨÷ÿ÷√ */
			clearArrowRectangle();
			_pCurScript = NULL;
			_pNextScript = NewhandManager::Instance()->getNewhandScript(_firstDlgScriptId);
			_firstDlgScriptId = 0;
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
			data->pScript = _pNextScript;
			data->finished = false;
			testScript(this, data);
		}
		//LayerManager.newhandLayer.visible = mapId == int(_curScript.locId);
	}
	else if(pData->type == "world")
	{
		if(diff && _pCurScript)
		{
			//LayerManager.newhandLayer.visible = 0 == int(_curScript.locId);
		}
		else{
			//LayerManager.newhandLayer.visible = true;
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
			data->pScript = _pNextScript;
			data->finished = false;
			testScript(this, data);
		}
	}
	else if(pData->type == "evt")
	{
		if(!diff && pData->id== atoi(_pNextScript->trigger[1].c_str()))
		{
			NewhandManager::Instance()->_pNextScript = NULL;
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
			data->pScript = _pNextScript;
			data->finished = false;
			testScript(this, data);
		}
	}
	else if(pData->type == "p")
	{
		if(1/*!diff *//*&& pData->id== atoi(_pNextScript->trigger[1].c_str())*/)
		{
			NewhandManager::Instance()->_pNextScript = NULL;
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
			data->pScript = pData->pScript/*_pNextScript*/;
			data->finished = false;
			testScript(this, data);
		}
	}
}

CCNode * NewHandView::getObject( int loc_type, int id, string viewName )
{
	if(!_pViewManager)
		_pViewManager = ViewManager::getInstance();

	switch(loc_type){
	case NewhandConst::LOC_TASK://»ŒŒÒ◊∑◊Ÿ
		{
			_objectParentType = ObjectGlow::TYPE_1;

			/*
			if(_pViewManager->taskFollowView)
			{
				// Equals _ob is CustomTabBar
				//// Show taskFollowView list.
				//GameDispatcher::getInstance()->dispatchEvent(TaskFollowMediator::SHOW_TASK_FOLLOW_LIST, NULL);
				_newhandTaskFollowId = _pCurScript->id;
				_pViewManager->taskFollowView->showTaskFollowLayer();
				return _pViewManager->taskFollowView->getNewHandItem(id);
			}
			*/
			if (_pViewManager->_taskUIView)
			{
				_newhandTaskFollowId = _pCurScript->id;
				return _pViewManager->_taskUIView->getNewHandItem(id);
			}
		}
		break;

	case NewhandConst::LOC_MAIN:
		{
			if(_pViewManager->mainNavigate)
			{
				_newhandMainNavigateId = _pCurScript->id;
				_pViewManager->mainNavigate->setisMainBtnOpen(true);
				return _pViewManager->mainNavigate->getNewHandItem(id);
			}
		}
		break;

	case NewhandConst::LOC_CD:
		{

			//if( _pViewManager->cdList )
			//{
			//	return _pViewManager->cdList->getNewHandItem(id);
			//}
		}
		break;

	case NewhandConst::LOC_SEC:
		{
			if(_pViewManager->_secNavigate)
			{
				return _pViewManager->_secNavigate->getNewHandItem(id);
			}
		}
		break;

	case NewhandConst::LOC_MAP:
		{
			if(_pViewManager->smallMapUI)
			{
				return _pViewManager->smallMapUI->getNewHandItem(id);
			}
		}
		break;

	case NewhandConst::LOC_WORLD:
		{
			if(_pViewManager->worldScene)
			{
				return _pViewManager->worldScene->getNewHandItem(id, true);
			}
		}
		break;

	case NewhandConst::LOC_CHILD:
		{
			if(_pViewManager->worldScene)
			{
				return _pViewManager->worldScene->getNewHandItem(id, false);
			}
		}
		break;

	case NewhandConst::LOC_VSCROLL:
		{
			_newhandMainNavigateId = _pCurScript->id;
			if (ViewManager::getInstance()->_pVScrollUI)
			{
				if (ViewManager::getInstance()->_pVScrollUI->getIsHide())
				{
					ViewManager::getInstance()->_pVScrollUI->clickHideVscroll();
				}
			}
			//_pViewManager->mainNavigate->setisMainBtnOpen(true);
			//_pViewManager->mainNavigate->setisMainBtnOpen(false);
			//onMainNavigateChange(true);
			return _pViewManager->mainNavigate->getNewHandItem(id);
		}
		break;

	case NewhandConst::LOC_POP:
		{
			if(viewName == "DIALOGUE")
			{
				if(_pViewManager->dialogView)
				{
					return _pViewManager->dialogView->getNewHandItem(id);
				}
			}
			else if (viewName == "BAG")
			{
				BagView* bagview = (BagView*)LayerManager::windowLayer->getChildByTag(PopEventName::BAG);
				if (bagview)
					bagview->getNewHandItem(id);
	/*			if(_pViewManager->bagView)
				{
					return _pViewManager->bagView->getNewHandItem(id);
				}*/
			}
			else if (viewName == "STRENG")
			{
				
				if(ViewManager::getInstance()->dialogView
					&& ViewManager::getInstance()->dialogView->getisPop())
				{
					return 0;
				}
				else
				{
					if(_pViewManager->_mainStrengView)
					{
						return _pViewManager->_mainStrengView->getNewHandItem(id);
					}
				}				
			}
			else if (viewName == "TRAIN")
			{
				if(_pViewManager->trainView)
				{
					return _pViewManager->trainView->getNewHandItem(id);
				}
			}
			else if (viewName == "FIGURE")
			{
				if(_pViewManager->figureView 
					&& _pViewManager->figureView->_figureV 
					&& _pViewManager->figureView->getisPop())
				{
					return _pViewManager->figureView->_figureV->getNewHandItem(id);
				}
			}
			else if (viewName == "FORMATION")
			{
				if(_pViewManager->formationView
					&& _pViewManager->formationView->getisPop())
				{
					return _pViewManager->formationView->getNewHandItem(id);
				}
			}
			else if (viewName == "CRYSTAL")
			{
				if(_pViewManager->crystalView
					&& _pViewManager->crystalView->getisPop())
				{
					return _pViewManager->crystalView->getNewHandItem(id);
				}
			}
			else if (viewName == "LEVY")
			{
				if(_pViewManager->levyView
					&& _pViewManager->levyView->getisPop())
				{
					return _pViewManager->levyView->getNewHandItem(id);
				}
			}
			else if (viewName == "GOLDLEVY")
			{
				if(_pViewManager->levyView
					&& _pViewManager->levyView->getisPop()
					&& g_pLevyMediator
					&& g_pLevyMediator->_goldPanel
					&& ((GoldLevyPanel *)(g_pLevyMediator->_goldPanel))->getIsVisible())
				{
					return _pViewManager->levyView->getNewHandItem(id);
				}
			}
			else if (viewName == "CHALLEGECOPY")
			{
				if(_pViewManager->dungeonEntrysView
					&& _pViewManager->dungeonEntrysView->getisPop())
				{
					return _pViewManager->dungeonEntrysView->getNewHandItem(id);
				}
			}
			else if (viewName == "TAOFA")
			{
				if(_pViewManager->dungeonEntrysView
					&& _pViewManager->dungeonEntrysView->getisPop())
				{
					return _pViewManager->dungeonEntrysView->getNewHandItem(id);
				}
			}
			else if (viewName == "ORE")
			{
				if(_pViewManager->oreView
					&& ((OreView *)(_pViewManager->oreView))->getisPop())
				{
					return ((OreView *)_pViewManager->oreView)->getNewHandItem(id);
				}
			}
			else if (viewName == "ARENA")
			{
				if(_pViewManager->arenaUI
					&& ((ArenaUI *)(_pViewManager->arenaUI))->getisPop())
				{
					return _pViewManager->arenaUI->getNewHandItem(id);
				}
			}
			else if (viewName == "FRIEND")
			{
				if(_pViewManager->friendView
					&& ((FriendView *)(_pViewManager->friendView))->getisPop())
				{
					return _pViewManager->friendView->getNewHandItem(id);
				}
			}
			else if (viewName == "UPSKILL")
			{
				if(_pViewManager->_upSkillView
					&& _pViewManager->_upSkillView->getisPop())
				{
					return _pViewManager->_upSkillView->getNewHandItem(id);
				}
			}
			else if (viewName == "RECRUIT")
			{
				if(_pViewManager->recruitView
					&& ((RecruitView *)(_pViewManager->recruitView))->getisPop())
				{
					return _pViewManager->recruitView->getNewHandItem(id);
				}
			}
			else if (viewName == "PEIYANG")
			{
				if(_pViewManager->figureView 
					&& _pViewManager->figureView->_figureV 
					&& _pViewManager->figureView->getisPop())
				{
					return _pViewManager->figureView->_figureV->getNewHandItem(id);
				}
			}
			else
			{
				return NewhandConst::Instance()->getItem(id);
			}
		}		
		break;
	default:
		break;
	}
	return NULL;
}

void NewHandView::autoClosePopContainer()
{
	/*TimerManage.getInstance().remove(autoClosePopContainer);
	var pop:PopContainer = PopManage.getInstance().getPopViewByKey(_prePopKey);
	if(pop){
		pop.removeEventListener(PopContainer.CLOSE_CONTAINER, popCloseTrigger);
		_dispatcher.dispatchEvent(new ParamEvent(PopEventName.EventName + _prePopKey.toString()));
		pop = null;
		_prePopKey = 0;
	}*/
}

void NewHandView::sendPopCloseEvent( CCNode *pNode, void *data )
{
	this->addEventListener(PopContainer::CLOSE_CONTAINER, 
		this,
		callfuncND_selector(NewHandView::popCloseTrigger));
	this->dispatchEvent(PopContainer::CLOSE_CONTAINER, NULL);
}

void NewHandView::sendPopOpenEvent( CCNode *pNode, void *data )
{
	this->dispatchEvent(PopContainer::OPEN_CONTAINER, NULL);
}

void NewHandView::viewPopTrigger( CCNode *pNode, void *data )
{
	this->addEventListener(PopContainer::CLOSE_CONTAINER, 
		this,
		callfuncND_selector(NewHandView::popCloseTrigger));

	this->removeEventListener(PopContainer::OPEN_CONTAINER);

	if(_pNextScript)
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
		data->pScript = _pNextScript;
		data->finished = false;
		testScript(this, data);
	}
}

void NewHandView::onMainNavigateChange( bool isShow )
{
	if(isShow)
	{
		if ((_firstDlgScriptId!=0 && _firstDlgScriptId == _newhandMainNavigateId)
			|| ( _pCurScript && _pCurScript->arrow == 15)
			/*|| (NewhandManager::Instance()->getNavigateType() == NewhandManager::Navigate_LeftVscroll)*/ )
		{
			clearArrowRectangle();
			_pNextScript = NewhandManager::Instance()->getNewhandScript(_firstDlgScriptId);
			/*if(_pNextScript
			|| _pNextScript->trigger.size() < 2
			|| _pNextScript->trigger[1] == "DIALOGUE")
			{
			return;
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
			Data *sData = new Data();
			sData->pScript = _pNextScript;
			sData->finished = false;
			testScript(this, sData);
		}
	}
	else
	{
		if ((_newhandTaskFollowId != _firstDlgScriptId)
			|| ( _pCurScript && _pCurScript->arrow == 15))
		{
			clearArrowRectangle();
		}
	}
}
