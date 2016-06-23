#include "DungeonEntrysManage.h"

DungeonEntrysManage::DungeonEntrysManage()
{

}

void DungeonEntrysManage::setDungeonEntrysCfg(int city, std::vector<int>& maps)
{
	mapAndCity.insert(make_pair(city, maps));
	citys.push_back(city);
}

std::vector<int>* DungeonEntrysManage::getStoryMapIDs(int cityID)
{
	std::map<int, std::vector<int> >::iterator iter = mapAndCity.find(cityID);
	if(iter != mapAndCity.end())
	{
		return &(iter->second);
	}
	
	return NULL;
}

std::vector<int>* DungeonEntrysManage::getCityIDs()
{
	return &citys;
}

int DungeonEntrysManage::getCityIDByMapID(int mapid)
{
	std::map<int, std::vector<int> >::iterator iter = mapAndCity.begin();
	for(; iter != mapAndCity.end(); ++iter)
	{
		std::vector<int>::iterator it = iter->second.begin();
		for(; it != iter->second.end(); ++it)
		{
			if(*it == mapid)
				return iter->first;
		}
	}

	return 0;
}