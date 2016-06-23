#include "NewhandManager.h"
#include "events/GameDispatcher.h"
#include "vo/TestNewhand.h"
#include "vo/HelpScriptVo.h"
#include "manager/ViewManager.h"
#include "manager/LevLimitConst.h"
#include "view/task/components/TaskScrollView.h"

NewhandManager::NewhandManager()
{
	_pInfoVo = 0 ;
	_deltaAttacPoint = 0;
	_isGetEquipment = false;
	_isNewAcount = false;
	_nextEventId = 0;

	_rcvTaskStepDic.clear();
	_smtTaskStepDic.clear();
	_levStepDic.clear();
	_fightLeadDic.clear();

	_pCurScript = 0;
	_pNextScript = 0;

	_navigateType = Navigate_BottomMain;

	createImagePathMap();
	initNewHandStateMap();
}

void NewhandManager::setNavigateType(int type)
{
	_navigateType = type;
}

int NewhandManager::getNavigateType()
{
	return _navigateType;
}

void NewhandManager::initNewhandStep()
{

} 

FightLeaderVo *NewhandManager::getFightLeadInfo( int map, int progress )
{
	std::map<int, FightLeaderVo *>::iterator it = _fightLeadDic.find(progress);

	if(it != _fightLeadDic.end())
	{
		FightLeaderVo *pFightLeader = it->second;
		return pFightLeader;
	}
	return NULL;
}

bool NewhandManager::addStep( StepVo *pStep )
{
	if(!pStep)
	{
		return false;
	}
	int id = atoi(pStep->trigger[1].c_str());
	pStep->id = id;
	if(pStep->trigger[0] == "smtTask")
	{
		std::map<int, std::list<StepVo *> >::iterator it = _smtTaskStepDic.find(id);
		
		if(it == _smtTaskStepDic.end())
		{
			std::list<StepVo *> smtTaskList;
			smtTaskList.push_back(pStep);
			_smtTaskStepDic.insert(make_pair(id, smtTaskList));
		}
		else
		{
			it->second.push_back(pStep);
		}
	}
	else if(pStep->trigger[0] == "rcvTask")
	{
		std::map<int, std::list<StepVo *> >::iterator it = _rcvTaskStepDic.find(id);
		
		if(it == _rcvTaskStepDic.end())
		{
			std::list<StepVo *> rcvTaskList;
			rcvTaskList.push_back(pStep);
			_rcvTaskStepDic.insert(make_pair(id, rcvTaskList));
		}
		else
		{
			it->second.push_back(pStep);
		}
	}
	else if(pStep->trigger[0] == "lev")
	{
		std::map<int, std::list<StepVo *> >::iterator it = _levStepDic.find(id);
		std::list<StepVo *> levTaskList;
		if(it == _levStepDic.end())
		{
			levTaskList.push_back(pStep);
			_levStepDic.insert(make_pair(id, levTaskList));
		}
		else
		{
			it->second.push_back(pStep);
		}
	}
	else
	{
		int iiii = 0;
		iiii = 1;
	}
	return true;
}

bool NewhandManager::addFightLead( FightLeaderVo *pFightLeader )
{
	if(!pFightLeader)
	{
		return false;
	}

	_fightLeadDic.insert(make_pair(pFightLeader->progress, pFightLeader));

	return true;
}

std::list<StepVo *> NewhandManager::getRcvTaskStepVo( int taskId )
{

	std::list<StepVo *> rcvList;
	std::map<int, std::list<StepVo *> >::iterator it = _rcvTaskStepDic.find(taskId);
	if(it != _rcvTaskStepDic.end())
	{
		rcvList = it->second;
		std::list<StepVo *>::iterator stepIt;

		for(stepIt = rcvList.begin(); stepIt != rcvList.end(); ++ stepIt)
		{
			StepVo *pStep = *stepIt;
			_isOpenDic[pStep->btnId] = 1;
		}
		_rcvTaskStepDic.erase(it);
	}
   return rcvList;

}

std::list<StepVo *> NewhandManager::getSmtTaskStepVo( int taskId )
{

	std::list<StepVo *> smtList;
	std::map<int, std::list<StepVo *> >::iterator it = _smtTaskStepDic.find(taskId);
	if(it != _smtTaskStepDic.end())
	{
		smtList = it->second;
		std::list<StepVo *>::iterator stepIt;

		for(stepIt = smtList.begin(); stepIt != smtList.end(); ++ stepIt)
		{
			StepVo *pStep = *stepIt;
			_isOpenDic[pStep->btnId] = 1;
		}
		_smtTaskStepDic.erase(it);
	}
	return smtList;

}

std::list<StepVo *> NewhandManager::getLevelStepVo( int lev )
{

	std::list<StepVo *> levList;
	std::map<int, std::list<StepVo *> >::iterator it = _levStepDic.find(lev);
	if(it != _levStepDic.end())
	{
		levList = it->second;
		std::list<StepVo *>::iterator stepIt;

		for(stepIt = levList.begin(); stepIt != levList.end(); ++ stepIt)
		{
			StepVo *pStep = *stepIt;
			_isOpenDic[pStep->btnId] = 1;
		}
		_levStepDic.erase(it);
	}
	return levList;

}

bool NewhandManager::addScript( ScriptVo *pScript )
{
	if(!pScript)
	{
		return false;
	}

	_scriptDic.insert(make_pair(pScript->id, pScript));

	string type = pScript->trigger[0];
	if(type == "canTask")
	{
		_canTaskTriggerDic.insert(make_pair(pScript->taskId, pScript->id));
	}
	else if (type == "ownTask")
	{
		_ownTaskTriggerDic.insert(make_pair(pScript->taskId, pScript->id));
	}
	else if (type == "finTask")
	{
		_finTaskTriggerDic.insert(make_pair(pScript->taskId, pScript->id));
	}
	else if (type == "addBtn")
	{
		_addBtnTriggerDic.insert(make_pair(atoi(pScript->trigger[1].c_str()), pScript->id));
	}
	else if (type == "evt")
	{
		_evtTriggerDic.insert(make_pair(atoi(pScript->trigger[1].c_str()), pScript->id));
	}
	else if (type == "p")
	{
		_pTriggerDic.insert(make_pair(pScript->trigger[1], pScript->id));
	}

	return true;
}

ScriptVo * NewhandManager::getNewhandScript( int id )
{
	std::map<int, ScriptVo *>::iterator it = _scriptDic.find(id);
	if(it != _scriptDic.end())
	{
		ScriptVo *pScript = it->second;
		return pScript;
	}
	return NULL;
}

ScriptVo * NewhandManager::getCanTaskScript( int taskId )
{
	std::map<int, int>::iterator it = _canTaskTriggerDic.find(taskId);
	if(it != _canTaskTriggerDic.end())
	{
		int scriptId = it->second;
		return getNewhandScript(scriptId);
	}
	return NULL;
}

ScriptVo * NewhandManager::getOwnTaskScript( int taskId )
{
	std::map<int, int>::iterator it = _ownTaskTriggerDic.find(taskId);
	if(it != _ownTaskTriggerDic.end())
	{
		int scriptId = it->second;
		return getNewhandScript(scriptId);
	}
	return NULL;
}

ScriptVo * NewhandManager::getFinTaskScript( int taskId )
{
	std::map<int, int>::iterator it = _finTaskTriggerDic.find(taskId);
	if(it != _finTaskTriggerDic.end())
	{
		int scriptId = it->second;
		return getNewhandScript(scriptId);
	}
	return NULL;
}

void NewhandManager::touchNextScript( string type, int id )
{
	ScriptVo *pScript = NULL;
	int scriptId = -1;
	if(type=="addBtn")
	{
		std::map<int, int>::iterator it = _addBtnTriggerDic.find(id);
		if(it != _addBtnTriggerDic.end())
		{
			scriptId = it->second;
		}
		else // By LONGHUI  // while there is a new hand without task 
		{

		}
	}
	else if(type=="evt")
	{
		std::map<int, int>::iterator it = _evtTriggerDic.find(id);
		if(it != _evtTriggerDic.end())
		{
			scriptId = it->second;
		}
	}

	pScript = getNewhandScript(scriptId);

	if(pScript)
	{
		//Doyang 20120712
		TestNewhand *pTestNewhand = new TestNewhand(type, pScript, 0);
		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::TEST_NEW_HAND, pTestNewhand);
		CC_SAFE_DELETE(pTestNewhand);
	}
}

void NewhandManager::touchNextScript( std::string type, std::string id )
{
	ScriptVo *pScript = NULL;
	int scriptId = -1;
	if(type=="p")
	{
		std::map<std::string, int>::iterator it = _pTriggerDic.find(id);
		if(it != _pTriggerDic.end())
		{
			scriptId = it->second;
		}
		else // By LONGHUI  // while there is a new hand without task 
		{

		}
	}
	else
	{
		return;
	}

	pScript = getNewhandScript(scriptId);

	if(pScript)
	{
		//Doyang 20120712
		TestNewhand *pTestNewhand = new TestNewhand(type, pScript, 0);
		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::TEST_NEW_HAND, pTestNewhand);
		CC_SAFE_DELETE(pTestNewhand);
	}
}

ScriptVo * NewhandManager::getMapScriptById( int scriptId, int mapId )
{
	ScriptVo *pScript = getNewhandScript(scriptId);
	while(pScript)
	{
		if(pScript->trigger[0] == "map")
		{
			if(atoi(pScript->trigger[1].c_str()) == mapId)
			{
				return pScript;
			}
		}
		pScript = getNewhandScript(pScript->next_id);
	}
	return NULL;
}

void NewhandManager::closeLayer()
{
	/*_layerVisible = LayerManager.newhandLayer.visible;
	LayerManager.newhandLayer.visible = false;*/
}

void NewhandManager::openLayer()
{
	//LayerManager.newhandLayer.visible = _layerVisible;
}

//newhandStep.xml param="a|b" £¬a = btnId
bool NewhandManager::isOpenButton( int btnId )
{
	std::map<int, int>::iterator it = _isOpenDic.find(btnId);
	if(it != _isOpenDic.end())
	{
		return true;
	}
	return false;
}

void NewhandManager::touchNextEvent( int evtId )
{
	//if(_nextEventId == evtId)
	bool isFind = false ;
	std::list<int>::iterator iter = _nextEventIdList.begin();
	if(!_nextEventIdList.empty())// LONGHUI 20121012
	{
			for (iter ; iter != _nextEventIdList.end() ; iter++)
			{
				if (*iter == evtId)
				{
					isFind = true;
					break;
				}
			}

			if (isFind)
			{
				//Doyang 20120712
				TestNewhand *pTestNewhand = new TestNewhand("evt", NULL, evtId);
				GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::TEST_NEW_HAND, pTestNewhand);
				CC_SAFE_DELETE(pTestNewhand);
				// LONGHUI 20121012
				_nextEventIdList.erase(iter);
			}
	}
}

void NewhandManager::addCallBack( int id, CCNode *pTarget, SEL_CallFuncND selector, void *data )
{
	_callBackFunc.m_pSelectorTarget = pTarget;
	_callBackFunc.m_pCallFuncND = selector;
	_callBackFunc.m_data = data;
}

void NewhandManager::touchCallBack( int id )
{
	_callBackFunc.execute();
	_callBackFunc.m_pSelectorTarget = 0;
	_callBackFunc.m_data = 0;
}

NewhandManager::~NewhandManager()
{
	std::map< int , ScriptVo* >::iterator it;
	for ( it = _scriptDic.begin(); it != _scriptDic.end();it++ )
	{
		CC_SAFE_DELETE( it->second );
	}
	_scriptDic.clear();

	std::map< int, std::list<StepVo *> >::iterator itMap;
	std::list< StepVo *>::iterator itList;

	for ( itMap = _rcvTaskStepDic.begin(); itMap != _rcvTaskStepDic.end(); itMap++ )
	{
		std::list<StepVo *>& tmpIterList = itMap->second;
		for ( itList = tmpIterList.begin(); itList != tmpIterList.end(); itList++ )
		{
			CC_SAFE_DELETE( *itList );
		}
		itMap->second.clear();
	}
	_rcvTaskStepDic.clear();

	for ( itMap = _smtTaskStepDic.begin(); itMap != _smtTaskStepDic.end(); itMap++ )
	{
		for ( itList = itMap->second.begin(); itList != itMap->second.end(); itList++ )
		{
			CC_SAFE_DELETE( *itList );
		}
		itMap->second.clear();
	}
	_smtTaskStepDic.clear();

	for ( itMap = _levStepDic.begin(); itMap != _levStepDic.end(); itMap++ )
	{
		for ( itList = itMap->second.begin(); itList != itMap->second.end(); itList++ )
		{
			CC_SAFE_DELETE( *itList );
		}
		itMap->second.clear();
	}
	_levStepDic.clear();

	std::map<int, FightLeaderVo *>::iterator itFl;
	for ( itFl = _fightLeadDic.begin(); itFl != _fightLeadDic.end(); itFl++ )
	{
		CC_SAFE_DELETE( itFl->second );
	}
	_fightLeadDic.clear();
}

void NewhandManager::addNewHandHelpScript(HelpScriptVo *pScript)
{
	if (!pScript)
	{
		return;
	}
	
	_helpScriptDic.insert(make_pair(pScript->id , pScript));

}

int NewhandManager::getIDByProcessID(int processid)
{
	int ret = 0;
	std::map<int, HelpScriptVo *>::iterator iter = _helpScriptDic.begin();
	for ( ; iter != _helpScriptDic.end() ; iter++)
	{
		if (iter->second->processid == processid)
		{
			ret = iter->second->id;
			break;
		}
	}
	return ret;
}

void NewhandManager::createImagePathMap()
{
	// left VScroll
	_imagePathMap.insert(make_pair(20 , "mainUI/mn_btn3_normal.png"));
	_imagePathMap.insert(make_pair(21 , "mainUI/award.png"));
	_imagePathMap.insert(make_pair(22 , "mainUI/crystal.png"));
	_imagePathMap.insert(make_pair(23 , "mainUI/arena.png"));
	_imagePathMap.insert(make_pair(24 , "mainUI/mn_btn10_normal.png"));

	// top center items
	_imagePathMap.insert(make_pair(328 , "secsmallui/award.png"));
	_imagePathMap.insert(make_pair(324 , "secsmallui/door.png"));
	_imagePathMap.insert(make_pair(325 , "secsmallui/eggbtn.png"));
	_imagePathMap.insert(make_pair(322 , "secsmallui/firstcharge.png"));
	_imagePathMap.insert(make_pair(323 , "reward/loginreward1.png"));
	_imagePathMap.insert(make_pair(320 , "secsmallui/dailytask1.png"));
	_imagePathMap.insert(make_pair(339 , "secsmallui/trader_btn_nor.png"));
}

std::string NewhandManager::getImagePathByButtonId(int id)
{
	std::string str("");
	
	std::map<int , std::string>::iterator iter = _imagePathMap.begin();
	for (iter ; iter != _imagePathMap.end() ; iter++)
	{
		if (iter->first == id)
		{
			str.append(iter->second);
			break;
		}
	}

	if (str.empty())
	{
		str.append("mainui2/smallcircle.png");
	}

	return str;
}

void NewhandManager::initNewHandStateMap()
{
	for (int i = 0 ; i< LevLimitConst::Limit_Max ; i++)
	{
		_newHandStateMap.insert(make_pair(i , Flag_Close));
	}
}

int NewhandManager::getNewHandStateByType(int type)
{
	std::map<int , int >::iterator iter = _newHandStateMap.find(type);
	if(iter != _newHandStateMap.end())
	{
		return iter->second;
	}
	return -1;
}

void NewhandManager::setNewHandStateByType(int type , int state)
{
	std::map<int , int >::iterator iter = _newHandStateMap.find(type);
	if(iter != _newHandStateMap.end())
	{
		iter->second = state;
	}
	else
	{
		_newHandStateMap.insert(make_pair(type , state));
	}
}

void NewhandManager::doTaskFollow()
{
	if (ViewManager::getInstance()->_taskUIView)
	{
		TaskScrollView * pScrollView = (TaskScrollView *)ViewManager::getInstance()->_taskUIView->getChildByTag(TaskUIView::Tag_ScrollView);
		if (pScrollView)
		{
			pScrollView->ccTouchEnded( 0 , 0 );
		}
	}
}