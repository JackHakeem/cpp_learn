#pragma once

#include "BaseType.h"
#include "utils/Singleton.h"
#include "vo/shopVo.h"

class ItemRiseInfo:public Singleton<ItemRiseInfo>
{
public:
	std::list<ItemRiseInfoVo> _Dic;
	//	
	//ItemRiseInfo(){}
	//	
	void addInfo(int8 ItemGradeLevel,
		int8 EquipPos,
		int8 ItemSmallType,
		int8 Growup)
	{
		_Dic.push_back(ItemRiseInfoVo(ItemGradeLevel, EquipPos, ItemSmallType, Growup));
	}
	//	
	///**
	//	* 根据蛋大类、小类、品质获取蛋蛋的tips内容 
	//	* @param type		蛋大类
	//	* @param smallType	蛋小类
	//	* @param quality	蛋品质
	//	* 
	//	*/		
	int getGrowup(int8 ItemGradeLevel,
		int8 EquipPos,
		int8 ItemSmallType);
};