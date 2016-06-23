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
	//	* ���ݵ����ࡢС�ࡢƷ�ʻ�ȡ������tips���� 
	//	* @param type		������
	//	* @param smallType	��С��
	//	* @param quality	��Ʒ��
	//	* 
	//	*/		
	int getGrowup(int8 ItemGradeLevel,
		int8 EquipPos,
		int8 ItemSmallType);
};