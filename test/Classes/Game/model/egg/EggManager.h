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
		* ���ݵ����ࡢС�ࡢƷ�ʻ�ȡ������tips���� 
		* @param type		������
		* @param smallType	��С��
		* @param quality	��Ʒ��
		* 
		*/		
	std::string getEggTips(int type, int smallType, int quality);
};