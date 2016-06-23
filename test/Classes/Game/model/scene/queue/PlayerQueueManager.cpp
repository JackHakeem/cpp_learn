#include "PlayerQueueManager.h"
#include "manager/GlobalManage.h"
#include "manager/RenderManage.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "model/player/vo/AccountInfoVo.h"
#include "model/player/RoleManage.h"

PlayerQueueManager::PlayerQueueManager()
{
	RenderManage::Instance()->add(this);
	_sceneProxy = (SceneProxy*)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
}

void PlayerQueueManager::step()
{
	if(!_sceneProxy)
		return;

	if(queue.size() > 0)
	{
		std::vector<PlayerBaseVo*>::iterator iter = queue.begin();
		if(iter != queue.end())
		{
			PlayerBaseVo* playerBaseVo = *iter;
			_sceneProxy->addPlayer(playerBaseVo);

			if(playerBaseVo)
			{
				std::map<int, PlayerBaseVo*>::iterator it = dic.find(playerBaseVo->accountId);
				if(it != dic.end())
					dic.erase(it);
			}

			queue.erase(iter);
		}
	}

	if(moveQueue.size() > 0)
	{
		std::vector<MoveObj>::iterator iter = moveQueue.begin();
		if(iter != moveQueue.end())
		{
			_sceneProxy->movePlayer(iter->accountId, &(iter->path));

			std::map<int, MoveObj>::iterator it = moveDic.find(iter->accountId);
			if(it != moveDic.end())
				moveDic.erase(it);

			moveQueue.erase(iter);
		}
	}
}

void PlayerQueueManager::addPlayer(PlayerBaseVo* playerBaseVo)
{
	if(!playerBaseVo)
		return;

	clearPlayerBaseVo(playerBaseVo->accountId);

	AccountInfoVo* info = RoleManage::Instance()->accountInfo();

	if(info && playerBaseVo->accountId == info->accountId)
	{
		if(_sceneProxy)
			_sceneProxy->addPlayer(playerBaseVo);
	}
	else if(g_pGlobalManage && (playerBaseVo->accountId == g_pGlobalManage->bFollowerId || playerBaseVo->accountId == g_pGlobalManage->followerId))
	{
		if(_sceneProxy)
			_sceneProxy->addPlayer(playerBaseVo);
	}
	else
	{
		dic[playerBaseVo->accountId] = playerBaseVo;
		queue.push_back(playerBaseVo);
	}
}

void PlayerQueueManager::removePlayer(int playerId)
{
	clearPlayerBaseVo(playerId);
	if(_sceneProxy)
		_sceneProxy->removePlayer(playerId);
}

void PlayerQueueManager::clearPlayerBaseVo(int playerId)
{
	std::map<int, PlayerBaseVo*>::iterator iter = dic.find(playerId);
	if(iter != dic.end())
	{
		std::vector<PlayerBaseVo*>::iterator it = queue.begin();
		for(; it != queue.end(); ++it)
		{
			if(*it == iter->second)
			{
				queue.erase(it);
				break;
			}
		}
		dic.erase(iter);
	}
}

void PlayerQueueManager::movePlayer(int accountId, std::vector<CCPoint>&path)
{
	AccountInfoVo* info = RoleManage::Instance()->accountInfo();

	if(info&& accountId == info->accountId)
	{
		if(_sceneProxy)
			_sceneProxy->movePlayer(accountId, &path);
	}
	else if(g_pGlobalManage && (accountId == g_pGlobalManage->bFollowerId || accountId == g_pGlobalManage->followerId))
	{
		if(_sceneProxy)
			_sceneProxy->movePlayer(accountId, &path);
	}
	else
	{
		MoveObj moveObj;
		moveObj.accountId = accountId;
		moveObj.path = path;
		moveDic[accountId] = moveObj;
		moveQueue.push_back(moveObj);
	}
}
void PlayerQueueManager::clearChangeScene()
{
	queue.clear();
	dic.clear();
	moveQueue.clear();
	moveDic.clear();
}