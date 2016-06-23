#ifndef _TASK_ASK_TYPE_H_
#define _TASK_ASK_TYPE_H_

class TaskAskType
{
public:
	enum
	{
		TASK_ASK_TYPE_KILL_MONSTER = 0,		// 杀死指定任务怪
		TASK_ASK_TYPE_FALL_ITEM,			// 杀怪掉落任务物品
		TASK_ASK_TYPE_TALK,					// 对话
		TASK_ASK_TYPE_USE_ITEM,				// 使用物品
		TASK_ASK_TYPE_DRESS,				// 穿装备
		TASK_ASK_TYPE_NEED_ITEM,			// 非杀怪获得物品数达到要求（不扣除物品）
		TASK_ASK_TYPE_GET_ITEM,				// 非杀怪获得物品数达到要求（扣除物品）
		TASK_ASK_TYPE_BEHAVIOR,				// 动作行为触发

		TASK_ASK_TYPE_CRYSTALUP,			// 到达等级任务	

		TASK_ASK_TYPE_ACHIRVE_FORMATION,	// N个阵型到达N级
		TASK_ASK_TYPE_ACHIRVE_PASSIVE_SKILL,// N个被动技能到达N级
		TASK_ASK_TYPE_KILL_GET_ITEM,		// 杀怪并拥有物品(不管是否是掉落)

	};
};
#endif