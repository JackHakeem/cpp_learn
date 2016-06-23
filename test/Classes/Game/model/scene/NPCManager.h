#ifndef _NPCMANAGER_H_
#define _NPCMANAGER_H_

#include "BaseType.h"
#include "vo/NPCVo.h"
#include "utils/Singleton.h"
//using namespace util;

typedef std::vector<int> MAPIDVECTOR;

typedef std::map<int, MAPIDVECTOR> MAPIDMAP;
typedef std::map<int, MAPIDVECTOR>::iterator MAPIDMAPITER;

typedef std::map<int, NPCVo *> MAPNPCVO;
typedef std::map<int, NPCVo *>::iterator MAPNPCVOITER;

class NPCManager:public Singleton<NPCManager>
{
public:
	NPCManager() {};
	~NPCManager();

public:
	NPCVo* allocVo(){ return new NPCVo(); };
	void setNPC(NPCVo* pNPCVo);
	NPCVo* getNPC( int npcId );
	MAPIDVECTOR getNpcsByMapId( int iMapID );
	CC_SYNTHESIZE(bool , hasGetTask , HasGetTask);
private:
	MAPNPCVO _npcDic;
	MAPIDMAP m_mapIDMap;	// A mapid corresponding to a npcid containers
};

#endif