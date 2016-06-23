#include "model/scene/SceneProxy.h"
#include "util/TileUtil.h"
#include "model/player/RoleManage.h"
#include "view/scene/SceneMediator.h"
#include "vo/SceneType.h"
#include "vo/SceneConst.h"
#include "MonsterManager.h"
#include "model/scene/vo/GMProgessVo.h"
#include "model/scene/ExitManager.h"
#include "manager/SystemManage.h"
#include "utils/ColorUtil.h"
#include "manager/GlobalManage.h"
#include "vo/SceneVo.h"
#include "SceneManager.h"
#include "../battle/FightProxy.h"
#include "view/mainUI/MainUIMediator.h"

SceneProxy::SceneProxy():isLoadMap(false)
{
	_curSceneId = 0;
	_clickNPC = NULL;
	_sceneInfoVo = NULL;

	SystemManage::Instance()->addEventListener(SystemManage::SHOW_PLAYER_CHANGE, this, callfuncND_selector(SceneProxy::showPlayersHandler));
}

/**
	* @param value
	*/		
void SceneProxy::virtualPos(CCPoint value)
{
	if(_sceneInfoVo)
	{
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		if(_rolePos.x <= size.width / 2.0f)
		{
			_focusPos.x = _sceneInfoVo->width / 2.0f;
		}
		else if(_rolePos.x >= (_sceneInfoVo->width - size.width / 2.0f))
		{
			_focusPos.x = - _sceneInfoVo->width / 2.0f + size.width;
		}
		else
			_focusPos.x = - _rolePos.x + _sceneInfoVo->width / 2.0f + size.width / 2.0f;


		if(_rolePos.y < size.height / 2.0f)
		{
			_focusPos.y = - _sceneInfoVo->height / 2.0f + size.height;
		}
		else if(_rolePos.y > (_sceneInfoVo->height - size.height / 2.0f))
		{
			_focusPos.y = _sceneInfoVo->height / 2.0f;
		}
		else
		{
			_focusPos.y = - _sceneInfoVo->height / 2.0f + size.height / 2.0f + _rolePos.y;
		}

		focusPos(_focusPos);
	}
}

void SceneProxy::setSceneInfoVo(SceneInfoVo value, FindPath8& findPath8)
{
	if(!_sceneInfoVo)
		_sceneInfoVo = new SceneInfoVo();
	*_sceneInfoVo = value;
	_findPath = findPath8;
	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(!info)
		return;

	CCPoint pos = TileUtil::Instance()->changeTileToPixs(ccp(info->playerBaseInfo.x,info->playerBaseInfo.y));
	rolePos(pos);
	sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)_sceneInfoVo->name.c_str(), SceneMediator::BUILD_SCENE);
	isLoadMap = false;
	CCLog("-------------------after BUILD_SCENE: %d",  Timer::millisecondNow());
}


SceneInfoVo* SceneProxy::sceneInfoVo()
{
	return _sceneInfoVo;
}

int SceneProxy::pid()
{
	if(!_sceneInfoVo)
		return -1;

	if(_sceneInfoVo->pid==0)
		return _sceneInfoVo->id;
	else 
		return _sceneInfoVo->pid;
}

void SceneProxy::addNPC(NPCVo& value)
{
	if(_npcDic.find(value.id) == _npcDic.end())
		_npcDic.insert(make_pair(value.id, value));

	ccColor3B color = ColorUtil::getGoodColor(6); //REDCOLOR
	if(_progressDic.find(value.id) != _progressDic.end())
	{
		color = ColorUtil::getGoodColor(2);    //GREENHPCOLOR
	}

	if(_sceneInfoVo && _sceneInfoVo->type == SceneType::CITY)
	{
		if(value.action == SceneConst::WANDER)
		{
			color = ColorUtil::getGoodColor(5);       //ORANGECOLOR
			value._lev = getMonsterGroupLev(value.id);
		}
	}

	struct Data
	{
		ccColor3B color;
		NPCVo* npcVo; 
	};
	Data data;
	data.color = color;
	data.npcVo = &value;
	sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)(&data), SceneMediator::ADDNPC);
}


int SceneProxy::getMonsterGroupLev(int gmProgressID)
{
	int lev = 1;
	GMProgressVo* gmProgressVo = MonsterManager::Instance()->getGroupMonsterById(gmProgressID);
	NPCVo* monsterGroupNPCVo = NULL;
	if(gmProgressVo)
	{
		monsterGroupNPCVo = MonsterManager::Instance()->getMonsterGroup(gmProgressVo->mgId);
		if(monsterGroupNPCVo)
			lev = monsterGroupNPCVo->_lev;
	}
	return lev;
}

/**
* 
* @param id
* 
*/		
void SceneProxy::removeNPC(int id)
{
	std::map<int, NPCVo>::iterator iter= _npcDic.find(id);
	_npcDic.erase(iter);
	sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)(&id), SceneMediator::REMOVENPC);
	//sendNotification(Facade_Mediator, AppFacade_SMALLMAP_MEDIATOR, (char*)(&id), SceneMediator::REMOVE_NPC_HANDLER);
}

NPCVo* SceneProxy::getNPC(int id)
{
	std::map<int, NPCVo>::iterator iter = _npcDic.find(id);
	if(iter == _npcDic.end())
		return NULL;
	
	return &(iter->second);
}

void SceneProxy::setClickNPC(int id)
{
	_clickNPC = getNPC(id);
}

NPCVo* SceneProxy::getClickNPC()
{
	return _clickNPC;
}

CCPoint SceneProxy::getNPCPos(int id)
{
	NPCVo* npc = getNPC(id);
	CCPoint pos;
	if(npc)
	{
		pos.x = (float)(npc->x);
		pos.y = (float)(npc->y);
	}
	return pos;
}

void SceneProxy::setNPCPos(int id, CCPoint pos)
{
	NPCVo* npc = getNPC(id);
	if(npc)
	{
		npc->x = pos.x;
		npc->y = pos.y;
	}
}

void SceneProxy::movePlayer(int id, std::vector<CCPoint>* path)
{
	struct Data
	{
		int id;
		std::vector<CCPoint>* path;
	};
	Data data;
	data.id = id;
	data.path = path;
	sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)(&data), SceneMediator::MOVEPLAYER);
}

void SceneProxy::moveTradePlayer(int id, std::vector<CCPoint>* path)
{
	struct Data
	{
		int id;
		std::vector<CCPoint>* path;
	};
	Data data;
	data.id = id;
	data.path = path;
	sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)(&data), SceneMediator::MOVETRADEPLAYER);
}

void SceneProxy::movePlayerAdjust(int id, std::vector<CCPoint>* path, float ranger)
{
	struct Data
	{
		int id;
		float ranger;
		std::vector<CCPoint>* path;
	};

	Data data;
	data.id = id;
	data.ranger = ranger;
	data.path = path;
	sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)(&data), SceneMediator::MOVEPLAYERADJUST);
}

void SceneProxy::addPlayer(PlayerBaseVo* playerVo)
{
	if(!playerVo)
		return;

	addPlayerHander(playerVo);
	/*
	std::map<int, PlayerBaseVo>::iterator iter = _waitAddDic.find(playerVo->accountId);
	if(iter != _waitAddDic.end())
	{
		std::vector<PlayerBaseVo>::iterator it = _waitAddPlayers.begin();
		for(; it != _waitAddPlayers.end(); ++it)
		{
			if(iter->second.accountId == it->accountId)
			{
				_waitAddPlayers.erase(it);
				break;
			}
		}
	}

	if(playerVo->accountId == g_pGlobalManage->bFollowerId || playerVo->accountId== g_pGlobalManage->followerId)
	{
		addPlayerHander(playerVo);
	}
	else
	{
		if(iter != _waitAddDic.end())
		{
			_waitAddDic.erase(iter);
		}
		_waitAddDic.insert(make_pair(playerVo->accountId, *playerVo));
		_waitAddPlayers.push_back(*playerVo);
	}
	*/
}

void SceneProxy::addTradePalyer(PlayerBaseVo* playerVo)
{
	if(!playerVo)
		return;

	if( SystemManage::Instance()->showPlayers() == false && _sceneInfoVo->type != SceneType::COPY) 
		return;
	
	sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)playerVo, SceneMediator::ADDPTRADELAYER);

}

void SceneProxy::addPlayerHander(PlayerBaseVo* playerVo)
{
	if(!playerVo)
		return;

	//std::map<int, PlayerBaseVo>::iterator iter = _playerDic.find(playerVo->accountId);
	//if(iter != _playerDic.end())
	//	return;

	_playerDic.insert(make_pair(playerVo->accountId, *playerVo));

	//_playerDic[playerVo->accountId] = *playerVo;

	AccountInfoVo* info = RoleManage::Instance()->accountInfo();
	if(info && playerVo->accountId == info->accountId)
	{
		sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, NULL, SceneMediator::ADDROLE);
	}
	else
	{
		if( SystemManage::Instance()->showPlayers() == false && _sceneInfoVo->type != SceneType::COPY) 
			return;

		sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)playerVo, SceneMediator::ADDPLAYER);
	}
}


/**
* 
* @param id
* 
*/		
void SceneProxy::removePlayer(int id)
{
	removePlayerHandler(id);

	/*_waitRemovePlayers.push_back(id);
	
	std::map<int, PlayerBaseVo>::iterator iter = _waitAddDic.find(id);
	if(iter != _waitAddDic.end())
	{
		std::vector<PlayerBaseVo>::iterator it = _waitAddPlayers.begin();
		for(; it != _waitAddPlayers.end(); ++it)
		{
			if(iter->second.accountId == it->accountId)
			_waitAddPlayers.erase(it);
			_waitAddDic.erase(iter);
		}
	}*/
}

void SceneProxy::removeTradePlayer(int id)
{
	sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)(&id), SceneMediator::REMOVETRADERPLAYER);
}
		
void SceneProxy::removePlayerHandler(int id)
{
	std::map<int, PlayerBaseVo>::iterator iter = _playerDic.find(id);
	if(iter != _playerDic.end())
	{
		_playerDic.erase(iter); //here got an error - edwardliu
		sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)(&id), SceneMediator::REMOVEPLAYER);
	}
}

/**
* 
* @param id
* @return 
* 
*/		
PlayerBaseVo* SceneProxy::getPlayer(int id)
{
	std::map<int, PlayerBaseVo>::iterator iter = _playerDic.find(id);
	if(iter == _playerDic.end())
		return NULL;
	
	return &(iter->second);
}



void SceneProxy::addElement(ExitVo* exitVo)
{
	if(!exitVo)
		return;

	/*bool isUpdate = false;
	if(exitVo->otherInfos.size()>=2)
	{
		int preId = exitVo->otherInfos[1];
		std::map<int, ExitVo>::iterator iter = _elementDic.find(preId);
		if(iter != _elementDic.end())
		{
			_elementDic.erase(iter);
			struct Data
			{
				int id;
				ExitVo* exitVo;
			};
			Data data;
			data.id = preId;
			data.exitVo = exitVo;
			sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)(&data), SceneMediator::UPDATEEXIT);
			isUpdate = true;
		}
	}
	if(!isUpdate)
	{
		sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)(exitVo), SceneMediator::ADDEXIT);
	}*/
	//erased and add the sendnotification - edwardliu
	sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)exitVo, SceneMediator::ADDEXIT);
	std::map<int, ExitVo>::iterator it = _elementDic.find(exitVo->id());
	if(it != _elementDic.end())
		_elementDic.erase(it);

	_elementDic.insert(make_pair(exitVo->id(), *exitVo));
}

void SceneProxy::removeElement(int id)
{
	std::map<int, ExitVo>::iterator it = _elementDic.find(id);
	if(it != _elementDic.end())
		_elementDic.erase(it);
	sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)(&id), SceneMediator::REMOVEEXIT);

}

ExitVo* SceneProxy::getElement(int id)
{
	std::map<int, ExitVo>::iterator iter = _elementDic.find(id);
	if(iter == _elementDic.end())
		return NULL;

	return &(iter->second);
}

/**
	* set other player position
	* @param id
	* @param pos
	* @return 
	* 
	*/		
void SceneProxy::setOtherPlayerPos(int id, CCPoint pos)
{
	std::map<int, PlayerBaseVo>::iterator iter = _playerDic.find(id);

	if(iter != _playerDic.end())
	{
		iter->second.x = pos.x;
		iter->second.y = pos.y;
	}
}

CCPoint SceneProxy::getOtherPlayerPos(int id)
{
	std::map<int, PlayerBaseVo>::iterator iter = _playerDic.find(id);

	if(iter != _playerDic.end())
	{
		return ccp(iter->second.x, iter->second.y);
	}

	CCPoint pos(0.0f, 0.0f);
	return pos;
}

std::vector<CCPoint> SceneProxy::findPath(CCPoint startPoint, CCPoint endPoint)
{
	//CCLog("start point:(%f, %f), end point:(%f, %f)", startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	point ps;
	point pe;
	ps.x = startPoint.x;
	ps.y = startPoint.y;
	pe.x = endPoint.x;
	pe.y = endPoint.y;
	std::vector<CCPoint> retPath;
	if(startPoint.x < 0 || startPoint.y < 0 || endPoint.x < 0 || endPoint.y < 0)
		return retPath;

	std::vector<point>path;
	std::vector<point>opt_path;
	_findPath.find(ps, pe, path);
	_findPath.optimizePath(opt_path);

	
	std::vector<point>::iterator iter = opt_path.begin();
	for(; iter != opt_path.end(); ++iter)
	{
		retPath.push_back(ccp(float(iter->x), float(iter->y)));
		CCLog("path :(%d, %d)", iter->x, iter->y);
	}
	return retPath;
}

void SceneProxy::addRole()
{
	PlayerInfoVo* info= RoleManage::Instance()->roleInfo();
	if(info)
		addPlayerHander(&(info->playerBaseInfo));
}


/**
* 
* @param obj 
* 
*/		
void SceneProxy::initSceneProgress(SCMD123* data)
{
	if(!data)
		return;

	//this._sceneProgress = new Dictionary;
			
	int duplicate1 = 0;//Recent copy of the open id
	int duplicate2 = 0;//Recent copy of the open id
			
	//Map state: 0 not customs clearance, 1 already customs clearance, 2 has perfect, 3 all perfect
	std::vector<SCMD123Node>::iterator iter = data->a_openMap.begin();
	for(; iter != data->a_openMap.end(); ++iter)
	{
		_sceneProgress.insert(make_pair(iter->a_mapId, iter->b_status));
		if(iter->a_mapId < 1052)
		{
			continue;
		}
		if(iter->a_mapId < 1200 && _curSceneId < iter->a_mapId)
		{
			_curSceneId = iter->a_mapId;
		} 
		if(iter->a_mapId > 1200 && duplicate2 < iter->a_mapId)
		{
			duplicate1 = duplicate2;
			duplicate2 = iter->a_mapId;
		}
	}
	if(duplicate1 != 0)
	{
		_curDuplicates.push_back(duplicate1);
	}
	if(duplicate2 != 0)
	{
		_curDuplicates.push_back(duplicate2);
	}
}

/**
* Add scene progress
* @param obj
* 
*/		
void SceneProxy::addSceneProgress(SCMD123* data)
{
	if(!data)
		return;

	
	std::vector<SCMD123Node>::iterator iter = data->a_openMap.begin();
	for(; iter != data->a_openMap.end(); ++iter)
	{
		// Asked whether the current map there has not yet been account opened exit point
		PlayerInfoVo* playerInfovo = RoleManage::Instance()->roleInfo();
		if(!playerInfovo)
			break;
		std::vector<ExitVo*> exitVo = ExitManager::Instance()->getNotOpenExitByMapId(playerInfovo->playerBaseInfo._mapId);

		for(std::vector<ExitVo*>::iterator it = exitVo.begin(); it != exitVo.end(); ++it)
		{
			if((*it) && (*it)->otherInfos[0] == iter->a_mapId)
			{
				ExitManager::Instance()->removeNotOpenExit((*it)->id());
				addElement((*it));
			}
		}

		
		std::map<int/*map_id*/, int/*status*/>::iterator sPIter = _sceneProgress.find(iter->a_mapId);
		if (sPIter != _sceneProgress.end())
		{//change the old data
			sPIter->second = iter->b_status;
		}
		else
		{
			//addnew
			_sceneProgress.insert(make_pair(iter->a_mapId, iter->b_status));
		}
	}
	if(_sceneInfoVo && _sceneInfoVo->type != SceneType::CITY)
	{
		//sendNotification(MainUIMediator.STARTUP_REPORT_UI, _sceneInfoVo.id);
	}

	// LH20121113
	/*
	iter--;
	SceneVo* vo = SceneManager::Instance()->getSceneDic(iter->a_mapId);
	if(vo && vo->type == SceneType::COPY)
	{
		//sendNotification(MainUIMediator.SET_CONVEY_HIGHLIGHT,true);
	}
	*/
}

/**
	* 
	* To set the current map progress, including a strange progress, the progress
	*/		
void SceneProxy::initProgress(SCMD11D* cmd)
{
	if(!cmd || !_sceneInfoVo)
		return;
	//If is the current map, the initial progress
	if(cmd->a_mapId == _sceneInfoVo->id)
	{
		_progressDic.clear();

		std::vector<SCMD11DNode>::iterator iter = cmd->d_finisheds.begin();
		for(; iter != cmd->d_finisheds.end(); ++iter)
		{
			_progressDic.insert(make_pair(iter->a_process, 1));
		}

		if(cmd->e_randMg.size() > 0)
		{
			shootDic.clear();
			std::vector<SCMD11DNode2>::iterator iter = cmd->e_randMg.begin();
			for(; iter != cmd->e_randMg.end(); ++iter)
			{
				shootDic.insert(make_pair(iter->mgId, 1));
			}
		}
		//Whether tip perfect customs clearance rewards
		bool hasAward = false;

		if(cmd->b_mapStatus == 3 && cmd->c_isAward != 1)
			hasAward = true;

		/*if(ViewManager::getInstance()->secNavigate)
		{
			ViewManager.getInstance()->secNavigate.hasMapAward(hasAward);
		}*/
	}
}

CCPoint SceneProxy::rolePos()
{
	return _rolePos;
}

/**
* @param value pixel
*/
void SceneProxy::rolePos(CCPoint value)
{
	/*if(value.x == 0.0f && value.y == 0.0f)
	{
		_rolePos = value;
		return;
	}*/

	//float dis = (_rolePos.x - value.x) * (_rolePos.x - value.x) + (_rolePos.y - value.y) * (_rolePos.y - value.y);
	//if(dis != 0.0f)
	//{
		_rolePos = value;
		if(!isLoadMap)
			sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, NULL, SceneMediator::ROLE_POS_CHANGE);

		if(_sceneInfoVo)
		{
			CCSize size = CCDirector::sharedDirector()->getWinSize();
			
			if(_rolePos.x <= size.width / 2.0f)
			{
				_focusPos.x = _sceneInfoVo->width / 2.0f;
			}
			else if(_rolePos.x >= (_sceneInfoVo->width - size.width / 2.0f))
			{
				_focusPos.x = - _sceneInfoVo->width / 2.0f + size.width;
			}
			else
				_focusPos.x = - _rolePos.x + _sceneInfoVo->width / 2.0f + size.width / 2.0f;


			if(_rolePos.y < size.height / 2.0f)
			{
				_focusPos.y = - _sceneInfoVo->height / 2.0f + size.height;
			}
			else if(_rolePos.y > (_sceneInfoVo->height - size.height / 2.0f))
			{
				_focusPos.y = _sceneInfoVo->height / 2.0f;
			}
			else
			{
				_focusPos.y = - _sceneInfoVo->height / 2.0f + size.height / 2.0f + _rolePos.y;
			}
			focusPos(_focusPos);
		}
	//}
}

CCPoint SceneProxy::focusPos()
{
	return _focusPos;
}

void SceneProxy::focusPos(CCPoint value)
{
	_focusPos = value;
	if(!isLoadMap)
		sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, NULL, SceneMediator::FOCUS_POS_CHANGE);
}

/**
* 
* @param value
* @return 
* 
*/		
int SceneProxy::checkTilePoint(CCPoint point)
{
	if(!_sceneInfoVo)
		return -1;

	int i = point.y;
	int j = point.x;
    if(i < 0) i = 0;
    if(j < 0) j = 0;
	return _sceneInfoVo->mapData[i][j];

}

/**
* 
* 
*/
CCPoint SceneProxy::findMinEndPoint(CCPoint endPoint)
{
	CCPoint p = ccp(-1.0f, -1.0f);
	if(!_sceneInfoVo)
		return p;

	int x = endPoint.x;
	int y = endPoint.y;
	//int _w =  _sceneInfoVo->mapData[0].length;
	//int _h = _sceneInfoVo->mapData.length;
	int _w = MAX_CELLS_X;
	int _h = MAX_CELLS_Y;

	int i = 3;
	while(true)
	{
		int k = i;
		int v = i / 2;
		for(int j = 0; j < 4; ++j)
		{
			int vx = 0;
			int vy = 0;
			for(int z = 0; z < k; ++z)
			{
				if(j == 0)
				{
					vx = x - v;
					vy = y - v + z;
				}
				else if(j == 1)
				{
					vx = x - v + 1 + z;
					vy = y + v;
				}
				else if(j == 2)
				{
					vx = x + v;
					vy = y - v  + z;
				}
				else if(j == 3)
				{
					vx = x - v + 1 + z ;
					vy = y - v;
				}
				if(j % 2 == 0 && (vx < 0 || vx  > _w - 1))
				{
					break;
				}
				else if(j % 2 == 1 && (vy < 0 || vy  > _h - 1))
				{
					break;
				}
				if(vx < 0 || vx  > _w - 1  || vy < 0 || vy  > _h - 1)
					continue;
				if(_sceneInfoVo->mapData[vy][vx] == 0 || _sceneInfoVo->mapData[vy][vx] == 2)
				{
					return ccp(vx,vy);
				}
			}
			if(j!=1)
				k--;
		}
		i+=2;
		if(i>15)
			break;
	}
	return ccp(-1.0f, -1.0f);
}

/**
	* set display other players
	* @param event
	* 
	*/
void SceneProxy::showPlayersHandler()
{
			
	if(_sceneInfoVo && _sceneInfoVo->type != SceneType::CITY)
	{ 
		// only in city
		return;   
	}

	AccountInfoVo* info = NULL;
	if(SystemManage::Instance()->showPlayers())
	{
		std::map<int, PlayerBaseVo>::iterator iter = _playerDic.begin();
		for(; iter != _playerDic.end(); ++iter)
		{
			info = RoleManage::Instance()->accountInfo();
			if(info)
			{
				if(iter->first == info->accountId )
					continue;
				sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)(&(iter->second)), SceneMediator::ADDPLAYER);
			}
 		}
				
	}
	else
	{
		std::map<int, PlayerBaseVo>::iterator iter = _playerDic.begin();
		for(; iter != _playerDic.end(); ++iter)
		{
			info = RoleManage::Instance()->accountInfo();
			if(info)
			{
				if(iter->first == info->accountId )
					continue;
				int accountId = iter->second.accountId;
				sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)(&accountId), SceneMediator::REMOVEPLAYER);
			}
		}
	} 
}

//void SceneProxy::step()
//{
//	int addNum = _waitAddPlayers.size() > 8 ? 8 : _waitAddPlayers.size(); 
//	if(_waitAddPlayers.size() > 0)
//	{
//		std::vector<PlayerBaseVo>::iterator iter;
//		std::map<int, PlayerBaseVo>::iterator iter1;
//		while(addNum>0)
//		{
//			iter = _waitAddPlayers.begin();
//
//			if(iter == _waitAddPlayers.end())
//				break;
//
//			addPlayerHander(&(*iter));
//			iter1 = _waitAddDic.find(iter->accountId);
//			_waitAddDic.erase(iter1);
//			addNum--;
//		}
//	}
//
//	int remNum = _waitRemovePlayers.size() > 8 ? 8 : _waitRemovePlayers.size();
//	if(_waitRemovePlayers.size() > 0)
//	{
//		std::vector<int>::iterator iter;
//		while(remNum>0)
//		{
//			iter = _waitRemovePlayers.begin();
//			if(iter == _waitRemovePlayers.end())
//				break;
//
//			//removePlayerHandler(*iter);
//			remNum--;
//		}
//	}
//}


bool SceneProxy::isInProgress(int progressId)
{
	std::map<int, int>::iterator iter = _progressDic.find(progressId);
	if(iter != _progressDic.end())
		return true;

	return false;
}


std::vector<int> SceneProxy::maptotalProgress()
{
	std::vector<int> arr;

	for(std::map<int, int>::iterator iter = _progressDic.begin();
		iter != _progressDic.end(); ++iter)
	{
		arr.push_back(iter->second);
	}
	return arr;
}

/**
	* 
	* 
	*/
void SceneProxy::addProgress(SCMD120* cmd)
{
	int _p = cmd->b_process;
	std::map<int, int>::iterator iter = _progressDic.find(_p);
	if(iter != _progressDic.end())
	{
		iter->second = 1;
	}
	else
	{
		_progressDic.insert(make_pair(_p, 1));
	}

	if(_sceneInfoVo->type == SceneType::STORY)
	{
		sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)(&_p), SceneMediator::REMOVENPC);
	}
	else if(_sceneInfoVo->type == SceneType::COPY)
	{
		sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)(&_p), SceneMediator::REMOVENPC);
	}
	else if (_sceneInfoVo->type == SceneType::CITY)
	{
	}
	else if (_sceneInfoVo->type == SceneType::WORLD_BOSS)
	{
	}
}

void SceneProxy::setSceneThrough(int id)
{
	std::map<int, int>::iterator iter = _sceneProgress.find(id);
	if(iter != _sceneProgress.end())
		iter->second = 1;
}

bool SceneProxy::isSceneOpened(int id)
{
	std::map<int, int>::iterator iter = _sceneProgress.find(id);
	if(iter != _sceneProgress.end())
		return true;

	return false;
}

/**
*status: 0 not pass, 1 passed, 2 perfect, 3 all perfect
* @param id
* @return 
* 
*/		
int SceneProxy::getSceneStatus(int id)
{
	std::map<int, int>::iterator iter = _sceneProgress.find(id);
	if(iter != _sceneProgress.end())
		return iter->second;

	return -1;
}

void SceneProxy::dispose()
{
	if(_sceneInfoVo)
		delete _sceneInfoVo;

	_sceneInfoVo = NULL;

	_npcDic.clear();
	_playerDic.clear();
	_elementDic.clear();
	_progressDic.clear();

	_waitAddPlayers.clear();
	_waitAddDic.clear();
	_waitRemovePlayers.clear();
}

std::map<int, int>* SceneProxy::sceneProgress()
{
	return &_sceneProgress;
}

std::vector<int>* SceneProxy::curDuplicates()
{
	return &_curDuplicates;
}

int SceneProxy::curSceneId()
{
	return _curSceneId;
}