#include "EggManager.h"

std::string EggManager::getEggTips(int type, int smallType, int quality)
{
	char key[30];
	sprintf(key, "%d_%d_%d", type, smallType, quality);
		
	std::map<std::string, std::string>::iterator _eggDiciterator = _eggDic.find(key);
	if (_eggDiciterator != _eggDic.end())
		return _eggDiciterator->second;
	else
		return "none";
}