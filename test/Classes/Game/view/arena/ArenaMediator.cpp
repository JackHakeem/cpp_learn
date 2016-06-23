#include "ArenaMediator.h"
#include "model/arena/ArenaProxy.h"
#include "events/GameDispatcher.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "model/player/vo/AccountInfoVo.h"
#include "model/player/RoleManage.h"
#include "manager/GlobalManage.h"
#include "Message.h"
#include "../scene/SceneMediator.h"
#include "components/ArenaUI.h"
#include "manager/ViewManager.h"
#include "utils/flash/CCIEventDispatcher.h"
#include "socket/command/c28/CCMD286.h"
#include "utils/ValuesUtil.h"
#include "model/arena/vo/HeroRankVo.h"
#include "socket/command/c36/CCMD360.h"
#include "control/arena/ArenaProxyCommand.h"
#include "socket/command/s39/SCMD39D.h"
#include "model/arena/vo/ArenaReportVo.h"
#include "components/HeroRankView.h"
#include "manager/LangManager.h"
#include "manager/PopEventName.h"

ArenaMediator::ArenaMediator()
{
	_arenaUI = 0;
	_arenaProxy = (ArenaProxy*)g_pFacade->retrieveProxy(AppFacade_ARENA_PROXY);
	_dispatcher =  GameDispatcher::getInstance();
	_dispatcher->addEventListener(GameDispatcher::SHOW_HERO_RANK, this, callfuncND_selector(ArenaMediator::lookRankHandler));
	_dispatcher->addEventListener(PopEventName::SHOW_UI_ARENA, this, callfuncND_selector(ArenaMediator::showArena));
}

ArenaMediator::~ArenaMediator()
{
	if (_arenaUI)
		_arenaUI->release();
}

void ArenaMediator::handleNotification(int M2Vcmd, char* data)
{
	switch(M2Vcmd)
	{
	case PVP_QUALIFYING_START:
		CommandQualifying();
		break;
	}
}

void ArenaMediator::showArenaHandler()
{
	AccountInfoVo* acc = RoleManage::Instance()->accountInfo();
	if(acc && acc->team > 0)
	{
		//Message.show("组队状态不能打开竞技场", 0xff0000);
		return;
	}
	else if (!g_pGlobalManage->canMove())
	{
		//Message.show("当前状态不能进入竞技场", 0xff0000);
		return;
	}
	sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, NULL, SceneMediator::ROLE_STOP);

	openArena();
}

void ArenaMediator::openArena()
{
 	openArenaUI();
  	_arenaProxy->reqArenaInfo();// 请求竞技场信息
  	_arenaProxy->reqHeroInfo(); // 请求英雄榜信息 
}

// 打开竞技场
void ArenaMediator::openArenaUI()
{
	_arenaProxy->isOpen = true;
	if(!_arenaUI)
	{
		_arenaUI = new ArenaUI();
		_arenaUI->initView();
		//_arenaUI.addEventListener(ArenaUI.EXIT_CLICK,closeArenaHander);
 		//_arenaUI.addEventListener(ArenaUI.ADD_FRIEND, addFriend);		//菜单-添加好友
		ViewManager::getInstance()->arenaUI = _arenaUI;
		_arenaUI->addEventListener(ArenaUI::GET_AWARD, this, callfuncND_selector(ArenaMediator::getAwardHandler));

		_arenaProxy->setarenaUI(_arenaUI);
	}
	
	_arenaUI->setisPop(!_arenaUI->getisPop());
	//if (_arenaUI->getisPop())
	//{
	//	_arenaUI->release();
	//}
	

	/*
	 		if(!_arenaUI){
				_arenaUI = new ArenaUI();
				_arenaUI.addEventListener(ArenaUI.EXIT_CLICK,closeArenaHander);
 				_arenaUI.addEventListener(ArenaUI.ADD_FRIEND, addFriend);		//菜单-添加好友
				
				_arenaProxy.arenaUI = _arenaUI;
			}
			
			if(!LayerManager.arenaUILayer.contains(_arenaUI)){
				LayerManager.arenaUILayer.addChild(_arenaUI);
			}
			
			var mercVO:FigureCfgBaseVo = FigureBaseManage.getInstance().getNextPopMerc(_roleManage.accountInfo.popularity);
			if(mercVO){
				var url:String = rURL("assets/res/snapshot/"+ mercVO.cloth +".swf");
				var tips:String = LangManager.getText("ARN024", mercVO.name, mercVO.needPop);
				_arenaUI.updateWraper(url, tips);
			}
			
			if(NewhandManager.getInstance().nextEventId == NewhandConst.EVENT_OPEN_ARENA){
				LayerManager.newhandLayer.visible = true;//新手引导层 隐藏
				_dispatcher.dispatchEvent(new ParamEvent(GameDispatcher.TEST_NEW_HAND, 
					{type:"evt", id:NewhandConst.EVENT_OPEN_ARENA}));
			}
			else{
				LayerManager.newhandLayer.visible =false;//新手引导层 隐藏
			}
			ViewManager.getInstance().scene.roleIcon = 1;
			
			resize();
	*/
}

void ArenaMediator::winningStarHandler(char* cmd)
{
	sendNotification(Facade_Command, AppFacade_ARENA_COMMAND, (char*)cmd, ArenaProxyCommand::PVP_QUALIFYING_STAR);
}


void ArenaMediator::closeArenaHander()
{

}

void ArenaMediator::getAwardHandler(CCNode* p, void* e)
{
	if(_arenaProxy->_giftNum <= 0){
		//Message.show("礼包已领取完毕", 0xff00000);
		return;
	}

	getHeroRankAward();
}

void ArenaMediator::getHeroRankAward()
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

void ArenaMediator::heroGetAwardHandler(SCMD287* cmd)
{
	/*
	if (cmd->a_ret == 0) //success
	{
		char msg[30];
		switch (cmd->b_type)
		{
		case 0:
			sprintf(msg, ValuesUtil::Instance()->getString("ARENA01").c_str(), cmd->c_value);
			Message::Instance()->show(std::string(msg));
			break;
		case 1:
			sprintf(msg, ValuesUtil::Instance()->getString("ARENA02").c_str(), cmd->c_value);
			Message::Instance()->show(std::string(msg));
			break;
		case 2:
			sprintf(msg, ValuesUtil::Instance()->getString("ARENA03").c_str(), cmd->c_value);
			Message::Instance()->show(std::string(msg));
			break;
		case 3:
			sprintf(msg, ValuesUtil::Instance()->getString("ARENA04").c_str(), cmd->c_value);
			Message::Instance()->show(std::string(msg));
			break;
		case 4:
			sprintf(msg, ValuesUtil::Instance()->getString("ARENA05").c_str(), cmd->c_value);
			Message::Instance()->show(std::string(msg));
			break;
		}

		_arenaProxy->_giftNum = _arenaProxy->_giftNum - 1;
		if(_arenaUI)
		{
			_arenaUI->updateAwardLabel(_arenaProxy->_giftNum);
		}
	}
	else 
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("ARENA06").c_str());
	}
	*/
}

void ArenaMediator::heroInfoHandler(SCMD285* cmd)
{
	/*
	_arenaProxy->_meRange = cmd->a_meRank;
	_arenaProxy->_meRank = cmd->b_meRank + 1;	//start from 0, need to add 1
	_arenaProxy->_giftNum = cmd->c_meGift;

	if(_arenaUI)
	{
		_arenaUI->updateAwardLabel(_arenaProxy->_giftNum);
	}

	int preRank = 0;
	std::vector<HeroRankVo> list;
	std::vector<SCMD285::SCMD285Node>::iterator it;
	std::vector<SCMD285::SCMD285Node>* array = &cmd->d_rankArr;
	
	for (it = array->begin(); it != array->end(); it++)
	{
		while(preRank < it->a_rank){
			HeroRankVo heroRankVo;
			heroRankVo.rank = preRank + 1;  // 从0-24 
			heroRankVo.id = 0;
			heroRankVo.lev = getMaxLevByRange(_arenaProxy->_meRange);
			list.push_back(heroRankVo);
			preRank++;
		}

		HeroRankVo heroRankVo;
		heroRankVo.rank = it->a_rank + 1;  // 从0-24 
		heroRankVo.id = it->b_playerId;
		heroRankVo.name = it->c_playerName;
		heroRankVo.lev = it->d_crysLev;
		heroRankVo.threat = it->e_threat;
		list.push_back(heroRankVo);

		preRank = heroRankVo.rank; 
	}

	while(preRank < 25){  // max is 24
		HeroRankVo heroRankVo;
		heroRankVo.rank = preRank + 1;  
		heroRankVo.id = 0;
		heroRankVo.lev = getMaxLevByRange(_arenaProxy->_meRange);
		list.push_back(heroRankVo);
		preRank++;
	}

// 	arr.sortOn("rank", Array.NUMERIC);
// 	if(_heroRankView){
// 		_heroRankView.createItems(arr);	
// 	}
*/
}

//  range values: 0 1 2 3 corresponding crystal level: 21-40  41-60 61-80 81-100
int ArenaMediator::getMaxLevByRange(int range)
{
	int maxLev = 40;
	switch(range)
	{
	case 0:
		maxLev = 40;
		break;
	case 1:
		maxLev = 60;
		break;
	case 2:
		maxLev = 80;
		break;
	case 3:
		maxLev = 100;
		break;
	default:
		maxLev = 40;
	}
	return maxLev;
}

void ArenaMediator::athleticsReportHandler(SCMD39D* cmd)
{
//	if(_arenaUI)
//	{
//// 		if(!_arenaUI.isAwardShow())
//// 		{
//			std::vector<ArenaReportVo*> report;
//			std::vector<SCMD39D::SCMD39DNode> nodeList = cmd->a_pvpReport;
//			std::vector<SCMD39D::SCMD39DNode>::iterator it;
//
//			for (it = nodeList.begin(); it != nodeList.end(); it++)
//			{
//				ArenaReportVo* arenaReportVo;
//				arenaReportVo->fightTime = it->a_time;
//				arenaReportVo->isChallenge = it->b_isChallenge;
//				arenaReportVo->enemyName = it->c_enemyName;
//				arenaReportVo->isSuccess = it->d_isSucess;
//				arenaReportVo->rank = it->e_rank;
//				arenaReportVo->fightingId1 = it->f_fightingId1;
//				arenaReportVo->fightingId2 = it->g_fightingId2;
//				report.push_back(arenaReportVo);
//			}
//
//			_arenaUI->showReportList(report);
////		}
//	}
}

void ArenaMediator::CommandQualifying()
{

}

/**查看英雄榜*/
void ArenaMediator::lookRankHandler(CCNode* n, void* data)
{
	HeroRankView* pHRV = (HeroRankView*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_heroUi);
	if (pHRV)
	{
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_heroUi, true);
	}
	_heroRankView = 0;

	_heroRankView = new HeroRankView();
	_heroRankView->init();		
	LayerManager::tipsLayer->addChild(_heroRankView, TipsLayer::TipsLayerZ_heroUi,TipsLayer::TipsLayerTAG_heroUi);
	_arenaProxy->setheroUI(_heroRankView);
	_arenaProxy->reqHeroInfo();
	_heroRankView->release();
}

void ArenaMediator::challengeErrorHandler(SCMD366* param)
{
	if(!param)
		return;

	switch(param->b_arenaType)
	{
	case 2:
		switch(param->a_isSucess)
		{
		case 1:
			//_fightProxy._bData._callbacks.push(new RingCallbackAction(_ringUI));
			break;
		default:
			LangManager::msgShow("ARENA31");
			//reqRingInfo();
			break;
		}
		break;
	case 4:
		switch(param->a_isSucess)
		{
		case 0:
			break;
		case 1:
			LangManager::msgShow("ARENA32");
			break;
		case 2:
			LangManager::msgShow("ARENA33");
			break;
		case 3:
			LangManager::msgShow("ARENA34");
			break;
		case 4:
			LangManager::msgShow("ARENA35");
			break;
		case 5:
			LangManager::msgShow("ARENA36");
			break;
		}
		break;
	}
}

void ArenaMediator::showArena( CCNode* p, void* e )
{
	showArenaHandler();
}
