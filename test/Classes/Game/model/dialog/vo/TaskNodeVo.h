#ifndef _TASK_NODE_VO_H_
#define _TASK_NODE_VO_H_

#include "BaseType.h"
#include "DialogueNodeVo.h"

class TaskNodeVo
{
public:
	TaskNodeVo(){}
	~TaskNodeVo(){}

public:

	// task id
	int _id;
	// task types
	int _type;
	// task name
	std::string _name;
	// task state 0: may meet; 3 have accepted, unfinished; 2 has been completed, and fails to submit
	int _state;
	// DialogueNodeVo 0, mission statement, 1, the unfinished dialogue, 2 submit task dialogue 3. Accept task in the main character of the mission statement of 4 a question
	std::vector < DialogueNodeVo * > _list;
};
#endif