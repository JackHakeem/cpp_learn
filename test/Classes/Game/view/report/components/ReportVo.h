#ifndef _REPORTVO_H_
#define _REPORTVO_H_

#include "BaseType.h"

class ReportHeadVo
{
public:
    ReportHeadVo(){ type = 9; }
    uint32 battleId1;
    uint32 battleId2;
    int type;
    std::string name;
    int lev;
    int acount;
	int groupId;
};

class ReportMonsterVo
{
public:
	~ReportMonsterVo() { reportList.clear(); }
	int32 id;
	int32 mgId;
	std::string name;
	std::vector<ReportHeadVo> reportList;
};

class ReportVo
{
public:
	~ReportVo() { monsters.clear(); }
	int32 mapId;
	std::string mapName;
	std::vector<ReportMonsterVo> monsters;
};

#endif
