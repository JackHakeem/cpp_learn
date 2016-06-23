#include "MapManage.h"
#include "model/player/RoleManage.h"
#include "view/task/components/TaskType.h"
#include "model/scene/ExitManager.h"
#include "model/scene/vo/SceneVo.h"
#include "model/scene/SceneManager.h"
#include "model/scene/vo/SceneType.h"
#include "model/scene/SceneProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

MapManage::MapManage()
{
	isAutoFindPath = false;
}

void MapManage::findPath(FindVo findVo)
{
	_findVo = findVo;
	isAutoFindPath=true;
}

FindVo MapManage::findVo()
{
	return _findVo;
}

void MapManage::cancelAutoPath()
{
	isAutoFindPath = false;
	_findVo.reset();
	//this.dispatchEvent(new Event(Event.CANCEL));
}

FindVo MapManage::changeFindVoHandler(FindVo findVo)
{
	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();


	FindVo find = findVo;
	int mapId = 0;
	if(info)
	{
		mapId = info->playerBaseInfo._mapId;
	}

	if(findVo._sceneId == mapId)
		return find;

	SceneVo* target = SceneManager::Instance()->getSceneDic(findVo._sceneId);
	if(!target)
		return find;

	if(target && target->type == SceneType::CITY)
	{
		findVo._isShowWorldMap = true;
		return findVo;
	}
	else if(target->type == SceneType::STORY)
	{
		SceneVo* curMap = SceneManager::Instance()->getSceneDic(mapId);
		if(!curMap)
			return find;

		SceneProxy* sceneProxy = (SceneProxy*)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
		if(!sceneProxy)
			return find;
		int status = sceneProxy->getSceneStatus(target->id);
		if(status > 0)
		{
			findVo._isShowWorldMap = false;
			return findVo;
		}
		else
		{
			int cityId;
			if(curMap->type == SceneType::CITY)
			{
				cityId = mapId;
			}
			else if(curMap->type == SceneType::STORY)
			{
				//cityId = DungeonEntrysManage.getInstance().getCityIDByMapID(target.id);
			}
			_nextFindVo._sceneId = findVo._sceneId;
			_nextFindVo._npcId = findVo._npcId;
			_nextFindVo._type = findVo._type;
			std::vector<int>* exits = ExitManager::Instance()->getExitsByMapId(cityId);
			if(exits)
			{
				std::vector<int>::iterator iter = exits->begin();
				for(; iter != exits->end(); ++iter)
				{
					ExitVo* exitVo = ExitManager::Instance()->getExit(*iter);

					if(exitVo && exitVo->otherInfos[0] == 0)
					{
						findVo._sceneId = cityId;
						findVo._npcId = *iter;
						findVo._type = TaskType::EXIT;
						findVo._isShowWorldMap = false;
						return findVo;
					}
				}
			}
		}
	}
	return find;
	/*
	if(mapId==1001 || mapId==1002)
	{
		_nextFindVo.reset();
		_nextFindVo._sceneId = findVo._sceneId;
		_nextFindVo._npcId = findVo._npcId;
		_nextFindVo._type = findVo._type;
		//In the new village to the garden, path, and in the dean city to silence the graveyard, will be looking for NPC to look for exit
		if(find._sceneId >= 1052 && find._sceneId <= 1058)
		{
			switch(find._sceneId){
				case 1052:
					find._npcId = 1;
					find._sceneId = 1001;
					break;
				case 1053:
					find._npcId = 2;
					find._sceneId = 1001;
					break;
				case 1054:
					find._npcId = 4;
					find._sceneId = 1001;
					break;
				case 1055:
					find._npcId = 6;
					find._sceneId = 1001;
					break;
				case 1056:
					find._npcId = 200;
					find._sceneId = 1002;
					break;
				case 1057:
					find._npcId = 201;
					find._sceneId = 1002;
					break;
				case 1058:
					find._npcId = 202;
					find._sceneId = 1002;
					break;
			}
			find._type = TaskType::EXIT;
		}
	}
	else if(mapId != find._sceneId)
	{
		find._isShowWorldMap = false;
	}
	return find;*/
}

FindVo MapManage::nextFindVo()
{
	return _nextFindVo;
}