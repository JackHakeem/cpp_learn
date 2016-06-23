#include "ItemRiseInfo.h"

int ItemRiseInfo::getGrowup(int8 ItemGradeLevel,
		int8 EquipPos,
		int8 ItemSmallType)
{
	for (std::list<ItemRiseInfoVo>::iterator it = _Dic.begin(); 
		it != _Dic.end(); it++)
	{
		ItemRiseInfoVo& info = *it;
		if (info.cfg_ItemGradeLevel == ItemGradeLevel && 
			info.cfg_EquipPos == EquipPos && 
			info.cfg_ItemSmallType == ItemSmallType)
			return info.cfg_Growup;
	}
	return -1;
}