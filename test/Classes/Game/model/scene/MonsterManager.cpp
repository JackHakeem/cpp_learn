#include "MonsterManager.h"

MonsterManager::MonsterManager()
{

}

MonsterManager::~MonsterManager()
{
	std::map< int, NPCVo* >::iterator it;
	for ( it = _monstersDic.begin(); it != _monstersDic.end(); it++ )
	{
		CC_SAFE_DELETE( it->second );
	}
	_monstersDic.clear();

	std::map< int, GMProgressVo* >::iterator itGm;
	for ( itGm = _gMonstersDic.begin(); itGm != _gMonstersDic.end(); itGm++ )
	{
		CC_SAFE_DELETE( itGm->second );
	}
	_gMonstersDic.clear();

	std::map<int , std::list<GMProgressVo*> >::iterator itMapDic;
	for ( itMapDic = _mapGMonstersDic.begin(); itMapDic != _mapGMonstersDic.end(); itMapDic++ )
	{
		//std::list<GMProgressVo*>& voList = itMapDic->second;
		//std::list<GMProgressVo*>::iterator itList;
		//for ( itList = voList.begin(); itList != voList.end(); itList++ )
		//{
		//	CC_SAFE_DELETE( *itList );
		//}
		itMapDic->second.clear();
	}
	_mapGMonstersDic.clear();

	std::map< int, NPCVo* >::iterator itGr;
	for ( itGr = _MonstersGroupDic.begin(); itGr != _MonstersGroupDic.end(); itGr++ )
	{
		CC_SAFE_DELETE( itGr->second );
	}
	_MonstersGroupDic.clear();
	
}



void MonsterManager::setMonsters( NPCVo* npcVo )
{
	if(!npcVo) return ;
	_monstersDic.insert(  make_pair( npcVo->id, npcVo) );

}


NPCVo* MonsterManager::getMonsters( int monsterId )
{
	std::map<int , NPCVo*>::iterator it = _monstersDic.find( monsterId );

	if ( it != _monstersDic.end() )
	{
		return it->second;
	}
	return NULL;

}

void MonsterManager::setMonsterGroup( NPCVo* npcVo )
{
	if(!npcVo) return ;
	_MonstersGroupDic.insert( make_pair(npcVo->id, npcVo)) ;          //From here monstergroup. Read the XML first id is groupid


}

NPCVo* MonsterManager::getMonsterGroup( int groupId )
{
	std::map<int , NPCVo*>::iterator it=_MonstersGroupDic.find(groupId);
	if ( it != _MonstersGroupDic.end() )
	{
		return it->second;
	}
	return NULL;
}

/**
		 * Set monster progress
		 * @GMProgressVo* gmpro

		 * std::map<int , GMProgressVo*>  _gMonstersDic; 
		 */	

void MonsterManager::setGMProgess( GMProgressVo* gmpro )    
{
	if(!gmpro) return;
	_gMonstersDic.insert(make_pair(gmpro->id, gmpro));
	_MonstersByGroupIdDic.insert(make_pair(gmpro->mgId, gmpro));

	std::map<int , std::list<GMProgressVo*> >::iterator it2 = _mapGMonstersDic.find(gmpro->mapId);

	if(it2!=_mapGMonstersDic.end())
	{
		std::list<GMProgressVo*>& gmList =it2->second;                  
		gmList.push_back(gmpro);
		 
	}
	else
	{
		std::list<GMProgressVo*> gmList2;
		gmList2.push_back(gmpro);
		_mapGMonstersDic.insert(make_pair(gmpro->mapId, gmList2));
	}
}



 
/**
		 *Get all of the combination of monster map list
		 * @param mapid Map Numbers


		 * @return  Array GMProgessVo
		 * 
		 */		
std::list<GMProgressVo*>& MonsterManager::getGroupMonsterByMapId( int mapId )
{
	std::map<int , std::list<GMProgressVo*> >::iterator it=_mapGMonstersDic.find(mapId);
	if(it!=_mapGMonstersDic.end())
	{
		return it->second;
	}
    
    return _mapGMonstersDic.begin()->second;//kevinchange
}


int MonsterManager::getGroupMonsterNumByMapId( int mapId )
{
	std::map<int , std::list<GMProgressVo*> >::iterator it=_mapGMonstersDic.find(mapId);
	if(it!=_mapGMonstersDic.end())
	{
		return it->second.size();
	}
	return NULL;
}

GMProgressVo* MonsterManager::getGroupMonsterById( int id )
{
	std::map<int , GMProgressVo*>::iterator it=_gMonstersDic.find(id);

	if(it!=_gMonstersDic.end())
	{
		return it->second;
	}
	return NULL;
}

GMProgressVo* MonsterManager::getGroupMonsterByGroupId( int id )
{
	std::map<int , GMProgressVo*>::iterator it=_MonstersByGroupIdDic.find(id);

	if(it!=_MonstersByGroupIdDic.end())
	{
		return it->second;
	}
	return NULL;
}




 


