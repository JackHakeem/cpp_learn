#ifndef _DAILY_TASK_EX_VO_H_
#define _DAILY_TASK_EX_VO_H_

struct DailyTaskExVo
{
	enum
	{
		//�ճ������£�
		//���     ����       
		DAILY_TASK_EX_TYPE_STORY = 1,		//1.    ���鸱��      
		DAILY_TASK_EX_TYPE_CHANLLENGE,		//2.    ��ս����      
		DAILY_TASK_EX_TYPE_ARENA,			//3.    ������        
		DAILY_TASK_EX_TYPE_STRENG,			//4.    װ��ǿ��      
		DAILY_TASK_EX_TYPE_GOLD,			//5.    �������      
		DAILY_TASK_EX_TYPE_TRAIN,			//6.    Ӷ��ѵ��      
		DAILY_TASK_EX_TYPE_SPEEDUP,			//7.    ѵ��ͻ��      
		DAILY_TASK_EX_TYPE_FOSTER,			//8.    ��������      
		DAILY_TASK_EX_TYPE_APPOINT,			//9.    �Ա�         
		DAILY_TASK_EX_TYPE_LEVY,			//10.    �ͽ���ȡ     
		DAILY_TASK_EX_TYPE_FRIEND			//11.    ��Ӻ���     
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