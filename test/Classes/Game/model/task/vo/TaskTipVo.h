#ifndef _TASK_TIP_VO_H_
#define _TASK_TIP_VO_H_
#include "BaseType.h"
class TaskTipVo
{
public:
	TaskTipVo();
	~TaskTipVo();

	int _id; // in the dialogue is NpcId task in task TASK_ASK_TYPE_CRYSTALUP category as category classId use
	std::string _name; // Npc name
	int _progress; // monster in progress, is used in the automatic pathfinding
	int _goodsId; // items Id in the collection 1 and 11 task category need the two fields
	std::string _goodsName; // items name
	int _type; // task content type TaskAskType 0 monsters collection 1 2 dialogue and task 8 upgrade task, and so on
	int _isFinish; // is completed
	int _count; // need quantity in the category TASK_ASK_TYPE_CRYSTALUP count as the task of id categories use conditions
	int _nowCount; // now number
	int _sceneId; // in the scene id
	std::string _sceneName; // in the name of the scene
};
#endif