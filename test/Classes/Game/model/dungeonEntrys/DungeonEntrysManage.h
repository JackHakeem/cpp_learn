#ifndef HLQS_DungeonEntrysManage_H_
#define HLQS_DungeonEntrysManage_H_
#include "utils/Singleton.h"
#include "BaseType.h"

class DungeonEntrysManage: public Singleton<DungeonEntrysManage>
{
public:
	DungeonEntrysManage();
	void setDungeonEntrysCfg(int city, std::vector<int>& maps);
	std::vector<int>* getStoryMapIDs(int cityID);
	std::vector<int>* getCityIDs();
	int getCityIDByMapID(int mapid);

public:
	std::map<int, std::vector<int> > mapAndCity;
	std::vector<int> citys;

};

#endif