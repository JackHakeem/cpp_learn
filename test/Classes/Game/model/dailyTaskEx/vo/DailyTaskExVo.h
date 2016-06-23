#ifndef _DAILY_TASK_EX_VO_H_
#define _DAILY_TASK_EX_VO_H_

struct DailyTaskExVo
{
	enum
	{
		//日常任务（新）
		//序号     种类       
		DAILY_TASK_EX_TYPE_STORY = 1,		//1.    剧情副本      
		DAILY_TASK_EX_TYPE_CHANLLENGE,		//2.    挑战副本      
		DAILY_TASK_EX_TYPE_ARENA,			//3.    竞技场        
		DAILY_TASK_EX_TYPE_STRENG,			//4.    装备强化      
		DAILY_TASK_EX_TYPE_GOLD,			//5.    金币消耗      
		DAILY_TASK_EX_TYPE_TRAIN,			//6.    佣兵训练      
		DAILY_TASK_EX_TYPE_SPEEDUP,			//7.    训练突飞      
		DAILY_TASK_EX_TYPE_FOSTER,			//8.    进行培养      
		DAILY_TASK_EX_TYPE_APPOINT,			//9.    淘宝         
		DAILY_TASK_EX_TYPE_LEVY,			//10.    赏金领取     
		DAILY_TASK_EX_TYPE_FRIEND			//11.    添加好友     
	};

	DailyTaskExVo()
	{
		taskId = 0;
		quailty = 0;
		type = 0;
		monsterGroup = 0;
		count = 0;
		finishCount = 0;
		hasAccepted = 0;
	}

	int8 taskId;
	int8 quailty;
	int8 type;
	int32 monsterGroup;
	int8 count;
	int8 finishCount;
	int8 hasAccepted;
	std::vector<std::pair<int, int> > awardList;
};
#endif