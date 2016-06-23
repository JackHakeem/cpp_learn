#ifndef _MONSTERMANAGER_H 
#define _MONSTERMANAGER_H 
#include "utils/Singleton.h"
#include "vo/NPCVo.h"
#include "vo/GMProgessVo.h"


class MonsterManager :public Singleton<MonsterManager>
{

public:
	MonsterManager() ;
	~MonsterManager(); 

private:

	std::map<int , NPCVo*> _monstersDic;                                       //Monster information, key: monsterId, value: NPCVo *
	std::map<int , NPCVo*> _MonstersGroupDic;                       //Combination monster information key: groupId, value: NPCVo *
	std::map<int , std::list<GMProgressVo*> > _mapGMonstersDic;   //Map of the combination of all the monster list,key:mapid, value:list GMProgessVo*
	std::map<int , GMProgressVo*>  _gMonstersDic;                          //ksy: id Progress Numbers, value:GMProgressVo*
	std::map<int , GMProgressVo*>  _MonstersByGroupIdDic;  

public:
	NPCVo* allocVo(){ return new NPCVo(); };
	void setMonsters(NPCVo* npcVo);
	NPCVo* getMonsters(int monsterId);
	void setMonsterGroup(NPCVo* npcVo);
    NPCVo* getMonsterGroup(int groupId );

	void setGMProgess(GMProgressVo* gmpro);
	std::list<GMProgressVo*>& getGroupMonsterByMapId(int mapId);
	int getGroupMonsterNumByMapId(int mapId);
	GMProgressVo* getGroupMonsterById(int id);
	GMProgressVo* getGroupMonsterByGroupId(int id);
};



#endif