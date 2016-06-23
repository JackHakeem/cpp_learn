#include "ExitManager.h"

ExitManager::ExitManager()
{
}

void ExitManager::setExit(ExitVo& exitVo)
{

	_exitDic.insert(make_pair(exitVo.id(), exitVo));

	std::map<int, std::vector<int> >::iterator iter = _exitMapDic.find(exitVo.mapId());
	if(iter != _exitMapDic.end())
	{
		iter->second.push_back(exitVo.id());
	}
	else
	{
		std::vector<int> vec;
		vec.push_back(exitVo.id());
		_exitMapDic.insert(make_pair(exitVo.mapId(), vec));
	}
}

ExitVo* ExitManager::getExit(int exitId)
{
	std::map<int, ExitVo>::iterator iter = _exitDic.find(exitId);
	if (iter == _exitDic.end())
	{
		return NULL;
	}
	return &(iter->second);
}

std::vector<int>* ExitManager::getExitsByMapId(int mapId)
{
	std::map<int, std::vector<int> >::iterator iter = _exitMapDic.find(mapId);
	
	if (iter == _exitMapDic.end())
	{
		return NULL;
	}
	return &(iter->second);
}


void ExitManager::addNotOpenExit(ExitVo* exitVo)
{
	if(!exitVo)
		return;

	if(_notOpenDic.find(exitVo->id()) != _notOpenDic.end())
		_notOpenDic.insert(make_pair(exitVo->id(), exitVo));
}

void ExitManager::removeNotOpenExit(int exitId)
{
	std::map<int, ExitVo*>::iterator iter = _notOpenDic.find(exitId);
	if(iter != _notOpenDic.end())
		_notOpenDic.erase(iter);
}

std::vector<ExitVo*> ExitManager::getNotOpenExitByMapId(int mapId)
{
	std::vector<ExitVo*> notOpen;
	for(std::map<int, ExitVo*>::iterator iter = _notOpenDic.begin();
		iter != _notOpenDic.end(); ++iter)
	{
		if(iter->second != NULL && iter->second->mapId() == mapId)
		{
			notOpen.push_back(iter->second);
		}
	}
	return notOpen;
}

void ExitManager::dispose()
{
	_exitDic.clear();
	_exitMapDic.clear();
	_notOpenDic.clear();
}