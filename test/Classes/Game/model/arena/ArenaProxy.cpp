#include "ArenaProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/arena/ArenaMediator.h"
#include "socket/command/c36/CCMD360.h"
#include "socket/network/GameServerSocket.h"
#include "socket/command/c28/CCMD284.h"
#include "socket/command/c28/CCMD286.h"
#include "view/arena/components/ArenaUI.h"
#include "socket/command/c13/CCMD134.h"
#include "socket/command/c36/CCMD362.h"
#include "socket/command/c36/CCMD364.h"
#include "socket/command/c36/CCMD36F.h"
#include "socket/command/c38/CCMD38D.h" //hwj
#include "socket/command/s38/SCMD38C.h"
#include "ArenaConst.h"
#include "manager/LangManager.h"
#include "view/arena/components/ArenaUI.h"
#include "view/arena/components/HeroRankView.h"
#include "../battle/FightProxy.h"
#include "socket/command/s36/SCMD363.h"
#include "view/fight/callback/ArenaCallbackAction.h"

ArenaProxy::ArenaProxy()
{
	_Row_number = 0;
	_Arena_lev = 0;
	_meRange = 0;
	_meRank = 0;
	_giftNum = 0;
	isOpen = 0;
	_arenaUI = 0;
	_heroRankView = 0;
}

ArenaProxy::~ArenaProxy()
{}

void ArenaProxy::setarenaUI(ArenaUI* ui)
{
	_arenaUI = ui;
	startArenaEvent();
	startArenaSocket();
}

void ArenaProxy::setheroUI(HeroRankView* ui)
{
	_heroRankView = ui;
}

void ArenaProxy::startArenaEvent()
{
	_arenaUI->addEventListener(ArenaConst::REPORT_ARENA, this, callfuncND_selector(ArenaProxy::onClickLinkReport));
	_arenaUI->addEventListener(ArenaConst::PK_ARENA, this, callfuncND_selector(ArenaProxy::onPkArena));
	_arenaUI->addEventListener(ArenaConst::TAKE_AWARD, this, callfuncND_selector(ArenaProxy::onTakeAward));
	_arenaUI->addEventListener(ArenaConst::GIFT_PACKAGE, this, callfuncND_selector(ArenaProxy::onGiftPackage));
	_arenaUI->addEventListener(ArenaConst::BUY_ARENA, this, callfuncND_selector(ArenaProxy::onBuy));
	_arenaUI->addEventListener(ArenaConst::RESET_OPPS, this, callfuncND_selector(ArenaProxy::onResetOpps));//hwj
	_arenaUI->addEventListener(ArenaConst::CARD_FINISH, this, callfuncND_selector(ArenaProxy::onCardFinish));
}
//刷新对手 hwj
void ArenaProxy::onResetOpps(CCNode* n, void* data)
{
	//if (!data)
		//return;
	//uint32 param = *(uint32*)data;
	CCMD38D* cmd = new CCMD38D();
	if (cmd)
	{
		//cmd->param = param;
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(cmd);
	}
	SAFE_DELETE(cmd);
}
/**挑战对手*/
void ArenaProxy::onPkArena(CCNode* n, void* data)
{
	if (!data)
		return;
	uint32 param = *(uint32*)data;
	CCMD362* cmd = new CCMD362();
	if (cmd)
	{
		cmd->param = param;
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(cmd);
	}
	SAFE_DELETE(cmd);
}

/**查看竞技场最近5场的战报*/
void ArenaProxy::onClickLinkReport(CCNode* n, void* data)
{
	if (!data)
		return;

	struct sdata
	{
		uint32 a_battleId1;
		uint32 b_battleId2;
	};
	sdata* d = (sdata*)data;

	CCMD134* cmd = new CCMD134();
	if (cmd)
	{
		cmd->a_battleId1 = d->a_battleId1;
		cmd->b_battleId2 = d->b_battleId2;
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(cmd);
	}
	SAFE_DELETE(cmd);
}

/**获取翻牌奖励*/
void ArenaProxy::onTakeAward(CCNode* n, void* data)
{
	CCMD364* cmd = new CCMD364();
	if (cmd)
	{
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(cmd);
	}
	SAFE_DELETE(cmd);
}

/**领取英雄榜礼包*/
void ArenaProxy::onGiftPackage(CCNode* n, void* data)
{
	CCMD286* cmd = new CCMD286();
	if (cmd)
	{
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(cmd);
	}
	SAFE_DELETE(cmd);
}
		
/**玩家购买竞技场挑战次数*/
void ArenaProxy::onBuy(CCNode* n, void* data)
{
	CCMD36F* cmd = new CCMD36F();
	if (cmd)
	{
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(cmd);
	}
	SAFE_DELETE(cmd);
}
		
/**翻牌领奖结束*/
void ArenaProxy::onCardFinish(CCNode* n, void* data)
{
	reqArenaInfo();
	reqHeroInfo();
}


void ArenaProxy::startArenaSocket()
{
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_WORLD_HERO_GET_AWARD, doGiftPackage);
}

// 玩家进入竞技场面板，请求竞技场信息
void ArenaProxy::reqArenaInfo()
{
	CCMD360* cmd = new CCMD360();
	if (cmd)
	{
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(cmd);
	}
	SAFE_DELETE(cmd);
}
 
// 请求英雄榜信息 
void ArenaProxy::reqHeroInfo()
{
	CCMD284* cmd = new CCMD284();
	if (cmd)
	{
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(cmd);
	}
	SAFE_DELETE(cmd);
}
		
// 返回玩家竞技场信息
void ArenaProxy::doArenaInfo(SCMD361* param){
	if (_arenaUI)
	{
		_arenaUI->updateInfo(param);
	}
}
		
// 竞技场战斗开启结果返回
void  ArenaProxy::doArenaPkRes(SCMD363* param)
{
	if(!param)
		return;

	if(param->b_result == 0)
	{
		FightProxy* fightProxy = (FightProxy*)g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
		if(fightProxy)
		{
			//figthProxy._bData._callbacks.push(new ArenaCallbackAction(this._arenaUI));

			ArenaCallbackAction* callback = new ArenaCallbackAction();
			callback->init(_arenaUI);
		
			fightProxy->_bData._callbacks.push_back(callback);
		}
	}
	else
	{
		LangManager::msgShow("ARN063");
	}
}

// 竞技场翻牌奖励
void ArenaProxy::doArenaAwardRes(SCMD36E* param)
{
	_arenaUI->updateCard(param);
}
		

// 竞技场购买竞技令返回
void ArenaProxy::doArenaBuyRes(SCMD38C* param)
{
	param->a_buy==0?LangManager::msgShow("JJC014"):LangManager::msgShow("JJC015");
}
		
// 领取英雄榜礼包返回
void ArenaProxy::doGiftPackage(SCMD287* param)
{
	if (param->a_ret == 0)
	{
		reqArenaInfo();
		reqHeroInfo();
	}
}
		
		
void ArenaProxy::startHeroEvent()
{
	//_heroRankView.addEventListener(ArenaConst.ADD_FRIEND, onAddFriend);
}
		
// 添加好友
void ArenaProxy::onAddFriend()
{
	//_gSocket.sendMessage(SocketCMDConst.CMSG_COMMU_FRIENDS_ADD_FRIEND, e.param as String);
}
		
		
/**服务端返回英雄榜列表*/
void ArenaProxy::doHeroInfo(SCMD285* param)
{

	if(_arenaUI){
		_arenaUI->updatePackage(param);
	}
	if(_heroRankView){
		_heroRankView->update(param);
	}
	
}

/*
public function getPvpReportByType(type:int):Array{
	return _pvpReportDic[type];
}
public function get pvpReportDic():Dictionary{
	return _pvpReportDic;
}
public function get pvpArray():Array{
	return _pvpArray;
}
public function set pvpReportDic(value:Dictionary):void{
	_pvpReportDic = value;
}
public function set pvpArray(value:Array):void{
	_pvpArray = value;
}
*/
/*
void ArenaProxy::PVPQualifying(SCMD361* data)
{
	_Row_number = data->b_straightNum;
	_StartDic.push_back(data->c_star1);
	_StartDic.push_back(data->d_star2);
	_StartDic.push_back(data->e_star3);
	_StartDic.push_back(data->f_star4);
	_StartDic.push_back(data->g_star5);
	sendNotification(Facade_Mediator, AppFacade_ARENA_MEDIATOR, NULL, ArenaMediator::PVP_QUALIFYING_START);
}
*/

	

