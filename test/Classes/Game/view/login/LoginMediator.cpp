 #include "LoginMediator.h"
#include "control/task/TaskProxyCommand.h"
#include "control/scene/SceneProxyCommand.h"
#include "../GameViewMediator.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "model/player/RoleManage.h"
#include "manager/GlobalManage.h"
#include "socket/command/c16/CCMD164.h"
#include "socket/command/c15/CCMD15F.h"
#include "socket/command/c35/CCMD351.h"
#include "socket/command/c31/CCMD317.h"
#include "socket/command/c30/CCMD307.h"
#include "socket/command/c30/CCMD308.h"
#include "control/figure/FigureCommand.h"
#include "socket/command/c12/CCMD122.h"
#include "BaseType.h"
#include "socket/command/c30/CCMD306.h"
#include "socket/command/c18/CCMD189.h"
#include "manager/CDManage.h"
#include "manager/TimerManage.h"
#include "events/GameDispatcher.h"
#include "control/backpack/BagProxyCommand.h"
#include "control/skill/SkillCommand.h"
#include "socket/command/c01/CCMD010.h"
#include "socket/command/c01/CCMD011.h"
#include "control/crystal/CrystalCommand.h"
#include "socket/network/GateServerSocket.h"
#include "socket/network/GameServerSocket.h"
#include "../vip/VipMediator.h"
#include "socket/command/c17/CCMD17E.h"

#include "model/scene/NPCManager.h"
#include "model/player/RoleManage.h"
#include "manager/SourceCacheManage.h"
#include "utils/ScaleUtil.h"
#include "Message.h"
#include "LoginManage.h"
#include "components/LoginView.h"
#include "manager/sound/SoundManager.h"
#include "model/train/vo/TrainManager.h"
#include "utils/loader/KKAnimationFactory.h"
#include "socket/command/c1a/CCMD1A0.h"
#include "model/mail/MailConst.h"
#include "socket/command/c1a/CCMD1AA.h"
#include "model/scene/MonsterManager.h"
#include "control/wordBoss/WorldBossCmd.h"
#include "socket/command/c14/CCMD141.h"
#include "socket/command/c3c/CCMD3C7.h"
#include "socket/command/c10/CCMD10F.h"
#include "socket/command/c42/CCMD420.h"
#include "socket/command/c1e/CCMD1E7.h"
#include "socket/command/c43/CCMD430.h"
#include "socket/command/c27/CCMD270.h"
#include "socket/command/c2b/CCMD2B0.h"
#include "model/trader/TraderProxy.h"

LoginMediator::LoginMediator()
{
	progress = 0;
	total = 3;

	GameDispatcher::getInstance()->addEventListener(GameDispatcher::GET_USER_INFO, this, callfuncND_selector(LoginMediator::getUserInfoHandler));
}

void LoginMediator::trialVipState( SCMD3C8 *pData )
{
	sendNotification(Facade_Mediator, AppFacade_VIP_MEDIATOR, (char *) pData, VipMediator::TRIAL_VIP_CHANGE);
	onLogin();
}


void LoginMediator::handleNotification(int M2Vcmd, char* data)
{
	switch(M2Vcmd)
	{
	case GETUSERINFO:
		//					getUserInfo();
		break;
	}
}

void LoginMediator::taskProcess(char *data)
{
	sendNotification(Facade_Command, AppFacade_TASK_COMMAND, data,TaskProxyCommand::INIT_FINISH_TASK_DATA);
}

void LoginMediator::taskAccept( char *data )
{
	sendNotification(Facade_Command, AppFacade_TASK_COMMAND, data,TaskProxyCommand::INIT_REC_TASK_DATA);
}

void LoginMediator::initScene( SCMD123* cmd ) //SCMD123
{
	sendNotification(Facade_Command, AppFacade_SCENEPROXY_COMMAND, (char*)cmd, SceneProxyCommand::INIT_SCENE_PROCESS);
	onLogin();
}

void LoginMediator::onLogin()
{
	progress++;
	//queueProgressHandler();

	//jaeno
	if ( progress == 1 ) // init role info after
	{
		//CCLog("------------------Loading Resource begin.");	// Jae

		//CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_RGBA4444 );
		//PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
		//if(!info)
		//	return;
		//std::vector<int> array = NPCManager::Instance()->getNpcsByMapId(info->playerBaseInfo._mapId);
		//if(!_sceneProxy)
		//	return;


		//DWORD d1 = Timer::millisecondNow();
		//CCLog("-------------------loading NPC Resource begin: %d");
		
		///////////npc begin
		//char _assetURL[128];
		//Begin Kenfly 20121106 : modify
		//for(std::vector<int>::iterator iter = array.begin();
		//	iter != array.end(); ++iter)
		//{
		//	NPCVo* npcVo = NPCManager::Instance()->getNPC(*iter);
		//	if(!npcVo)
		//		continue;

		//	sprintf( _assetURL, "assets/res/%d", npcVo->_resId);
		//	
		//	BitmapMovieClip* movieClip = NULL;
		//	if(  npcVo->_isMonster ||
		//		(npcVo->action==SceneConst::FIGHT) || (npcVo->action==SceneConst::STORY) )
		//	{
		//		movieClip = SourceCacheManage::Instance()->loadModel(
		//			_assetURL, npcVo->_resId, 0.2f, true, true);
		//	}
		//	else
		//	{
		//		movieClip = SourceCacheManage::Instance()->loadPvrNormal(
		//			_assetURL, npcVo->_resId, BitmapMovieClip::ACTION_STAND, npcVo->state, 0.2f, true, true);
		//	}
		//	if (movieClip)
		//	{
		//		movieClip->dispose(true);
		//	}
		//	CC_SAFE_DELETE( movieClip );

		//}
		////////npc end

		///////////////monster
		//std::list<GMProgressVo*> arrayMonster =
		//	MonsterManager::Instance()->getGroupMonsterByMapId(info->playerBaseInfo._mapId);

		//for(std::list<GMProgressVo*>::iterator iter = arrayMonster.begin();
		//	iter != arrayMonster.end(); ++iter)
		//{
		//	if(!(*iter))
		//		continue;
		//	
		//	if((*iter)->mgId == 0)
		//	{
		//		continue;
		//	}
		//	NPCVo* npcVo = MonsterManager::Instance()->getMonsterGroup((*iter)->mgId);
		//	if(!npcVo)
		//		continue;

		//	sprintf( _assetURL, "assets/res/%d", npcVo->_resId);

		//	BitmapMovieClip* movieClip = NULL;
		//	movieClip = SourceCacheManage::Instance()->loadModel(
		//		_assetURL, npcVo->_resId, 0.2f, true, true);
		//	if (movieClip)
		//	{
		//		movieClip->dispose(true);
		//	}
		//	CC_SAFE_DELETE( movieClip );
		//}

		////////////////monster end

		
		////////////

		////player
		//DWORD d2 = Timer::millisecondNow();
		//CCLog("-----------------loading NPC Resource use: %d ,%f s", (d2-d1), (d2-d1)*0.001 );

		//sprintf( _assetURL, "assets/res/%d", info->playerBaseInfo.cloth);
		//BitmapMovieClip* m = SourceCacheManage::Instance()->loadModel(
		//	_assetURL, info->playerBaseInfo.cloth, 0.1f, true);
		//if (m)
		//{
		//	m->dispose(true);
		//}
		//CC_SAFE_DELETE( m );
		//////player end
		
		//End Kenfly 20121106

		//CCLog("------------------Loading Resource end.");	// Jae

		// jae 20120803, Kenfly 20121112 
		//g_pKKAnimationFactory->registAni("assets/effect/recvTask/recvTask.plist", "recvImg%d.png", 12, 0.1f);
		//g_pKKAnimationFactory->registAni("assets/effect/finTask/finTask.plist", "finTask%d.png", 12, 0.1f);
		//SourceCacheManage::Instance()->loadModelAnimation("assets/effect/recvTask/recvTask.plist", "recvImg%d.png", 12, 0.1f);
		//SourceCacheManage::Instance()->loadModelAnimation("assets/effect/finTask/finTask.plist", "findTask%d.png", 12, 0.1f);


		//DWORD d3 = Timer::millisecondNow();
		//CCLog("-----------------loading player and effect use: %d ,%f s", (d3-d2), (d3-d2)*0.001 );

		//CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_Default );

		g_pGlobalManage->loadOneProgress( 20 );
	}
	
	if ( progress == 2 )
	{
		g_pGlobalManage->loadOneProgress( 20 );
		//CCDirector::sharedDirector()->drawScene();
	}
	

	if(progress == total)
	{
		g_pGlobalManage->loadOneProgress( 20 );

		int roleLev = RoleManage::Instance()->roleLev();
		TaskProxy *pTaskProxy = (TaskProxy *) g_pFacade->retrieveProxy(AppFacade_TASK_PROXY);
		if(pTaskProxy)
		{
			pTaskProxy->initCanTaskList(roleLev);
		}
		//GameDispatcher.getInstance().dispatchEvent(new Event(GameDispatcher.LOAD_COMPLETE) );
		sendNotification(Facade_Mediator, AppFacade_GAME_VIEW_MEDIATOR, NULL, GameViewMediator::GOTO_GAME_VIEW);
		TimerManage::Instance()->add( 2* 60 * 1.0f, schedule_selector(LoginMediator::sendHartbeatToServer), this);
		//TimerManage.getInstance().add(2*60*1000, sendHartbeatToServer);

		//CCDirector::sharedDirector()->drawScene();
	}
}


/*
		private function getUserInfo(e:Event=null):void{
			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_MERCENARY_BASE_INFO, new Int8(0));
			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_ALL_TASK_REQUEST,new Int8(0));
			_gateSocket.sendMessage(SocketCMDConst.CMSG_COMMU_MAIL_COUNTINFO);	
			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_LOGIN_CD );
			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_LOGIN_CRYSLTAL);
			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_BAG_INIT, new Int8(0));
			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_FORMATION_PASSIVESKILL, new Int8(1));
			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_FORMATION_PASSIVESKILL, new Int8(3));
			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_FORMATION_PASSIVESKILL, new Int8(2));

			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_PROCESS,new Int8(0));	
			
			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_TRAIN_INFO); 
			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_MERCENARY_EQUIP_INFO, new Int8(0));
			_socket.sendMessage(SocketCMDConst.CMSG_GET_ACHIVEMENT_INFO);
			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_REQ_TRIAL_VIP);
		}
*/

void LoginMediator::getUserInfo()
{
	GameServerSocket* pSocket = GameServerSocket::getInstance();
	if ( !pSocket ) return;

	// task
	CCMD15F cCMD15F;
	pSocket->sendMessage(&cCMD15F);
	
	//Request mercenaries foundation information
	CCMD306 packet306;
	//packet306;
	pSocket->sendMessage(&packet306);

	CCMD189* packet189 = new CCMD189();
	pSocket->sendMessage(packet189);
	CC_SAFE_DELETE(packet189); // LH0712LEAK

	CCMD307 packet307;

	packet307.a_byte=0;
	pSocket->sendMessage(&packet307);

	CCMD308 packet308;
	packet308.a_byte=0;
	pSocket->sendMessage(&packet308);

	CCMD164 s;
	pSocket->sendMessage( &s );

	CCMD351 packet351;	//1 a bag, request to hang up training list
	pSocket->sendMessage( &packet351 );

	// 290 what get a map has open, which will open
	CCMD122 packet122;
	packet122.a_byte = 0;
	pSocket->sendMessage(&packet122);
 
	//1 application system formation
	CCMD317 packet317;
	packet317.a_type=1;
	pSocket->sendMessage(&packet317);

	//Request 3 passive skill
	CCMD317 packet317_1;
	packet317_1.a_type=3;
	pSocket->sendMessage(&packet317_1);

	//Request 2 talent
	CCMD317 packet317_2;
	packet317_2.a_type=2;
	pSocket->sendMessage(&packet317_2);

	// Request CD
	CCMD17E packet17e;
	pSocket->sendMessage(&packet17e);
	
	// Request honor list
	CCMD141 packet141;
	pSocket->sendMessage(&packet141);

	CCMD3C7 packet3c7;
	pSocket->sendMessage(&packet3c7);

	CCMD420 packet420;
	pSocket->sendMessage(&packet420);

	CCMD1E7 packet1e7;
	pSocket->sendMessage(&packet1e7);

	CCMD430 packet430;	
	pSocket->sendMessage(&packet430);

	CCMD270 packet270;
	packet270.a_fbId = 0;

	// gate

	GateServerSocket* pGateSocket = GateServerSocket::getInstance();
	if ( !pGateSocket ) return;

	CCMD1AA packet1aa;
	pGateSocket->sendMessage(&packet1aa);


	/*
	// Request mail list
	CCMD1A0 packet1A0_0;
	packet1A0_0.a_mailType = (uint8)MailConst::MAIL_TYPE_ALL;
	packet1A0_0.b_startNum = (uint16)0;
	packet1A0_0.c_mailNum = (uint16)60;
	pGateSocket->sendMessage(&packet1A0_0);
	*/


	/*
	// Request mail list
	CCMD1A0 packet1A0_1;
	packet1A0_1.a_mailType = (uint8)MailConst::MAIL_TYPE_SYSTEM;
	packet1A0_1.b_startNum = (uint16)0;
	packet1A0_1.c_mailNum = (uint16)6;
	pSocket->sendMessage(&packet1A0_1);

	// Request mail list
	CCMD1A0 packet1A0_2;
	packet1A0_2.a_mailType = (uint8)MailConst::MAIL_TYPE_PLAYER;
	packet1A0_2.b_startNum = (uint16)0;
	packet1A0_2.c_mailNum = (uint16)6;
	pSocket->sendMessage(&packet1A0_2);
	*/

// 
// 	if (g_pLoginManage->_pLoginView)
// 	{
// 		g_pLoginManage->_pLoginView->autorelease();
// 		g_pLoginManage->_pLoginView = 0;
//   }
 /*
	//0x1AA;
	//0x17E;
	//0x189;
	//0x141; 
	//0x3C7;
	*/

	////////////////////////////////////////
	/*
		private function getUserInfo(e:Event=null):void{
			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_MERCENARY_BASE_INFO, new Int8(0));	// 0x307
			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_ALL_TASK_REQUEST,new Int8(0));		// 0x15F
			_gateSocket.sendMessage(SocketCMDConst.CMSG_COMMU_MAIL_COUNTINFO);					// 0x1AA
			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_LOGIN_CD );							// 0x17E
			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_LOGIN_CRYSLTAL);						//0x189
			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_BAG_INIT, new Int8(0));				// 0x164
			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_FORMATION_PASSIVESKILL, new Int8(1));	// 0x317
			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_FORMATION_PASSIVESKILL, new Int8(3));	// 0x317
			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_FORMATION_PASSIVESKILL, new Int8(2));	// 0x317

			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_PROCESS,new Int8(0));					// 0x122
			
			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_TRAIN_INFO);   						// 0x351
			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_MERCENARY_EQUIP_INFO, new Int8(0));	// 0x308
			_socket.sendMessage(SocketCMDConst.CMSG_GET_ACHIVEMENT_INFO); 						// 0x141
			_socket.sendMessage(SocketCMDConst.CMSG_WORLD_REQ_TRIAL_VIP);						//0x3C7
		}
*/
	////////////////////////////////////////////
}

void LoginMediator::getUserInfoHandler()
{

	//if(GameManager::instance()->isGameServerLogin && GameManager::getInstance()->isLoadComplete)
	{
		getUserInfo();
	}	 
}

void LoginMediator::initRoleInfo(SCMD107* cmd)
{
	if(!cmd)
		return;

	//The initial a leading role
	PlayerInfoVo playerinfo;
	playerinfo.playerBaseInfo.x = cmd->c_x;
	playerinfo.playerBaseInfo.y = cmd->d_y;
	playerinfo.playerBaseInfo._mapId = cmd->b_mapId;
	playerinfo.playerBaseInfo.name = cmd->f_name;
	playerinfo.playerBaseInfo.accountId = cmd->a_AccountId;
	playerinfo.playerBaseInfo.isRole = true;
	playerinfo.playerBaseInfo._guildName = cmd->s_guildName;
	RoleManage::Instance()->addMercenary(cmd->e_id, &playerinfo);

	RoleManage::Instance()->_accountInfo.accountId = cmd->a_AccountId;
	RoleManage::Instance()->_accountInfo.roleId = cmd->e_id;
	RoleManage::Instance()->_accountInfo.name = cmd->f_name;
	RoleManage::Instance()->_accountInfo._silver = cmd->g_silvere;
	RoleManage::Instance()->_accountInfo._gold = cmd->h_gold;
	RoleManage::Instance()->_accountInfo._stone = cmd->t_stone;
	RoleManage::Instance()->_accountInfo._practice = cmd->i_practice;
	RoleManage::Instance()->_accountInfo._popularity = cmd->j_popularity;
	RoleManage::Instance()->_accountInfo._energy = cmd->k_energy;
	RoleManage::Instance()->_accountInfo._vigourBuffCount = cmd->_remainVigourBuffCount;
	RoleManage::Instance()->_accountInfo._gongExpBuffCount = cmd->_gongExpBuffCount;
	RoleManage::Instance()->_accountInfo._vipLev = cmd->m_vipLev;
	RoleManage::Instance()->_accountInfo._goldcount = cmd->n_vipGold;
	RoleManage::Instance()->_accountInfo._onlineTime = cmd->o_onlineTime;
	RoleManage::Instance()->_accountInfo._trainSitNumLim = cmd->q_trainSitNum;
	TrainManager::Instance()->setTrainLim(cmd->q_trainSitNum);
	RoleManage::Instance()->_accountInfo._numCrystalCd = cmd->r_crystalListNum;
	RoleManage::Instance()->_accountInfo.guild = g_pGlobalManage->guild;
	RoleManage::Instance()->_currentId = cmd->e_id;
	CDManage::Instance()->serverTimer( cmd->l_serverTime );
	g_pGlobalManage->isGm = (cmd->p_accountType == 3);
	g_pGlobalManage->_isOnBusiness = (cmd->x_isOnbussiness==1)?true:false;

	TraderProxy* traderProxy = (TraderProxy*)g_pFacade->retrieveProxy(AppFacade_CITY_TRADER_CHANGE);
	if (traderProxy)
	{
		traderProxy->_restTraderCnt = cmd->y_restTraderCnt;
	}	

	SoundManager::Instance()->_nCurMapID = cmd->b_mapId;

	//Get addicted state the platform, and sent to the server, might as well the 0 0 defenses
	//int fcmStatus = 0;
	//if(GameManager.getInstance().parameters.fcm)
	//{
	//	fcmStatus = GameManager.getInstance().parameters.fcm;
	//}
	//GlobalManage.getInstance().isFCM =  fcmStatus !=0;

	//_socket.sendMessage(SocketCMDConst.CMSG_WORLD_FCM_STATE, fcmStatus);

	//if(GlobalManage.getInstance().isFCM && params.o_onlineTime>=10800){
	//	GameServerSocket.getInstance().close();
	//	GateServerSocket.getInstance().close();
	//}

	//params = null;
	////To the service requests for other data
	//GameManager.getInstance().isGameServerLogin = true;

	//jae 20120831
	g_pGlobalManage->startResourceLoadingSync();

	getUserInfoHandler();

	// world boss info request
	// LH 20120918
	sendNotification(Facade_Command , AppFacade_WorldBoss_Command , (char *)0 , WorldBossCmd::INIT_WORLD_BOSS_PROXY);
}

/**
* Mercenaries foundation information
* @param param
* 
*/
void LoginMediator::mercenaryBaseInfo(SCMD309* cmd)
{
	//sendNotification(Facade_Command, AppFacade_FIGURE_COMMAND, (char*)cmd, FigureCommand::INIT_FIGURE_BASE_INFO);
	sendNotification(Facade_Command, AppFacade_FIGURE_COMMAND, (char*)cmd, FigureCommand::INIT_FIGURE_BASE_INFO);
	onLogin();
}

/**
*Initialize equipment information
* @ param param
* 
*/		
void LoginMediator::sockEquipInfo(SCMD30A* cmd)
{
	//sendNotification(Facade_Command, AppFacade_FIGURE_COMMAND, (char*)cmd, FigureCommand::INIT_FIGURE_EQUIP_INFO);
	sendNotification(Facade_Command, AppFacade_FIGURE_COMMAND, (char*)cmd, FigureCommand::INIT_FIGURE_EQUIP_INFO);
	onLogin();
}

void LoginMediator::initCD(SCMD17F* scmd17f)
{
	CDManage::Instance()->initAllCD(scmd17f->a_cd);
	onLogin();
}

void LoginMediator::initWorldBag(SCMD161* cmd)
{
	sendNotification(Facade_Command, AppFacade_BAG_PROXY_CHANGE, (char*)&(cmd->a_goodsList), BagProxyCommand::CREATE_GOODS_LIST);
	//_socket.removeCmdListener(SocketCMDConst.WMSG_WORLD_BAG_INIT, initWorldBag);
	onLogin();
}

void LoginMediator::initBank(SCMD161* cmd)
{
	//_socket.removeCmdListener(SocketCMDConst.WMSG_WORLD_BAG_INIT, initBank);
	//this.sendNotification(AppFacade.BANK_PROXY_CHANGE,arr, BankProxyCommand.CREATE_GOODS_LIST);
	sendNotification(Facade_Command, AppFacade_BAG_PROXY_CHANGE, (char*)&(cmd->a_goodsList), BagProxyCommand::CREATE_GOODS_LIST);
}

void LoginMediator::initPassiveSkill(SCMD319* cmd)
{
	sendNotification(Facade_Command, AppFacade_SKILL_COMMAND, (char*)cmd, SkillCommand::INIT_SKILL_DIC);
	//sendNotification(AppFacade.UP_SKILL_PROXY_CHANGE, param, SkillCommand.INIT_SKILL_DIC);
	//_socket.removeCmdListener(SocketCMDConst.WMSG_WORLD_PASSIVESKILL_INFO, initPassiveSkill);
	onLogin();
}

void LoginMediator::initTalentSkill(SCMD3C9* cmd)
{
	sendNotification(Facade_Command, AppFacade_SKILL_COMMAND, (char*)cmd, SkillCommand::INIT_TALENT_DIC);
	//sendNotification(AppFacade.UP_SKILL_PROXY_CHANGE, param, SkillCommand.INIT_TALENT_DIC);
	//_socket.removeCmdListener(SocketCMDConst.WMSG_WORLD_Req_Talent, initTalentSkill);
	onLogin();
}

void LoginMediator::initCrystal(SCMD18A* cmd)
{
	sendNotification(Facade_Command, AppFacade_CRYSTAL_PROXY_CHANGE, (char*)cmd, CrystalCommand::INIT_ACCOUNT_INFO);
	//sendNotification(AppFacade.CRYSTAL_PROXY_CHANGE, param, CrystalCommand.INIT_ACCOUNT_INFO);
	//_socket.removeCmdListener(SocketCMDConst.WMSG_WORLD_LOGIN_CRYSTAL_FEEDBACK, initCrystal);
	onLogin();
}


void LoginMediator::sendHartbeatToServer( ccTime dt )
{
	GateServerSocket* gSocket = GateServerSocket::getInstance();
	GameServerSocket* pSocket = GameServerSocket::getInstance();
	
	if(gSocket)
	{
		CCMD010 ccmd010;
		gSocket->sendMessage(&ccmd010);
	}

	if (pSocket)
	{
		CCMD011 ccmd011;
		pSocket->sendMessage(&ccmd011);
	}
}

void LoginMediator::sendClientType()
{
	int8 type = 2;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	type = 1;
#endif

	{
		CCMD10F ccmd10f;
		ccmd10f.a_type = type;
		ccmd10f.b_accId = 0;//RoleManage::Instance()->accountInfo()->accountId;
		GameServerSocket::getInstance()->sendMessage(&ccmd10f);
	}

	{
		CCMD10F ccmd10f;
		ccmd10f.a_type = type;
		ccmd10f.b_accId = RoleManage::Instance()->accountInfo()->accountId;
		GateServerSocket::getInstance()->sendMessage(&ccmd10f);
	}
}
