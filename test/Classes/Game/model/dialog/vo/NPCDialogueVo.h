#ifndef _NPCDIALOGVO_H
#define _NPCDIALOGVO_H

#include "model/shop/vo/shopVo.h"
#include "TaskNodeVo.h"

class NPCDialogueVo
{
public:
	NPCDialogueVo(){};
	~NPCDialogueVo(){};

	int npcId;					//npc id
	//public var taskList:Dictionary;			//contains taskNodeVo list
	std::vector<TaskNodeVo *> taskList;
	std::vector<ShopVo *> chatList;			//Interactive list such as buying and selling
};
#endif