#include "SceneProxyCommand.h"
#include "mvc/Facade.h"
#include "../AppFacade.h"
#include "socket/command/s11/SCMD11D.h"
#include "socket/command/s12/SCMD123.h"
#include "model/scene/vo/SceneVo.h"
#include "model/scene/SceneManager.h"
#include "socket/command/s12/SCMD120.h"
#include "socket/command/s11/SCMD111.h"
#include "util/TileUtil.h"
#include "socket/command/s11/SCMD112.h"
#include "model/player/vo/AccountInfoVo.h"
#include "model/player/RoleManage.h"
#include "model/player/ClothManage.h"
#include "model/player/FigureBaseManage.h"
#include "socket/command/s11/SCMD113.h"
#include "model/scene/vo/SceneType.h"
#include "socket/command/s11/SCMD118.h"
#include "view/scene/SceneMediator.h"
#include "model/scene/ExitManager.h"
#include "model/scene/NPCManager.h"
#include "model/scene/MonsterManager.h"
#include "view/scene/SceneWorldMediator.h"
#include "SceneCommand.h"
#include "manager/GlobalManage.h"
#include "../wordBoss/WorldBossCmd.h"
#include "view/mainUI/MainUIMediator.h"
#include "socket/command/s12/SCMD12D.h"
#include "socket/command/c12/CCMD12C.h"
#include "model/trader/TraderProxy.h"
#include "socket/command/s0f/SCMD0F2.h"
#include "socket/command/s0f/SCMD0F1.h"

SceneProxyCommand::SceneProxyCommand()
{
	_sceneProxy = NULL;
}

void SceneProxyCommand::execute(int32 command, char* data)
{
	if(!g_pFacade)
		return;

	_sceneProxy = (SceneProxy*)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);

	switch(command)
	{
		case ROLE_POS_CHANGE:
			{
				if(!data)
					break;

				CCPoint* p = (CCPoint*)data;
				if(_sceneProxy)
					_sceneProxy->rolePos(ccp(p->x, p->y));
				break;
			}
		case MOVE_PLAYER:
			movePlayer(data);
			break;
		case MOVE_TRADEPLAYER:
			moveTradePlayer(data);
			break;
		case ADD_PLAYER:
			addPlayers(data);
			break;
		case ADD_TRADEPLAYER:
			addTrader(data);
			break;
		case CREAT_TRADEPLAYER:
			creatTrader(data);
			break;
		case REMOVE_TRADEPLAYER:
			removeTradePlayer(data);
			break;
		case REMOVE_PLAYER:
			removePlayer(data);
			break;
		case REMOVE_NPC:
			{
				if(!data)
					break;

				int id = ((int*)data)[0];
				if(_sceneProxy)
					_sceneProxy->removeNPC(id);
				break;
			}
		case MAP_SKIP:
			mapSkip(data);
			break;
		case INIT_PROCESS:
			{
				if(!data)
					break;

				SCMD11D* scmd11d = (SCMD11D*)data;

				if(_sceneProxy && _sceneProxy->_sceneInfoVo
					&& _sceneProxy->_sceneInfoVo->id == scmd11d->a_mapId)
				{
					_sceneProxy->initProgress(scmd11d);
					addRoleSElement();
				}
				setPerfectInfo(scmd11d);
				break;
			}
		case ADD_PROCESS:
			{
				SCMD120* scmd120 = (SCMD120*)data;
				if(_sceneProxy)
					_sceneProxy->addProgress(scmd120);
				break;
			}
		case INIT_SCENE_PROCESS:
			{
				SCMD123* scmd123 = (SCMD123*)data;
				if(_sceneProxy)
					_sceneProxy->initSceneProgress(scmd123);
				break;
			}
		case ADD_SCENE_PROCESS:
			{
				if(_sceneProxy)
					_sceneProxy->addSceneProgress((SCMD123*)data);
				break;
			}
	}
}

/**
*Set up perfect degrees map data
* @param cmd
* 
*/	

void SceneProxyCommand::setPerfectInfo(SCMD11D* cmd)
{
	if(!cmd)
		return;

	SceneVo* sceneVo = SceneManager::Instance()->getSceneDic(cmd->a_mapId);
	if(!sceneVo)
		return;

	if(_sceneProxy && (sceneVo->pid ==_sceneProxy->pid() || sceneVo->id==_sceneProxy->pid()))
	{
		//PerfectManager.getInstance().resetCurMapInfo(_sceneProxy->pid(), cmd->b_mapStatus == 3, cmd->c_isAward == 1);
	}
	/*PerfectManager.getInstance().initProgressLev(cmd->a_mapId, cmd->d_finisheds);
	sendNotification(ReportMediator::INIT_PROGRESS, cmd->a_mapId);
	sendNotification(SceneWorldMediator::INIT_PROGRESS, cmd->a_mapId);*/

	if(!g_pFacade)
		return;

	SceneWorldMediator* m = (SceneWorldMediator*)g_pFacade->retrieveMediator(AppFacade_SCENEWORLD_MEDIATOR);
	if(m)
		m->handleNotification(SceneWorldMediator::INIT_PROGRESS, (char*)(&(cmd->a_mapId)));
}

void SceneProxyCommand::movePlayer(char* data)
{
	if(!data)
		return;

	SCMD111* playerMove = (SCMD111*)data;
	if(!playerMove)
		return;

	std::vector<CCPoint> path;
	path.push_back(TileUtil::Instance()->changeTileToPixs(ccp(float(playerMove->b_startX), float(playerMove->c_startY))));
	for(int i = 0; i< playerMove->d_path.size(); i++)
	{
		SCMD111Node _SCMD111Node = playerMove->d_path[i];
		path.push_back(TileUtil::Instance()->changeTileToPixs(ccp(float(_SCMD111Node.a_x), float(_SCMD111Node.b_y))));
	}

	//if(_teamProxy->followerId == playerMove->a_AccountId)
	//{ // He is the PlayerMove is the team players
	//	this.sendNotification(SceneMediator.ROLE_MOVE_PATH,{ranger:80,path:path});
	//}
	//else if(_teamProxy.bFollowerId == playerMove.a_AccountId){ //
	//	_sceneProxy.movePlayerAdjust(playerMove.a_AccountId, path, 80);
	//	return;
	//}
	//PlayerQueueManager::Instance()->movePlayer(playerMove->a_AccountId, path);
	if(_sceneProxy)
		_sceneProxy->movePlayer(playerMove->a_AccountId, &path);
}

void SceneProxyCommand::addPlayers(char* data)
{
	if(!data)
		return;

	SCMD112* players = (SCMD112*)data;
	if(!players)
		return;

	std::vector<SCMD112Node>::iterator iter = players->a_Accounts.begin();
	for(; iter != players->a_Accounts.end(); ++iter)
	{
		AccountInfoVo *acc = RoleManage::Instance()->accountInfo();
		if(!acc)
			continue;

		if(iter->a_AccountId == acc->accountId)
			continue;

		PlayerBaseVo playerVo;
		playerVo.accountId = iter->a_AccountId;
		playerVo.name = iter->b_RoleName;
		playerVo.x = iter->c_x;
		playerVo.y =  iter->d_y;
		playerVo._guildName = iter->e_guildName;
		playerVo._maxHp = iter->f_maxHp;
		playerVo._hp = iter->g_hp;
		playerVo.energy = iter->h_energy;
		playerVo.mercId = iter->i_mercId;
		playerVo._lev = iter->j_roleLev;
		playerVo.threat = iter->m_weiXie;
		playerVo._titleId = iter->n_title;

		int avatar = int(iter->k_avatar);
		//if(avatar == 1)
		//	playerVo.cloth = ClothManage::Instance()->RES_ID_ONBUSINESS;	// 1 run business image
		//else
		if(avatar == 2)
			playerVo.cloth = ClothManage::Instance()->RES_ID_ONMEDITATION;	//2 meditation image
		else
		{	//0 Normal role image
			FigureCfgBaseVo* mercVo = FigureBaseManage::Instance()->getMercBase(iter->i_mercId);
			if(mercVo)
				playerVo.cloth = mercVo->cloth;//mercVo->mercId	Jae commond
		}
		/*===================Add people to move the path=======================*/
		if(iter->l_path.size() > 0)
		{
			SCMD111 movePath;
			movePath.a_AccountId = iter->a_AccountId;
			movePath.b_startX = iter->c_x;
			movePath.c_startY = iter->d_y;
			movePath.d_path = iter->l_path;
			playerVo.path = movePath;
		}
		/*====================================================*/
		//PlayerQueueManager::Instance()->addPlayer(&playerVo);
		if(_sceneProxy)
			_sceneProxy->addPlayer(&playerVo);
	}
}

void SceneProxyCommand::removePlayer(char* data)
{
	if(!data)
		return;
	SCMD113* players = (SCMD113*)data;
	if(!players)
		return;

	if(!_sceneProxy)
		return;

	std::vector<SCMD113Node>::iterator iter = players->a_Accounts.begin();
	for(; iter != players->a_Accounts.end(); ++iter)
	{

		// special handle for World Boss crash BUG
		// by LONGHUI 20120925
		if (iter->a_AccountId == RoleManage::Instance()->accountInfo()->accountId)
		{
			// WorldBoss
			int curMapID = RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId;
			if (curMapID == 1208) // WorldBoss
			{
				continue;
			}
			// other system
			// continue?
		}
		

		//PlayerQueueManager::Instance()->removePlayer(iter->a_AccountId);
		_sceneProxy->removePlayer(iter->a_AccountId);

	}
}

void SceneProxyCommand::addRoleSElement()
{
	if(!_sceneProxy)
		return;

	//Add leading role
	_sceneProxy->addRole();
	//Add NPC
	addNPCs();
	//Add monsters
	addMonsters();
	// initial progress
	// add exit point
	addExit();

	addTraders();
	
	////this.sendNotification(ArenaMediator.REQ_RING_DATA);
	////A layer of the next layer button
	//SceneInfoVo* sceneInfoVo = _sceneProxy->sceneInfoVo();
	//if(!sceneInfoVo)
	//	return;

}

void SceneProxyCommand::mapSkip(char* data)
{
	if(!data)
		return;

	SCMD118* params = (SCMD118*)data;
	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(!info)
		return;

	info->playerBaseInfo._mapId = params->a_mapId;
	info->playerBaseInfo.x = params->b_startX;
	info->playerBaseInfo.y = params->c_startY;

	if(!g_pFacade)
		return;

	CCLog("--------------change scene");
	g_pGlobalManage->IsChangeScene( true );//jae

	// show all UI
	g_pGlobalManage->showAllUI(true); // add by L.H. 0704

	SceneMediator* m = (SceneMediator*)g_pFacade->retrieveMediator(AppFacade_SCENE_MEDIATOR);
	if(m)
		m->handleNotification(SceneMediator::STARTUP_GAME_SCENE, NULL);

	//add by edwardliu, logic changed by liangjie
	if(g_pFacade)
	{
		SceneCommand* cmd = (SceneCommand*)g_pFacade->retrieveController(AppFacade_SCENE_COMMAND);
		if(cmd)
		{
			cmd->setSceneInfo();
		}
	}
	//sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, NULL, SceneMediator::STARTUP_GAME_SCENE);
	//sendNotification(SceneMediator.STARTUP_GAME_SCENE);

	// World boss by LH 20120917
	int mapID = params->a_mapId;
	sendNotification(Facade_Command , AppFacade_WorldBoss_Command , (char *)&mapID , WorldBossCmd::MAP_SKIP);
}

void SceneProxyCommand::addNPCs()
{
	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(!info)
		return;

	std::vector<int> array = NPCManager::Instance()->getNpcsByMapId(info->playerBaseInfo._mapId);

	if(!_sceneProxy)
		return;

	DWORD d1 = Timer::millisecondNow();
	CCLog("-------------------loading NPC time begin: %d \n ,%f s",  d1, d1*0.001);
	for(std::vector<int>::iterator iter = array.begin();
		iter != array.end(); ++iter)
	{

		NPCVo* npcVo = NPCManager::Instance()->getNPC(*iter);
		if(!npcVo)
			continue;

		npcVo->speed = 150;
		if(npcVo->state != 1 && npcVo->state != 3) 
			npcVo->state =1;  //
		_sceneProxy->addNPC(*npcVo);
	}
	DWORD d2 = Timer::millisecondNow();
	CCLog("-------------------loading NPC time use: %d \n ,%f s", (d2-d1), (d2-d1)*0.001 );


}

void SceneProxyCommand::addMonsters()
{
	if(!_sceneProxy)
		return;

	SceneInfoVo* sinfo = _sceneProxy->sceneInfoVo();
	if(!sinfo)
		return;

	if(sinfo->type == SceneType::CITY)
		return; // Not the strange town monster as NPC processing

	std::list<GMProgressVo*> array = MonsterManager::Instance()->getGroupMonsterByMapId(sinfo->id);
	if(array.size() == 0)
		return;

	bool isHide = false; //Hidden have been strange
	if(sinfo->type == SceneType::COPY || sinfo->type == SceneType::WORLD_BOSS)
	{
		isHide = true;
	}
	else if(sinfo->type == SceneType::STORY)
	{
		isHide = _sceneProxy->getSceneStatus(sinfo->id) < 1;
	}

	std::vector<int> proIdArray;
	for(std::list<GMProgressVo*>::iterator iter = array.begin();
		iter != array.end(); ++iter)
	{
		if(!(*iter))
			continue;

		if(_sceneProxy->shootDic.find((*iter)->id) != _sceneProxy->shootDic.end())
		{
			continue;
		}

		if((*iter)->mgId == 0)
		{
			continue;
		}

		if(isHide && _sceneProxy->isInProgress((*iter)->id))
		{
			continue;
		}
		NPCVo* npcVo = MonsterManager::Instance()->getMonsterGroup((*iter)->mgId);
		if(!npcVo)
			continue;

		NPCVo newNPCVo;
		newNPCVo._lev = npcVo->_lev;
		newNPCVo._hp = npcVo->_hp;
		newNPCVo._resId = npcVo->_resId;
		newNPCVo.name = npcVo->name;
		newNPCVo.id = (*iter)->id;
		newNPCVo.action = SceneConst::FIGHT;
		newNPCVo.x = (*iter)->x;
		newNPCVo.y = (*iter)->y;
		newNPCVo.speed = 100;
		newNPCVo.otherInfos = (*iter)->id;
		newNPCVo._isMonster = true;
		//jae 20120802 add npc mapId for talk
		newNPCVo.setMapId( sinfo->id );
		_sceneProxy->addNPC(newNPCVo);
		proIdArray.push_back((*iter)->id);
	}
	_sceneProxy->shootDic.clear();
	//proIdArray
	if(isHide)
	{
		SceneMediator* m = (SceneMediator*)g_pFacade->retrieveMediator(AppFacade_SCENE_MEDIATOR);
		if(m)
			m->handleNotification(SceneMediator::INIT_RED_PROCESS_ID, (char*)(&proIdArray));
	}
}

void SceneProxyCommand::addExit()
{
	PlayerInfoVo* playerInfoVo = RoleManage::Instance()->roleInfo();
	if(!playerInfoVo)
		return;

	std::vector<int>* exits = ExitManager::Instance()->getExitsByMapId(playerInfoVo->playerBaseInfo._mapId);
	if(!exits)
		return;
	//exits.sort(Array.NUMERIC);
	for(std::vector<int>::iterator iter = exits->begin();
		iter != exits->end(); ++iter)
	{
		ExitVo* exitVo = ExitManager::Instance()->getExit(*iter);
		if(!exitVo)
			continue;

		if( exitVo->otherInfos[0] !=0 && !_sceneProxy->isSceneOpened(exitVo->otherInfos[0]))
		{
			ExitManager::Instance()->addNotOpenExit(exitVo);
			continue;
		}
		else
		{
			if(_sceneProxy)
				_sceneProxy->addElement(exitVo);
		}
		//if( exitVo->otherInfos[0] !=0 && !_sceneProxy->isSceneOpened(exitVo->otherInfos[0])) 
		//{  // Transfer target map has not been open
		//	ExitManager::Instance()->addNotOpenExit(exitVo);
		//	continue;  // 1 already open 2 has not yet open 0 map progress does not exist
		//}
		//else
		//{
		//	_sceneProxy->addElement(exitVo);
		//}
	}
}

void SceneProxyCommand::moveTradePlayer( char* data )
{
	if(!data)
		return;

	SCMD111* playerMove = (SCMD111*)data;
	if(!playerMove)
		return;

	std::vector<CCPoint> path;
	path.push_back(TileUtil::Instance()->changeTileToPixs(ccp(float(playerMove->b_startX),
		float(playerMove->c_startY))));
	for(int i = 0; i< playerMove->d_path.size(); i++)
	{
		SCMD111Node _SCMD111Node = playerMove->d_path[i];
		path.push_back(TileUtil::Instance()->changeTileToPixs(ccp(float(_SCMD111Node.a_x),
			float(_SCMD111Node.b_y))));
	}
	if(_sceneProxy)
		_sceneProxy->moveTradePlayer(playerMove->a_AccountId, &path);
}

void SceneProxyCommand::creatTrader( char* data )
{
	if(!data)
		return;

	SCMD0F1* players = (SCMD0F1*)data;
	if(!players)
		return;

	std::vector<SCMD0F1Node>::iterator iter = players->a_Accounts.begin();
	for(; iter != players->a_Accounts.end(); ++iter)
	{
		SCMD0F1Node node = *iter;
		AccountInfoVo *acc = RoleManage::Instance()->accountInfo();

		//if(node.a_AccountId == acc->accountId)
		//	return;

		PlayerBaseVo playerVo;
		playerVo.accountId = node.a_AccountId;
		playerVo.name = node.b_RoleName;
		playerVo.x = node.c_x;
		playerVo.y =  node.d_y;
		playerVo._guildName = node.e_guildName;
		playerVo._maxHp = node.f_maxHp;
		playerVo._hp = node.g_hp;
		playerVo.energy = node.h_energy;
		playerVo.mercId = node.i_mercId;
		playerVo._lev = node.j_roleLev;
		playerVo.threat = node.m_weiXie;
		playerVo._titleId = node.n_title;

		playerVo.cloth = ClothManage::Instance()->RES_ID_ONBUSINESS;	// 1 run business image
		playerVo.color = node.k_avatar;

		/*===================Add people to move the path=======================*/
		if(node.l_path.size() > 0)
		{
			SCMD111 movePath;
			movePath.a_AccountId = node.a_AccountId;
			movePath.b_startX = node.c_x;
			movePath.c_startY = node.d_y;
			movePath.d_path = node.l_path;
			playerVo.path = movePath;
		}
		/*====================================================*/
		if(_sceneProxy)
			_sceneProxy->addTradePalyer(&playerVo);
	}
}


void SceneProxyCommand::addTrader( char* data )
{
	if(!data)
		return;

	SCMD12D* players = (SCMD12D*)data;
	if(!players)
		return;

	//std::vector<SCMD112Node>::iterator iter = players->a_Accounts.begin();
	//for(; iter != players->a_Accounts.end(); ++iter)
	{
		AccountInfoVo *acc = RoleManage::Instance()->accountInfo();

		//if(players->a_node.a_AccountId == acc->accountId)
		//	return;

		PlayerBaseVo playerVo;
		playerVo.accountId = players->a_node.a_AccountId;
		playerVo.name = players->a_node.b_RoleName;
		playerVo.x = players->a_node.c_x;
		playerVo.y =  players->a_node.d_y;
		playerVo._guildName = players->a_node.e_guildName;
		playerVo._maxHp = players->a_node.f_maxHp;
		playerVo._hp = players->a_node.g_hp;
		playerVo.energy = players->a_node.h_energy;
		playerVo.mercId = players->a_node.i_mercId;
		playerVo._lev = players->a_node.j_roleLev;
		playerVo.threat = players->a_node.m_weiXie;
		playerVo._titleId = players->a_node.n_title;

		playerVo.cloth = ClothManage::Instance()->RES_ID_ONBUSINESS;	// 1 run business image
		playerVo.color = players->a_node.k_avatar;

		/*===================Add people to move the path=======================*/
		if(players->a_node.l_path.size() > 0)
		{
			SCMD111 movePath;
			movePath.a_AccountId = players->a_node.a_AccountId;
			movePath.b_startX = players->a_node.c_x;
			movePath.c_startY = players->a_node.d_y;
			movePath.d_path = players->a_node.l_path;
			playerVo.path = movePath;
		}
		/*====================================================*/
		if(_sceneProxy)
			_sceneProxy->addTradePalyer(&playerVo);
	}
}

void SceneProxyCommand::removeTradePlayer(char* data)
{
	if(!data)
		return;
	SCMD0F2* players = (SCMD0F2*)data;
	if(!players)
		return;

	if(!_sceneProxy)
		return;

	std::vector<SCMD0F2Node>::iterator iter = players->a_Accounts.begin();
	for(; iter != players->a_Accounts.end(); ++iter)
	{
		//if (iter->a_AccountId==RoleManage::Instance()->accountInfo()->accountId)
		//{
		//	continue;
		//}
		
		_sceneProxy->removeTradePlayer(iter->a_AccountId);
	}
}

void SceneProxyCommand::addTraders()
{
	if(!_sceneProxy)
		return;
	std::map<int, PlayerBaseVo>::iterator iter = _sceneProxy->_traderplayerDic.begin();
	for(; iter != _sceneProxy->_traderplayerDic.end(); ++iter)
	{
		_sceneProxy->addTradePalyer(&iter->second);
	}
	_sceneProxy->_traderplayerDic.clear();
}
