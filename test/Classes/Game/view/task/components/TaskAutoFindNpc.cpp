#include "TaskAutoFindNpc.h"
#include "model/scene/vo/NPCVo.h"
#include "model/scene/NPCManager.h"
#include "model/task/vo/TaskBehaviorType.h"
#include "TaskStrConcat.h"
#include "model/scene/vo/SceneVo.h"
#include "model/scene/SceneManager.h"
#include "model/player/RoleManage.h"
#include "model/task/vo/TaskAskType.h"
#include "TaskType.h"

TaskAutoFindNpc::TaskAutoFindNpc()
{
	_progress = 0;
}

std::string TaskAutoFindNpc::taskFollowStr( TaskVo *pTaskVo )
{
	if(!pTaskVo) 
		return "";

	char pResult[20];
	string result;
	bool isFinish = TaskStrConcat::checkTaskFinish(pTaskVo->_taskTip);
	if(isFinish)
	{
		//任务完成可提交
		NPCVo *pNpcVo = NPCManager::Instance()->getNPC(pTaskVo->getFinishTaskNpc());
		SceneVo *pSceneVo = SceneManager::Instance()->getSceneDic(pNpcVo->_mapId);
		TaskTipVo *pTaskTipVo = pTaskVo->_taskTip;
		if(pTaskTipVo)
		{
			//var taskTipLast:TaskTipVo = taskTips[taskTips.length - 1];
			//打怪任务完成可提交的时候，不自动寻路（城内怪物除外）
			if(RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId > 1050)
			{
				result = "";
			}
			else
			{
				sprintf(pResult, "%d,%d,%d", TaskType::NPC, pSceneVo->id, pNpcVo->id);
				result = pResult;
			}
		}
		else
		{
			sprintf(pResult, "%d,%d,%d", TaskType::NPC, pSceneVo->id, pNpcVo->id);
			result = pResult;
		}
	}
	else
	{	
		//任务未完成
		TaskTipVo *pTaskTipVo = pTaskVo->_taskTip;
		if(pTaskTipVo)
		{
			if (pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_KILL_MONSTER  // 0 杀怪 杀死指定任务怪
				|| pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_GET_ITEM   // 6 非杀怪获得物品数达到要求（扣除物品）
				|| pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_NEED_ITEM 	// 1 非杀怪获得物品数达到要求（不扣除物品）
				|| pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_FALL_ITEM	// 5 杀怪掉落任务物品
				|| pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_KILL_GET_ITEM)   // 11 杀怪并拥有物品(不管是否是掉落)
			{
				//if(_progress == pTaskTipVo->_progress){//打怪多次的任务,只寻路一次
				//	pResult = "";
				//}else{
				//	_progress = pTaskTipVo->_progress;
				//	sprintf(pResult, "%d,%d,%d", TaskType::MONSTER, pTaskTipVo->_sceneId, pTaskTipVo->_progress);
				//	result = pResult;
				//}
				_progress = pTaskTipVo->_progress;
				sprintf(pResult, "%d,%d,%d", TaskType::MONSTER, pTaskTipVo->_sceneId, pTaskTipVo->_progress);
				result = pResult;
			}
			else if (pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_TALK)    // 2 对话
			{    
				result = getDialogType(pTaskVo, pTaskTipVo);
			}
			else if (pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_USE_ITEM)  // 3 使用物品
			{
				sprintf(pResult, "%d,%d,%d", TaskType::NPC, pTaskTipVo->_sceneId, pTaskTipVo->_id);
				result = pResult;
			}
			else if (pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_DRESS)   // 4 穿装备
			{
				//						str = "open_4_equip";
			}
			else if (pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_BEHAVIOR)  // 7 动作行为触发
			{
				result = getBehaviorType(pTaskVo, pTaskTipVo);
			}
			else if (pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_CRYSTALUP)  // 8 等级升级
			{
				result = getUpGradeType(pTaskVo, pTaskTipVo);
			}
			else if(pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_ACHIRVE_FORMATION  // 9 N个阵型到达M级
				|| pTaskTipVo->_type == TaskAskType::TASK_ASK_TYPE_ACHIRVE_PASSIVE_SKILL)  // 10 N个被动技能到达M级
			{
				result = "open_skill";
			}
		}
	}
	return result;
}

/**
* 对话任务 askType=2   同一个npc则可以直接完成，不同的npc需要去找 npcs[1] 配置的taskTipVo.id 需要重新赋值 
* @return 
* 
*/		
std::string TaskAutoFindNpc::getDialogType( TaskVo *pTaskVo, TaskTipVo *pTaskTipVo )
{
	if(!pTaskVo)
		return "";

	NPCVo *pNpcVo = NPCManager::Instance()->getNPC(pTaskVo->getFinishTaskNpc());
	pTaskTipVo->_id = pTaskVo->getFinishTaskNpc();
	pTaskTipVo->_name = pNpcVo->name;
	char pResult[20];
	sprintf(pResult, "%d,%d,%d", TaskType::NPC, pTaskTipVo->_sceneId, pTaskTipVo->_id);
	return pResult;
}

/**
* 动作行为触发的任务 askType=7
* @return 
* 
*/		
std::string TaskAutoFindNpc::getBehaviorType( TaskVo *pTaskVo, TaskTipVo *pTaskTipVo )
{
	char pResult[32];
	switch(pTaskTipVo->_id){
		//				case TaskBehaviorType.TASK_BEHAVIOR_STRENGTHEN:
		//					str = "open_strength";
		//					break;
		//				case TaskBehaviorType.TASK_BEHAVIOR_STRENGTHEN_CD:
		//					str = "open_strength";
		//					break;
	case TaskBehaviorType::TASK_BEHAVIOR_RECRUIT:
		//NPCVo *pNpcVo = NPCManager::Instance()->getNPC(pTaskVo->_pNpcs[1]);// 去提交任务处的NPC招募
		sprintf(pResult, "%d,%d,%d", TaskType::NPC, pTaskTipVo->_sceneId, pTaskTipVo->_id);
		break;

	case TaskBehaviorType::TASK_BEHAVIOR_FORMATION:
		if (pTaskVo->_id != 7) // task id for learning formation
		{
			sprintf(pResult, "open_formation");
		}
		break;
		//				case TaskBehaviorType.TASK_BEHAVIOR_FORMATION:
		//					str = "open_formation";
		//					break;
		//				case TaskBehaviorType.TASK_BEHAVIOR_PASSIV_SKILL:
		//					str = "open_skill";
		//					break;
		//				case TaskBehaviorType.TASK_BEHAVIOR_CRYSTAL:
		//					str = "open_crystal";
		//					break;
		//				case TaskBehaviorType.TASK_BEHAVIOR_TRAIN:
		//					str ="open_train";
		//					break;
		//				case TaskBehaviorType.TASK_BEHAVIOR_SPEEDUP:
		//					str = "open_train";
		//					break;
		//				case TaskBehaviorType.TASK_BEHAVIOR_FOSTER:
		//					str = "open_foster";
		//					break;
		//				case TaskBehaviorType.TASK_BEHAVIOR_IMPOSE:
		//					str = "open_impose"
		//					break;
		//				case TaskBehaviorType.TASK_BEHAVIOR_EQUIP_SKILL:
		//					str = "open_foster";
		//					break;
		//				case TaskBehaviorType.TASK_BEHAVIOR_ADD_FRIEND:
		//					str = "open_friend";
		//					break;
		//				case TaskBehaviorType.TASK_BEHAVIOR_WIND_CRYSTAL:
		//					str = "open_crystal";
		//					break;
		//				case TaskBehaviorType.TASK_BEHAVIOR_SUBMIT_ENT_TASK:
		//					str = "open_task";
		//					break;
		//				case TaskBehaviorType.TASK_BEHAVIOR_INTO_GUILD:
		//					str = "open_guild";
		//					break;
		//				case TaskBehaviorType.TASK_BEHAVIOR_BLESS_FRIEND:
		//					str = "open_friend";
		//					break;
		//				case TaskBehaviorType.TASK_BEHAVIOR_SUBMIT_DAYLYTARGET:
		//					str = "open_dialy";
		//					break;
		//				case TaskBehaviorType.TASK_BEHAVIOR_COMPLET_STAR:
		//					str = "open_dialy";
		//					break;
		//				case TaskBehaviorType.TASK_BEHAVIOR_JJC_FIGHT:
		//					str = "open_arena";
		//					break;
		//				case TaskBehaviorType.TASK_BEHAVIOR_RF_FIGHT:
		//					str = "open_farm";
		//					break;
		//				case TaskBehaviorType.TASK_BEHAVIOR_DELEGATE:
		//					str = "完成一次黑市淘宝";
		//					break;
		//				case TaskBehaviorType.TASK_BEHAVIOR_TRADE:
		//					str = "进行一次跑商";	
		//					break;
		//				case TaskBehaviorType.TASK_BEHAVIOR_DUNGEON_FIGHT:
		//					str = "发起一次副本挑战";
		//					break;
		//				case TaskBehaviorType.TASK_BEHAVIOR_GROUP_WAR:
		//					str = "发起一次巢穴战";
		//					break;
	}
	return pResult;
}

/**
* 升级任务（人物升级、水晶升级、阵型升级等） askType = 8
* @return 
* 
*/	
std::string TaskAutoFindNpc::getUpGradeType( TaskVo *pTaskVo, TaskTipVo *pTaskTipVo )
{
	char pResult[20];
	if(pTaskVo->_id == 1)
	{ // 主角升级
		//				str = "open_train";
	}
	else if(pTaskVo->_id == 2)
	{ // VIP升级
		//				str = "open_vip";
	}
	else if(pTaskVo->_id == 3)
	{ // 拥有某个佣兵
		NPCVo *pNpcVo = NPCManager::Instance()->getNPC(pTaskVo->getFinishTaskNpc()); // 提交任务处的招募NPC
		if(pNpcVo)
		{
			sprintf(pResult, "%d,%d,%d", TaskType::NPC, pTaskTipVo->_sceneId, pTaskTipVo->_id);
		}
	}
	else if(pTaskVo->_id == 4)
	{ // 主角身上拥有强化到某等级的武器
		//				str = "open_strength";
	}
	else if(pTaskVo->_id > 1000 && pTaskVo->_id < 7000)
	{ //monsterID：部位*1000+佣兵ID(主角佣兵ID999) 1 头部 2项链 3胸甲 4披风 5武器 6戒指
		//				str = "open_strength";
	}
	else if (pTaskVo->_id == 100
		||pTaskVo->_id == 251)
	{
		// Doyang 20120829 特殊处理
		sprintf(pResult, "%s", "open_recruit");
	}
	else
	{ // 水晶升级
		//				str = "open_crystal";
	}
	return pResult;
}


std::string TaskAutoFindNpc::conditionHtmlString( TaskVo *pTaskVo )
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
		SceneVo *pSceneVo = SceneManager::Instance()->getSceneDic(pEndNpc->_mapId);
		TaskTipVo *pTaskTipVo = new TaskTipVo();
		pTaskTipVo->_sceneName = pSceneVo->name;
		pTaskTipVo->_sceneId = pSceneVo->id;
		pTaskTipVo->_id = pEndNpc->id;
		pTaskTipVo->_name = pEndNpc->name;
		condition = TaskStrConcat::getDialog(pTaskVo, pTaskTipVo);
	}
	else
	{
		condition = TaskStrConcat::getTaskTip(pTaskVo);
	}
	return condition;
}
