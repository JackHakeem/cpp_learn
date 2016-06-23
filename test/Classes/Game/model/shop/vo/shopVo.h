#ifndef _SHOPVO_H_
#define _SHOPVO_H_

#include "BaseType.h"	

class ShopVo
{
public:
	int32 npcid; // the corresponding NPC if is the mall. Is tentatively set for 0
	int32 type; // DialogueType
	std::string name; // shop name, the NPC list of words appear
	std::string otherinfos; // otherinfos
};

class ItemRiseInfoVo
{
public:
	ItemRiseInfoVo(
		int8 ItemGradeLevel,
		int8 EquipPos,
		int8 ItemSmallType,
		int8 Growup
	)
	{
		cfg_ItemGradeLevel = ItemGradeLevel;
		cfg_EquipPos = EquipPos;
		cfg_ItemSmallType = ItemSmallType;
		cfg_Growup = Growup;
	}
	int8 cfg_ItemGradeLevel; 
	int8 cfg_EquipPos;
	int8 cfg_ItemSmallType; 
	int8 cfg_Growup;
};

#endif