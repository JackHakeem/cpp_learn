//
//  SceneManager.cpp
//  HLQS_IPAD
//
//  Created by hui long on 12-2-27.
//  Copyright (c) 2012 4399. All rights reserved.
//

//#include "Include.h"
#include "SceneManager.h"
#include "view/scene/layer/BattleLayer.h"
#include "view/scene/layer/FightLayer.h"
#include "vo/SceneType.h"
#include "../player/RoleManage.h"

//static SceneManager * instance;


SceneManager::SceneManager()
{
    
}

SceneManager::~SceneManager()
{
}

void SceneManager::setMapDic(SceneVo* sceneVo)
{
	if(!sceneVo)
		return;

	if(_sceneDic.find(sceneVo->id) == _sceneDic.end())
		_sceneDic.insert(make_pair(sceneVo->id, *sceneVo));

	std::map<int, SceneVo>::iterator iter = _sceneDic.find(sceneVo->id);

	if(sceneVo->type != SceneType::CITY && sceneVo->type != SceneType::WORLD_BOSS)
	{
		int pid = sceneVo->pid == 0 ? sceneVo->id : sceneVo->pid;
		std::map<int, std::vector<int> >::iterator it = _scenePidDic.find(pid);
		if(it != _scenePidDic.end())
		{
			it->second.push_back(iter->second.id);
		}
		else
		{
			std::vector<int> v;
			v.push_back(iter->second.id);
			_scenePidDic.insert(make_pair(pid, v));
		}
	}
}
		
SceneVo* SceneManager::getSceneDic(int id)
{
	std::map<int, SceneVo>::iterator iter = _sceneDic.find(id);
	if (iter == _sceneDic.end())
	{
		return NULL;
	}

	return &(iter->second);
}
		
std::vector<SceneVo*> SceneManager::getWorldSceneDic()
{
	std::map<int, SceneVo>::iterator iter = _sceneDic.begin();
	std::vector<SceneVo*> ret;
	for(; iter != _sceneDic.end(); ++iter)
	{
		//if(iter->second.pid == 0 && iter->second.pid != 1051)
		if(iter->second.pid == 0)
		{
			ret.push_back(&(iter->second));
		}
	}

	return ret;
}

/**
* According to the map for father son atlas
* @param pid
* 
*/

std::vector<int>* SceneManager::getChildByPid(int pid)
{
	std::map<int, std::vector<int> >::iterator iter = _scenePidDic.find(pid);
	if (iter == _scenePidDic.end())
	{
		return NULL;
	}
	return &(iter->second);
}

std::vector<SceneVo*> SceneManager::getCityScenes()
{
	std::vector<SceneVo*> ret;
	std::map<int, SceneVo>::iterator iter = _sceneDic.begin();
	for(; iter != _sceneDic.end(); ++iter)
	{
		if(iter->second.id < 1050 && iter->second.pid == 0)
		{
			ret.push_back(&(iter->second));
		}
	}
	return ret;
}

std::vector<SceneVo*> SceneManager::getChallengeMapIDs()
{

	std::vector<SceneVo*> ret;
	std::map<int, SceneVo>::iterator iter = _sceneDic.begin();
	for(; iter != _sceneDic.end(); ++iter)
	{
		if(iter->second.type == 3)
		{
			//特殊处理1209
			{
						if (iter->first == 1209)
							continue;
			}
			//特殊处理1209
			{
						if (iter->first == 1201)
						{
							std::map<int, SceneVo>::iterator iterSpicl = _sceneDic.find(1209);
							if (iterSpicl != _sceneDic.end())
							{
								ret.push_back(&(iterSpicl->second));
							}
						}
			}

			ret.push_back(&(iter->second));

		}
	}
	return ret;

}

int SceneManager::getCurMapType()
{
	SceneVo* pSceneVo = SceneManager::Instance()->getSceneDic(RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId);
	if (pSceneVo)
	{
		return pSceneVo->type;
	}
	return -1;
}