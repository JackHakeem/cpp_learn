#include "NPCItem.h"

void NPCItem::findNpc()
{
	dispatchEvent(GO_TO_NPC, &_vo.id);
}