#include "TaskStrConcat.h"
#include "model/task/vo/TaskAskType.h"
#include "TaskType.h"
#include "model/scene/NPCManager.h"
#include "model/task/vo/TaskBehaviorType.h"
#include "model/scene/vo/SceneVo.h"
#include "model/scene/SceneManager.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "model/scene/vo/FindVo.h"
#include "manager/GlobalManage.h"
#include "model/task/TaskProxy.h"
#include "control/AppFacade.h"

bool TaskStrConcat::checkTaskFinish( TaskTipVo * tips )
{
	bool isFinish = true;
	/*int tipsSize = tips.size();
	for(int i=0; i<tipsSize; ++i)
	{
	if(tips[i]->_isFinish == 0)
	{
	isFinish = false;
	break;
	}
	}*/
	if(tips->_isFinish == 0) 
		isFinish = false;

	return isFinish;
}


std::string TaskStrConcat::getTaskTip( TaskVo *pTaskVo )
{
	//var string:String = "<font color='" + color + "'>";
	string str = "";

	if(!pTaskVo)
		return str;
	/*for (var i:uint=0; i < taskVo.taskTips.length; i++)
	{*/
	TaskTipVo *pTaskTipVo = pTaskVo->_taskTip;
	if(!pTaskTipVo)
		return str;

	if (pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_KILL_MONSTER  // 杀怪 杀死指定任务怪 0
		|| pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_GET_ITEM )  // 非杀怪获得物品数达到要求（扣除物品）6
	{
		str = getType0(pTaskVo, pTaskTipVo);
	}
	else if (pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_NEED_ITEM // 非杀怪获得物品数达到要求（不扣除物品）1
		|| pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_FALL_ITEM)   //  杀怪掉落任务物品  5
	{
		str = getType1(pTaskVo, pTaskTipVo);
	}
	else if (pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_TALK)    // 对话 2 
	{    
		str = getType2(pTaskVo, pTaskTipVo);
	}
	else if (pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_USE_ITEM)  // 使用物品 3
	{
		str = getType3(pTaskVo, pTaskTipVo);
	}
	else if (pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_DRESS)   // 穿装备 4 
	{
		str = getType4(pTaskVo, pTaskTipVo);
	}
	else if (pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_BEHAVIOR)  // 动作 7
	{
		str = getType7(pTaskVo, pTaskTipVo);
	}
	else if (pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_CRYSTALUP)  // 等级升级  8
	{
		str = getType8(pTaskVo, pTaskTipVo);
	}
	else if(pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_ACHIRVE_FORMATION)  //  9 N个阵型到达M级
	{	
		str = getType9(pTaskVo, pTaskTipVo);
	}
	else if(pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_ACHIRVE_PASSIVE_SKILL)  // 10 N个被动技能到达M级
	{
		str = getType10(pTaskVo, pTaskTipVo);
	}
	else if(pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_KILL_GET_ITEM) //  11 
	{
		str = getType11(pTaskVo, pTaskTipVo);
	}

	//if (taskVo.taskTips.length > 1) str = (getTaskState(taskTipVo.isFinish));

	//string = string.concat("\n");
	/*}*/

	//return string.concat("</font>");
	return str;
}

/**
* Kill Monster
* 
*/
std::string TaskStrConcat::getType0( TaskVo *pTaskVo, TaskTipVo *pTaskTipVo )
{
	char pChar[20];
	sprintf(pChar, "%d,%d,%d", TaskType::MONSTER, pTaskTipVo->_sceneId, pTaskTipVo->_progress);
	return pChar;
}
/**
* Collect goods askType=1
* 
*/	
std::string TaskStrConcat::getType1( TaskVo *pTaskVo, TaskTipVo *pTaskTipVo )
{
	char pChar[20];
	sprintf(pChar, "%d,%d,%d", TaskType::MONSTER, pTaskTipVo->_sceneId, pTaskTipVo->_progress);
	return pChar;
}

/**
* Dialog Task askType=2   base on npc[1] 
* 
*/	
std::string TaskStrConcat::getType2( TaskVo *pTaskVo, TaskTipVo *pTaskTipVo )
{
	//NPCVo *pNpcVo = NPCManager::Instance()->getNPC(pTaskVo->_pNpcs[1]);
	pTaskTipVo->_id = pTaskVo->getFinishTaskNpc();
	//pTaskTipVo->_name = pNpcVo->name;

	char pChar[20];
	sprintf(pChar, "%d,%d,%d", TaskType::NPC, pTaskTipVo->_sceneId, pTaskTipVo->_id);
	return pChar;
}

/**
* Use Goods askType=3
* 
*/		
std::string TaskStrConcat::getType3( TaskVo *pTaskVo, TaskTipVo *pTaskTipVo )
{
	char pChar[20];
	sprintf(pChar, "%d,%d,%d", TaskType::NPC, pTaskTipVo->_sceneId, pTaskTipVo->_id);
	return pChar;
}

/**
* Get on equipments askType=4
* 
*/	
std::string TaskStrConcat::getType4( TaskVo *pTaskVo, TaskTipVo *pTaskTipVo )
{
	return "open_4_equip";
}
//
//std::string TaskStrConcat::getType5( TaskVo *pTaskVo, TaskTipVo *pTaskTipVo )
//{
//
//}
//
//std::string TaskStrConcat::getType6( TaskVo *pTaskVo, TaskTipVo *pTaskTipVo )
//{
//
//}

/**
* Action Task askType=7
* 
*/		
std::string TaskStrConcat::getType7( TaskVo *pTaskVo, TaskTipVo *pTaskTipVo )
{
	string str = "";
	switch(pTaskTipVo->_id)
	{
	case TaskBehaviorType::TASK_BEHAVIOR_STRENGTHEN:
		str = "open_strength";
		break;

	case TaskBehaviorType::TASK_BEHAVIOR_STRENGTHEN_CD:
		str = "open_strength";
		break;

	case TaskBehaviorType::TASK_BEHAVIOR_RECRUIT:
		{
			char pChar[20];
			sprintf(pChar, "%d,%d,%d", TaskType::NPC, pTaskTipVo->_sceneId, pTaskVo->getFinishTaskNpc());
			str = pChar;
		}
		break;

	case TaskBehaviorType::TASK_BEHAVIOR_FORMATION:
		str = "open_formation";
		break;

	case TaskBehaviorType::TASK_BEHAVIOR_PASSIV_SKILL:
		str = "open_skill";
		break;
	case TaskBehaviorType::TASK_BEHAVIOR_CRYSTAL:
		str = "open_crystal";
		break;
	case TaskBehaviorType::TASK_BEHAVIOR_TRAIN:
		str = "open_train";
		break;
	case TaskBehaviorType::TASK_BEHAVIOR_SPEEDUP:
		str = "open_train";
		break;
	case TaskBehaviorType::TASK_BEHAVIOR_FOSTER:
		str = "open_foster";
		break;
	case TaskBehaviorType::TASK_BEHAVIOR_IMPOSE:
		str = "open_impose";
		break;
	case TaskBehaviorType::TASK_BEHAVIOR_EQUIP_SKILL:
		str = "open_foster";
		break;
	case TaskBehaviorType::TASK_BEHAVIOR_ADD_FRIEND:
		str = "open_friend";
		break;
	case TaskBehaviorType::TASK_BEHAVIOR_WIND_CRYSTAL:
		str = "open_crystal";
		break;
	case TaskBehaviorType::TASK_BEHAVIOR_SUBMIT_ENT_TASK:
		str = "open_task";
		break;
	case TaskBehaviorType::TASK_BEHAVIOR_INTO_GUILD:
		str = "open_guild";
		break;
	case TaskBehaviorType::TASK_BEHAVIOR_BLESS_FRIEND:
		str = "open_friend";
		break;
	case TaskBehaviorType::TASK_BEHAVIOR_SUBMIT_DAYLYTARGET:
		str = "open_dialy";
		break;
	case TaskBehaviorType::TASK_BEHAVIOR_COMPLET_STAR:
		str = "open_dialy";
		break;
	case TaskBehaviorType::TASK_BEHAVIOR_JJC_FIGHT:
		str = "open_arena";
		break;
	case TaskBehaviorType::TASK_BEHAVIOR_RF_FIGHT:
		str = "open_farm";
		break;
	case TaskBehaviorType::TASK_BEHAVIOR_DELEGATE:
		{
			char pChar[20];
			sprintf(pChar, "%d,%d,%d", TaskType::NPC, pTaskTipVo->_sceneId, pTaskVo->getFinishTaskNpc());
			str = pChar;
		}
		break;
	case TaskBehaviorType::TASK_BEHAVIOR_TRADE:
		{
			char pChar[20];
			sprintf(pChar, "%d,%d,%d", TaskType::NPC, pTaskTipVo->_sceneId, pTaskVo->getRecTaskNpc());
			str = pChar;
		}
		//					str = "open_businiss", "进行一次跑商"));
		break;
	case TaskBehaviorType::TASK_BEHAVIOR_DUNGEON_FIGHT:
		{
			char pChar[20];
			sprintf(pChar, "%d,%d,%d", TaskType::NPC, pTaskTipVo->_sceneId, pTaskVo->getRecTaskNpc());
			str = pChar;
		}
		//					str = "open_copy", "发起一次副本挑战"));
		break;
	case TaskBehaviorType::TASK_BEHAVIOR_GROUP_WAR:
		{
			char pChar[20];
			sprintf(pChar, "%d,%d,%d", TaskType::NPC, pTaskTipVo->_sceneId, pTaskVo->getRecTaskNpc());
			str = pChar;
		}
		//					str = "open_army", "发起一次军团战"));
		break;
	}
	return str;
}

std::string TaskStrConcat::getType8( TaskVo *pTaskVo, TaskTipVo *pTaskTipVo )
{
	string str = "";
	switch(pTaskTipVo->_id)
	{
	case 1:
		str = "open_train";
		break;
		
	case 2:
		str = "open_vip";
		break;

	case 3:
		{
			char pChar[20];
			sprintf(pChar, "%d,%d,%d", TaskType::NPC, pTaskTipVo->_sceneId, pTaskVo->getFinishTaskNpc());
			str = pChar;
		}
		break;

	case 4:
		str = "open_strength";
		break;

	default:
		{
			if(pTaskTipVo->_id > 1000 &&
				pTaskTipVo->_id < 7000)
			{
				str = "open_strength";
			}
			else 
			{
				str = "open_crystal";
			}
		}
		break;
	}
	return str;
}

std::string TaskStrConcat::getType9( TaskVo *pTaskVo, TaskTipVo *pTaskTipVo )
{
	return "open_skill";
}

std::string TaskStrConcat::getType10( TaskVo *pTaskVo, TaskTipVo *pTaskTipVo )
{
	return "open_skill";
}

std::string TaskStrConcat::getType11( TaskVo *pTaskVo, TaskTipVo *pTaskTipVo )
{
	char pChar[20];
	sprintf(pChar, "%d,%d,%d", TaskType::MONSTER, pTaskTipVo->_sceneId, pTaskTipVo->_progress);
	return pChar;
}

std::string TaskStrConcat::getDialog( TaskVo *pTaskVo, TaskTipVo *pTaskTipVo )
{
	if(!pTaskVo || !pTaskTipVo)
		return "";
	char pChar[20];
	sprintf(pChar, "%d,%d,%d", TaskType::NPC, pTaskTipVo->_sceneId, pTaskTipVo->_id);
	return pChar;
}

std::string TaskStrConcat::conditionHtmlString( TaskVo *pTaskVo )
{
	//string condition:String = "";
	//var taskTipVo:TaskTipVo = new TaskTipVo;  
	//var sceneVo:SceneVo;

	//var npc:NPCVo;
	//var startNpc:NPCVo = NPCManager.getInstance().getNPC(taskVO.npcs[0]);
	//var endNpc:NPCVo = NPCManager.getInstance().getNPC(taskVO.npcs[1]);

	//condition += LangManager.getText("TSK068") + "<font color='#ffcc00'>" + startNpc.name +"</font>，";
	//condition += LangManager.getText("TSK069") + "<font color='#ffcc00'>" + endNpc.name + "</font>\n";

	//if(taskVO.taskTips.length == 0){
	//	npc = (curTabIndex == TAB_CAN_TASK) ? startNpc : endNpc;
	//	sceneVo = SceneManager.getInstance().getSceneDic(npc.mapId);
	//	taskTipVo.sceneName = sceneVo.name;
	//	taskTipVo.sceneId = sceneVo.id;
	//	taskTipVo.id = npc.id;
	//	taskTipVo.name = npc.name;  
	//	condition += TaskStrConcat.getDialog(taskVO, taskTipVo, "#ffcc00", "#ffffff");
	//}
	//else{
	//	var isFinish:Boolean = TaskStrConcat.checkTaskFinish(taskVO.taskTips);
	//	if(curTabIndex==TAB_CAN_TASK){ // 可接状态
	//		npc = startNpc;
	//		sceneVo = SceneManager.getInstance().getSceneDic(npc.mapId);
	//		taskTipVo.sceneName = sceneVo.name;
	//		taskTipVo.sceneId = sceneVo.id;
	//		taskTipVo.id = npc.id;
	//		taskTipVo.name = npc.name;
	//		condition += TaskStrConcat.getDialog(taskVO, taskTipVo, "#ffcc00", "#ffffff");

	//	}
	//	else if(curTabIndex==TAB_REC_TASK){
	//		if(isFinish){  // 可提交状态
	//			npc = endNpc;
	//			sceneVo = SceneManager.getInstance().getSceneDic(npc.mapId);
	//			taskTipVo.sceneName = sceneVo.name;
	//			taskTipVo.sceneId = sceneVo.id;
	//			taskTipVo.id = npc.id;
	//			taskTipVo.name = npc.name;
	//			condition += TaskStrConcat.getDialog(taskVO, taskTipVo, "#ffcc00", "#ffffff");
	//		}
	//		else{  // 未完成状态
	//			condition += TaskStrConcat.getTaskTip(taskVO, "#ffffff");
	//		}
	//	}
	//}


	string condition;
	bool isFinish = TaskStrConcat::checkTaskFinish(pTaskVo->_taskTip);
	if(isFinish)
	{
		NPCVo *pEndNpc = NPCManager::Instance()->getNPC(pTaskVo->getFinishTaskNpc());
		if (pEndNpc)
		{
			SceneVo *pSceneVo = SceneManager::Instance()->getSceneDic(pEndNpc->_mapId);
			if (pSceneVo)
			{
				TaskTipVo *pTaskTipVo = new TaskTipVo();
				pTaskTipVo->_sceneName = pSceneVo->name;
				pTaskTipVo->_sceneId = pSceneVo->id;
				pTaskTipVo->_id = pEndNpc->id;
				pTaskTipVo->_name = pEndNpc->name;
				condition = TaskStrConcat::getDialog(pTaskVo, pTaskTipVo);
				SAFE_DELETE(pTaskTipVo);
			}			
		}		
	}
	else
	{
		condition = TaskStrConcat::getTaskTip(pTaskVo);
	}

	

	// LH
	//if (!NPCManager::Instance()->getHasGetTask())
	if (!pTaskVo->isRecived())
	{
		//NPCVo *pBeginNpc = NPCManager::Instance()->getNPC(pTaskVo->getCanTaskNpc());
		NPCVo *pBeginNpc = NPCManager::Instance()->getNPC(pTaskVo->getCanTaskNpc(pTaskVo->_id));
		if (pBeginNpc)
		{
			SceneVo *pSceneVo = SceneManager::Instance()->getSceneDic(pBeginNpc->_mapId);
			if (pSceneVo)
			{
				TaskTipVo *pTaskTipVo = new TaskTipVo();
				pTaskTipVo->_sceneName = pSceneVo->name;
				pTaskTipVo->_sceneId = pSceneVo->id;
				pTaskTipVo->_id = pBeginNpc->id;
				pTaskTipVo->_name = pBeginNpc->name;
				condition = TaskStrConcat::getDialog(pTaskVo, pTaskTipVo);
				SAFE_DELETE(pTaskTipVo);
			}
		}		
	}
	else
	{
			
	}
	//condition = TaskStrConcat::getTaskTip(pTaskVo);

	return condition;
}

void TaskStrConcat::findNPC( TaskVo *pTaskVo )
{
	TaskStrConcat::findElement(conditionHtmlString(pTaskVo));
}

void TaskStrConcat::findElement( string str )
{
	/*
	if(!data)
	return;

	string str = * (string*)data;*/
	if(g_pGlobalManage->_isInFight || g_pGlobalManage->isInStory) return ;
			
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

