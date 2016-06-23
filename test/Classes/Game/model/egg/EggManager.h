#pragma once

#include "BaseType.h"
#include "utils/Singleton.h"

class EggManager:public Singleton<EggManager>
{
public:
	std::map<std::string, std::string> _eggDic;
		
	EggManager(){}
		
	void addEgg(std::string key, std::string tips)
	{
		_eggDic.insert(make_pair(key, tips));
	}
		
	/**
		* 根据蛋大类、小类、品质获取蛋蛋的tips内容 
		* @param type		蛋大类
		* @param smallType	蛋小类
		* @param quality	蛋品质
		* 
		*/		
	std::string getEggTips(int type, int smallType, int quality);
};