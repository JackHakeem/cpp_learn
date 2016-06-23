#ifndef _NPCITEM_H_
#define _NPCITEM_H_

#include "BaseType.h"
#include "model/scene/vo/NPCVo.h"

class NPCItem:public LayerNode
{
public:
	enum
	{
		GO_TO_NPC = 0,
	};

	void findNpc();
public:
	NPCVo _vo;
};

#endif