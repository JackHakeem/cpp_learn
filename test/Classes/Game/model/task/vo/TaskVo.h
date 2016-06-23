#ifndef _TASK_VO_H_
#define _TASK_VO_H_
#include "BaseType.h"
#include "model/task/vo/TaskTipVo.h"

class TaskVo
{
public:
	TaskVo(){/*_pNpcs = new int[2];*/}
	virtual ~TaskVo();


	int _id; // task id
	int _level; // task required level
	std::string _dificulty; // entrust task difficulty
	int _frontTaskId; // task lead Numbers
	int _type; // task type 1 Lord, two, four entrusted
	int _askType; // task TaskAskType
	std::string _taskName; // task name
	std::string _description; // task description
	std::string _findStr; // find NPC, a strange
	int _copper; // / silver coin
	int _gold; // gold
	int _experience; // experience
	int _lifeExperiences; // experience
	int _energy; // energy
	std::vector < int > _fixedGoods; // fixed rewards
	std::vector < int > _dialogs; // task tip mission statement | the unfinished dialogue | submit task | | additional dialogue accept task dialogue
	TaskTipVo * _taskTip; // task tip
	//std::vector < int > _npcs;
	//int *_pNpcs; // NPC NPC | complete issued by the NPC
	std::list <int> _pNpcs;
	std::vector < int > _storys; // story 2 quests to complete the task 4
	//std::string _startDes; // = "1 | 1002 | 38";
	//std::string _endDes; // = "1 | 1002 | 38";

	virtual TaskVo *clone();

	void setFixGoods(std::string fixGoodsStr);
	void setDialogs(std::string dialogsStr);
	void setTaskTips(std::string taskTipsStr);
	void setNPCs(std::string npcsStr);
	void setStorys(std::string storysStr);

	int getFinishTaskNpc();
	int getRecTaskNpc();
	int getCanTaskNpc();
	int getCanTaskNpc( int taskId);

	bool isRecived();
};
#endif
