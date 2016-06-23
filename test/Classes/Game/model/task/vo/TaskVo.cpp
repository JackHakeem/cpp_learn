#include "TaskVo.h"
#include "model/scene/vo/NPCVo.h"
#include "model/scene/MonsterManager.h"
#include "model/backpack/GoodsManager.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "../TaskProxy.h"

TaskVo * TaskVo::clone()
{
	TaskVo *newTask = new TaskVo();
	newTask->_id = _id;
	newTask->_level = _level;
	newTask->_frontTaskId = _frontTaskId;
	newTask->_type = _type;
	newTask->_taskName = _taskName;
	newTask->_description = _description;
	newTask->_findStr = _findStr;
	newTask->_copper = _copper;
	newTask->_experience = _experience;
	newTask->_lifeExperiences = _lifeExperiences;
	newTask->_energy = _energy;
	newTask->_fixedGoods.assign(_fixedGoods.begin(), _fixedGoods.end());
	newTask->_dialogs.assign(_dialogs.begin(), _dialogs.end());
	newTask->_taskTip = _taskTip;
	newTask->_pNpcs.assign(_pNpcs.begin(), _pNpcs.end());
	/*newTask->_pNpcs[0] = _pNpcs[0];
	newTask->_pNpcs[1] = _pNpcs[1];*/
	newTask->_storys.assign(_storys.begin(), _storys.end());
	return newTask;
}

void TaskVo::setFixGoods( std::string fixGoodsStr )
{
	//cocos2d::CCLog("...setFixGoods=%s", fixGoodsStr.c_str());
	if(fixGoodsStr.empty()) return;
	_fixedGoods.clear();
	int pos1, pos2;
	pos1 = 0;
	pos2 = fixGoodsStr.find('|');
	while(std::string::npos != pos2)
	{
		int split = atoi(fixGoodsStr.substr(pos1, pos2 - pos1).c_str());
		_fixedGoods.push_back(split);
		pos1 = pos2 + 1;
		pos2 = fixGoodsStr.find('|',  pos1);
	}
	_fixedGoods.push_back(atoi(fixGoodsStr.substr(pos1).c_str()));
}

void TaskVo::setDialogs( std::string dialogsStr )
{
	//cocos2d::CCLog("...setDialogs=%s", dialogsStr.c_str());
	if(dialogsStr.empty()) return;
	_dialogs.clear();
	int pos1, pos2;
	pos1 = 0;
	pos2 = dialogsStr.find('|');
	while(std::string::npos != pos2)
	{
		int split = atoi(dialogsStr.substr(pos1, pos2 - pos1).c_str());
		_dialogs.push_back(split);
		pos1 = pos2 + 1;
		pos2 = dialogsStr.find('|',  pos1);
	}
	_dialogs.push_back(atoi(dialogsStr.substr(pos1).c_str()));
}

void TaskVo::setTaskTips( std::string taskTipsStr )
{
	if(taskTipsStr.empty()) return;
	int pos1, pos2;
	pos1 = 0;
	pos2 = taskTipsStr.find('|');

	_taskTip = new TaskTipVo();
	_taskTip->_id = atoi(taskTipsStr.substr(pos1, pos2 - pos1).c_str());
	pos1 = pos2 + 1;
	pos2 = taskTipsStr.find('|',  pos1);
	_taskTip->_type = atoi(taskTipsStr.substr(pos1, pos2 - pos1).c_str());

	_taskTip->_isFinish = 0;

	pos1 = pos2 + 1;
	pos2 = taskTipsStr.find('|',  pos1);
	_taskTip->_count = atoi(taskTipsStr.substr(pos1, pos2 - pos1).c_str());

	_taskTip->_nowCount = 0;

	pos1 = pos2 + 1;
	pos2 = taskTipsStr.find('#',  pos1);

	if(std::string::npos != pos2)
	{
		_taskTip->_sceneId = atoi(taskTipsStr.substr(pos1, pos2 - pos1).c_str());

		pos1 = pos2 + 1;
		taskTipsStr = taskTipsStr.substr(pos1).c_str();
		pos1 = 0;
		pos2 = taskTipsStr.find('|');
		if(std::string::npos != pos2)
		{
			_taskTip->_sceneName = taskTipsStr.substr(pos1, pos2 - pos1);
			_taskTip->_progress = atoi(taskTipsStr.substr(pos2 + 1).c_str());
		}
		else
		{
			_taskTip->_sceneName = taskTipsStr;
		}
	}
	if(_taskTip->_type == 0)
	{
		NPCVo *monster = MonsterManager::Instance()->getMonsters(_taskTip->_id);
		if(monster)
			_taskTip->_name = monster->name;
	}
	else if(_taskTip->_type == 1)
	{
		GoodsBasic *pGoods = g_pGoodsManager->getBasicGood(_taskTip->_id);
		_taskTip->_name = pGoods->goodName;
	}

	/*cocos2d::CCLog("-------taskTip,id=%d,type=%d,count=%d,sceneId=%d,sceneName=%s",
		_taskTip->_id,
		_taskTip->_type,
		_taskTip->_count,
		_taskTip->_sceneId,
		_taskTip->_sceneName.c_str());*/
}

void TaskVo::setNPCs( std::string npcsStr )
{
	//cocos2d::CCLog("...setNPCs=%s", npcsStr.c_str());
	if(npcsStr.empty()) return;
	int pos1, pos2;
	pos1 = 0;
	pos2 = npcsStr.find('|');
	_pNpcs.push_back(atoi(npcsStr.substr(pos1, pos2 - pos1).c_str()));

	pos1 = pos2 + 1;
	_pNpcs.push_back(atoi(npcsStr.substr(pos1).c_str()));
	/*cocos2d::CCLog("-------setNPCs,[0]=%d,[1]=%d",
		_npcs[0],
		_npcs[1]);*/
}

void TaskVo::setStorys( std::string storysStr )
{
	//cocos2d::CCLog("...setStorys=%s", storysStr.c_str());
	if(storysStr.empty()) return;
	_storys.clear();
	int pos1, pos2;
	pos1 = 0;
	pos2 = storysStr.find('|');
	while(std::string::npos != pos2)
	{
		int split = atoi(storysStr.substr(pos1, pos2 - pos1).c_str());
		_storys.push_back(split);
		pos1 = pos2 + 1;
		pos2 = storysStr.find('|',  pos1);
	}
	_storys.push_back(atoi(storysStr.substr(pos1).c_str()));
}

TaskVo::~TaskVo()
{
	//CC_SAFE_DELETE_ARRAY( _pNpcs );
	CC_SAFE_DELETE( _taskTip );
}

int TaskVo::getFinishTaskNpc()
{
	int finTaskNpcId = 0;
	std::list<int>::iterator it;
	int index = 0;
	for(it = _pNpcs.begin(); it != _pNpcs.end(); ++it)
	{
		if(index == 1)
		{
			finTaskNpcId = *it;
			break;
		}
		++ index;
	}
	return finTaskNpcId;
}

int TaskVo::getRecTaskNpc()
{
	return *_pNpcs.begin();
}

bool TaskVo::isRecived()
{
	TaskProxy * pTaskProxy = (TaskProxy *)g_pFacade->retrieveProxy(AppFacade_TASK_PROXY);
	if (!pTaskProxy)		{return 0;		}
	std::vector<TaskVo *> pRecvList = pTaskProxy->getAllRecTask();
	if (pRecvList.empty())		{return 0;		}
	std::vector<TaskVo *>::iterator iter = pRecvList.begin();
	for (iter ; iter != pRecvList.end() ; iter++)
	{
		if (_id == (*iter)->_id)
		{
			return true;
		}		
	}
	return false;
}

int TaskVo::getCanTaskNpc()
{
	int canTaskNpcId = 0;
	TaskProxy * pTaskProxy = (TaskProxy *)g_pFacade->retrieveProxy(AppFacade_TASK_PROXY);
	if (!pTaskProxy)		{return 0;		}
	std::vector<TaskVo *> pCanList = pTaskProxy->getCanTasks();
	if (pCanList.empty())		{return 0;		}
	std::vector<TaskVo *>::iterator iter = pCanList.begin();
	for (iter ; iter != pCanList.end() ; iter++)
	{
		if ((*iter)->_type == 1)
		{
			std::list<int> npcList = (*iter)->_pNpcs;
			if (!npcList.empty())
			{
				std::list<int>::iterator it = npcList.begin();
				canTaskNpcId = *it;
			}
			break;
		}
	}
	if (canTaskNpcId == 0)
	{
		std::list<int> npcList = (*pCanList.begin())->_pNpcs;
		if (!npcList.empty())
		{
			std::list<int>::iterator it = npcList.begin();
			canTaskNpcId = *it;
		}
	}
	return canTaskNpcId;
}

int TaskVo::getCanTaskNpc( int taskId)
{
	int canTaskNpcId = 0;

	TaskProxy * pTaskProxy = (TaskProxy *)g_pFacade->retrieveProxy(AppFacade_TASK_PROXY);
	if (!pTaskProxy)		{return 0;		}
	std::vector<TaskVo *> pRecvList = pTaskProxy->getAllRecTask();
	if (!pRecvList.empty())
	{
		std::vector<TaskVo *>::iterator iter = pRecvList.begin();
		for (iter ; iter != pRecvList.end() ; iter++)
		{
			if ((*iter)->_id == taskId)
			{
				std::list<int> npcList = (*iter)->_pNpcs;
				if (!npcList.empty())
				{
					std::list<int>::iterator it = npcList.begin();
					canTaskNpcId = *it;
				}
				break;
			}
		}
	}
	
	pTaskProxy = (TaskProxy *)g_pFacade->retrieveProxy(AppFacade_TASK_PROXY);
	if (!pTaskProxy)		{return 0;		}
	std::vector<TaskVo *> pCanList = pTaskProxy->getCanTasks();
	if (!pCanList.empty())
	{
		std::vector<TaskVo *>::iterator iter1 = pCanList.begin();
		for (iter1 ; iter1 != pCanList.end() ; iter1++)
		{
			if ((*iter1)->_id == taskId)
			{
				std::list<int> npcList = (*iter1)->_pNpcs;
				if (!npcList.empty())
				{
					std::list<int>::iterator it = npcList.begin();
					canTaskNpcId = *it;
				}
				break;
			}
		}
	}	

	if (canTaskNpcId == 0)
	{
		std::list<int> npcList = (*pCanList.begin())->_pNpcs;
		if (!npcList.empty())
		{
			std::list<int>::iterator it = npcList.begin();
			canTaskNpcId = *it;
		}
	}
	return canTaskNpcId;
}