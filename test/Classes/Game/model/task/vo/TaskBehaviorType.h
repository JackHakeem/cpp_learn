#ifndef _TASK_BEHAVIOR_TYPE_H_
#define _TASK_BEHAVIOR_TYPE_H_

class TaskBehaviorType
{
public:
	enum
	{
		TASK_BEHAVIOR_STRENGTHEN = 1,    	// 强化
		TASK_BEHAVIOR_STRENGTHEN_CD,		// 强化清CD
		TASK_BEHAVIOR_RECRUIT,				// 招募
		TASK_BEHAVIOR_FORMATION,			// 阵型佣兵上阵
		TASK_BEHAVIOR_PASSIV_SKILL,			// 被动技能升级
		TASK_BEHAVIOR_CRYSTAL,		     	// 水晶升级
		TASK_BEHAVIOR_TRAIN,				// 训练
		TASK_BEHAVIOR_SPEEDUP,				// 突发
		TASK_BEHAVIOR_FOSTER,				// 培养	
		TASK_BEHAVIOR_IMPOSE,				// 征收
		TASK_BEHAVIOR_EQUIP_SKILL,			// 装备被动	
		TASK_BEHAVIOR_ADD_FRIEND,			// 加好友

		TASK_BEHAVIOR_WIND_CRYSTAL,			// 风之水晶升级
		//TASK_BEHAVIOR_MAINROLE_LV10 = 14,		// 主角升级到10级
		TASK_BEHAVIOR_SUBMIT_ENT_TASK = 15,		// 完成一次委托任务
		TASK_BEHAVIOR_INTO_GUILD,			// 加入或创建一个公会
		TASK_BEHAVIOR_BLESS_FRIEND,			// 祝福好友
		TASK_BEHAVIOR_SUBMIT_DAYLYTARGET,	 // 完成一次每日目标
		TASK_BEHAVIOR_COMPLET_STAR,			// (每日目标)完成一颗星
		TASK_BEHAVIOR_JJC_FIGHT,			// 发起一次竞技场战斗
		TASK_BEHAVIOR_RF_FIGHT,				// 发起一次资源田战斗
		TASK_BEHAVIOR_DELEGATE,				// 完成一次委派
		TASK_BEHAVIOR_TRADE,				// 进行一次跑商
		TASK_BEHAVIOR_DUNGEON_FIGHT,		// 发起一次副本挑战
		TASK_BEHAVIOR_GROUP_WAR,			// 发起一次军团战
	};
};
#endif