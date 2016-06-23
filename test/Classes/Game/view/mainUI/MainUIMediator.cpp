#include "MainUIMediator.h"
#include "components/MainNavigate.h"
#include "manager/LayerManager.h"
#include "manager/ViewManager.h"
#include "model/task/TaskProxy.h"
#include "socket/command/c29/CCMD29D.h"
#include "socket/network/GameServerSocket.h"
//#include "../scene/components/fight/UpdateSilverAction.h"
#include "socket/command/s18/SCMD18D.h"
#include "Message.h"
#include "model/player/RoleManage.h"
#include "socket/command/c21/CCMD21E.h"
#include "socket/command/c21/CCMD21D.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "socket/command/s21/SCMD21F.h"
#include "socket/command/s18/SCMD18E.h"
#include "socket/command/s18/SCMD18D.h"
#include "socket/command/s18/SCMD18C.h"
#include "socket/command/s18/SCMD188.h"
#include "socket/command/s2e/SCMD2ED.h"
#include "socket/command/c2e/CCMD2EC.h"
#include "../newhand/NewhandMediator.h"
#include "control/com/ComProxyCommand.h"
#include "view/fight/callback/UpdatePraceticeAction.h"
#include "view/fight/callback/UpdateSilverAction.h"
#include "view/fight/callback/UpdatePopularityAction.h"
#include "manager/CDManage.h"
#include "manager/LangManager.h"
#include "utils/flash/CCIEventDispatcher.h"
#include "manager/GlobalManage.h"
#include "view/dailyTaskEx/components/DailyTaskExView.h"
#include "view/silverMine/SilverMineMediator.h"
#include "model/silverMine/SilverMineManage.h"
#include "manager/CDManage.h"
#include "socket/command/c24/CCMD24E.h"
#include "socket/command/s24/SCMD24F.h"
#include "model/scene/TokenManager.h"

MainUIMediator::MainUIMediator()
{
	_dispatcher = 0;
	_buttomView = 0;
	_cdList = 0;
	_secNavigate = NULL;
	_roleUI = 0;

	g_pGlobalManage->addEventListener(GlobalManage::MINE_TIME_CHANGE, this, callfuncND_selector(MainUIMediator::mineTimeChange));
}

MainUIMediator::~MainUIMediator()
{}


void MainUIMediator::handleNotification(int M2Vcmd, char* data)
{
	switch(M2Vcmd)
	{
	case STARTUP_PEOPLE_UI:
        startUpPeopleView();
		break;
	case STARTUP_CD_LIST:
		startUpCdList();
		break;
	case STARTUP_TOKEN_BAR:
		startUpTokenBar();
		break;
	case STARTUP_SEC_NAV:
		startUpSecondaryNavigate();
		break;
	case SET_SEC_NAVIGATE_VISIBLE:
		{
			if(!LayerManager::sceneUILayer)
				break;

			if(_secNavigate->getParent() == LayerManager::sceneUILayer)
			{
				LayerManager::sceneUILayer->removeChild(_secNavigate, true);
			}
			else if(_secNavigate->getParent() == NULL)
			{
				LayerManager::sceneUILayer->addChild(_secNavigate);
			}
		break;
		}
	//added by chenjian Begin
	case STARTUP_REPORT_UI:
		startupReportUI(*(int*)data);
		break;
	case CLOSE_REPORT_UI:
		closeReportUI();
		break;
	case SET_REPORT_VISIBLE:
		setReportUIVisible(*((bool*)data));
		break;
	//added by chenjian End
	default:
		break;
	}
}

/**
	* 银矿战时间状态发生更改
	*/
void MainUIMediator::mineTimeChange(CCNode* pSender, void* data)
{
	int mineType = 28; //
			
	if(g_pGlobalManage->inMineTime())
	{
		//this.facade.registerProxy(new SilverMineProxy());
		//this.facade.registerMediator(new SilverMineMediator());
			
		// 
	/*	if(!_mineEntrance){
			_mineEntrance = new MineEntrance;
			_mineEntrance.x = StageProxy.width - 65;
			_mineEntrance.y = 500;
			LayerManager.sceneUILayer.addChild(_mineEntrance);
		}*/
	}
	else
	{
		//Message.show(LangManager.getText("MUI103"));
		sendNotification(Facade_Mediator, AppFacade_SilverMine_PROXY_CHANGE, NULL, SilverMineMediator::TIME_END);
				
	/*	if(_mineEntrance){
			LayerManager.sceneUILayer.removeChild(_mineEntrance);
			_mineEntrance.dispose();
			_mineEntrance = null;
		}*/
	}
}

void MainUIMediator::startUpPeopleView()
{
	// role info UI
	_roleUI = ViewManager::getInstance()->_roleUI;
	if (!_roleUI)
	{
		/*
		std::map<int, PlayerInfoVo> * merList = &RoleManage::Instance()->_mercList;
		std::map<int, PlayerInfoVo>::iterator iter = merList->begin();
		if (iter != merList->end())
		{
			PlayerInfoVo info = iter->second;
			*/
			_roleUI = new RoleUI(RoleManage::Instance()->_accountInfo.name ,RoleManage::Instance()->roleLev() ,RoleManage::Instance()->_accountInfo._crystalLev,
				RoleManage::Instance()->roleInfo()->playerBaseInfo._maxHp , RoleManage::Instance()->roleInfo()->playerBaseInfo._hp,RoleManage::Instance()->_accountInfo._energy,
				RoleManage::Instance()->_accountInfo._vipLev,/*info.playerBaseInfo.career*/1,
				RoleManage::Instance()->_accountInfo._gold, RoleManage::Instance()->_accountInfo._silver, RoleManage::Instance()->_accountInfo._silverLim, 
				RoleManage::Instance()->_accountInfo._practice,RoleManage::Instance()->_accountInfo._popularity);
			_roleUI->setVigourBuffCount(RoleManage::Instance()->_accountInfo._vigourBuffCount, 10);
			LayerManager::sceneUILayer->addChild(_roleUI, 0, SceneUILayer::SceneUILayerTAG_RoleUI);
		/*}*/
		ViewManager::getInstance()->_roleUI = _roleUI;

		sendNotification(Facade_Mediator, AppFacade_NEWHAND_MEDIATOR, 0, NewhandMediator::INIT_BUTTONS);
	}

	//
	_buttomView = new MainNavigate();
	_buttomView->init();
	LayerManager::sceneUILayer->addChild(_buttomView, 0, SceneUILayer::SceneUILayerTAG_MainUIMediator);
	ViewManager::getInstance()->mainNavigate =_buttomView;
	_buttomView->release();

	getMainUIInfo();

	startListener();
}

/*ÃÌº”CD∂”¡– */
void  MainUIMediator::startUpCdList()
{
	sendNotification(Facade_Mediator, AppFacade_NEWHAND_MEDIATOR, 0, NewhandMediator::INIT_BUTTONS);

	//if(!_cdList)
	//{
	//	_cdList = new CDPanel();
	//	_cdList->init();

	//	LayerManager::sceneUILayer->addChild(_cdList, 0, SceneUILayer::SceneUILayerTAG_MainUIMediator);
	//	ViewManager::getInstance()->cdList =_cdList;

	//	sendNotification(Facade_Mediator, AppFacade_NEWHAND_MEDIATOR, 0, NewhandMediator::INIT_BUTTONS);

	//	_cdList->onClose(0);
	//}
}

void MainUIMediator::getMainUIInfo()
{
	GameServerSocket* _wSocket = GameServerSocket::getInstance();


	CCMD29D pCCMD29D;
	_wSocket->sendMessage(&pCCMD29D);

	CCMD2EC pCCMD2EC;
	_wSocket->sendMessage(&pCCMD2EC);
}

void MainUIMediator::mineOpenTime(SCMD2ED* param)
{
	//_wSocket.removeCmdListener(SocketCMDConst::WMSG_SILVERMINE_OPENTIME, mineOpenTime);
			
	SilverMineManage::Instance()->setmineStartTime(param->a_time);   // 秒为单位 
	SilverMineManage::Instance()->setmineEndTime(param->a_time + 30*60); // 半个小时 
			
	SilverMineManage::Instance()->setgongStartTime(param->b_timeGong);   // 秒为单位 
	SilverMineManage::Instance()->setgongEndTime(param->b_timeGong + 30*60); // 半个小时 
			
	stepMineTime(0);
	CDManage::Instance()->addTimerHandle(  schedule_selector(MainUIMediator::stepMineTime), this );

	stepGongTime(0);
	CDManage::Instance()->addTimerHandle(  schedule_selector(MainUIMediator::stepGongTime), this );
}

void MainUIMediator::stepMineTime(float dt)
{
	Number clientTime = CDManage::Instance()->getServerTime()/1000;
	Number mineStartTime = SilverMineManage::Instance()->getmineStartTime();
	Number mineEndTime =  SilverMineManage::Instance()->getmineEndTime();
			
	if(mineStartTime <= clientTime && clientTime <= mineEndTime){
		g_pGlobalManage->inMineTime(true); 
	}
	else {
		g_pGlobalManage->inMineTime(false); 
				
		if( clientTime > SilverMineManage::Instance()->getmineEndTime()){
			// remove step cause  new time of mine will update till tomorrow
			CDManage::Instance()->removeTimerHandle(schedule_selector(MainUIMediator::stepMineTime), this);
		}
		else if(clientTime < mineStartTime){
			// just wait for mine
		}
	}

}
		

void MainUIMediator::stepGongTime(float dt)
{
	Number clientTime = CDManage::Instance()->getServerTime()/1000;
	Number gongStartTime = SilverMineManage::Instance()->getgongStartTime();
	Number gongEndTime =  SilverMineManage::Instance()->getgongEndTime();

	if(gongStartTime <= clientTime && clientTime <= gongEndTime){
		g_pGlobalManage->inGongTime(true); 
	}
	else
	{
		g_pGlobalManage->inGongTime(false); 
				
		if( clientTime > SilverMineManage::Instance()->getgongEndTime()){
			// remove step cause  new time of mine will update till tomorrow
			CDManage::Instance()->removeTimerHandle(schedule_selector(MainUIMediator::stepGongTime), this);
		}
		else if(clientTime < gongStartTime){
			// just wait for mine
		}
	}
}

void MainUIMediator::startUpSecondaryNavigate()
{
	if(!_secNavigate)
	{
		_secNavigate = new SecNavigate();
		ViewManager::getInstance()->_secNavigate = _secNavigate;

		LayerManager::sceneUILayer->addChild(_secNavigate);
		//startUPOnlineRewardView();
		sendNotification(Facade_Mediator, AppFacade_NEWHAND_MEDIATOR, 0, NewhandMediator::INIT_BUTTONS);
	}
}

void MainUIMediator::onRequestEnergy()
{
	CCMD21E * cmd = new CCMD21E();
	if (cmd)
	{
		GameServerSocket * pSocket = GameServerSocket::getInstance();
		if (pSocket)
		{
			pSocket->sendMessage(cmd);
			CC_SAFE_DELETE(cmd); // LH0712LEAK
		}
	}
}

void MainUIMediator::onAddEnergy()
{
	CCMD21D * cmd = new CCMD21D();
	if (cmd)
	{
		GameServerSocket * pSocket = GameServerSocket::getInstance();
		if (pSocket)
		{
			pSocket->sendMessage(cmd);
		}
	}
}

void MainUIMediator::initBuyEnergy(char *pPacket)
{
	if (_roleUI)
	{
		_roleUI->onAddHandler((SCMD21F*)pPacket,0);
	}
}

void MainUIMediator::updateEnergy(char * pPacket)
{
	SCMD188 * cmd = (SCMD188 *)pPacket;
	RoleManage::Instance()->_accountInfo._energy = cmd->a_presentEnergy;
	RoleManage::Instance()->_accountInfo.vigourBuffCount(cmd->c_remainVigourBuffCount);
	if (_roleUI)
	{
		_roleUI->setEnergy(cmd->a_presentEnergy,MAX_ENERGY);
		_roleUI->setVigourBuffCount(cmd->c_remainVigourBuffCount, cmd->d_maxVigourBuffCount);
	}
}


/**
* ∏¸–¬“¯±“ 
* @param param
* 
*/
void MainUIMediator::updateSliverHandler(char * pPacket)
{
	FightProxy* _fightProxy = (FightProxy*)g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
	if(!_fightProxy)
		return;

	if(_fightProxy->battleId!=0)
	{
		UpdateSilverAction* callback = new UpdateSilverAction();
		callback->init(pPacket,_roleUI);
		
		_fightProxy->_bData._callbacks.push_back(callback);
	}
	else
	{
		UpdateSilverAction callback = UpdateSilverAction();
		callback.init(pPacket,_roleUI);
		callback.doAction();
       // callback->release();
	}			
}


/**
* @param param
*/	
void MainUIMediator::updateGoldHandler(char * pPacket)
{
	// by longhui
	SCMD18D * cmd = (SCMD18D *)pPacket;
	RoleManage::Instance()->_accountInfo._gold = cmd->a_newvalue;
	if (_roleUI)
	{
		_roleUI->setGold(cmd->a_newvalue);
		RoleManage::Instance()->_accountInfo.gold((int)cmd->a_newvalue);
	}

	// by 
	if(  (cmd->b_diffvalue > 0) && (cmd->c_isShow>0)  )
	{
		Message::Instance()->show( LangManager::getText("MUI097",cmd->b_diffvalue), ccc3(0xFF, 0xFF, 0x33) );
	}
	else if( (cmd->b_diffvalue<0) && (cmd->c_isShow>0) )
	{
		Message::Instance()->show( LangManager::getText("MUI098", abs(cmd->b_diffvalue)) );	
	}	

	//RoleManage::Instance()->accountInfo()->gold( cmd->a_newvalue );

	if (ViewManager::getInstance()->_peiyangView)
	{
		ViewManager::getInstance()->_peiyangView->updateGold();
	}
}

void MainUIMediator::updatePracticeHandler(char * pPacket)
{
	/*
	SCMD18E * cmd = (SCMD18E *)pPacket;
	RoleManage::Instance()->_accountInfo._practice = cmd->a_newvalue;
	if (_roleUI)
	{
		_roleUI->setPrictice(cmd->a_newvalue);
	}*/
	FightProxy* _fightProxy = (FightProxy*)g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
	if(!_fightProxy)
		return;


	if(_fightProxy->battleId!=0)
	{
		UpdatePraceticeAction* callback = new UpdatePraceticeAction();
		callback->init(pPacket,_roleUI);
		
		_fightProxy->_bData._callbacks.push_back(callback);
	}
	else
	{
		UpdatePraceticeAction callback;
		callback.init(pPacket,_roleUI);
		callback.doAction();
	}


	if (ViewManager::getInstance()->_upSkillView)
	{
		ViewManager::getInstance()->_upSkillView->updatePractice();
	}
	if (ViewManager::getInstance()->_peiyangView)
	{
		ViewManager::getInstance()->_peiyangView->updatePractice();
	}
}

/**
	* 更新名声
	* @param param
	* 
	*/	
void MainUIMediator::updatePopularityHandler(char * pPacket)
{
	FightProxy* _fightProxy = (FightProxy*)g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
	if(!_fightProxy)
		return;


	if(_fightProxy->battleId!=0)
	{
		UpdatePopularityAction* callback = new UpdatePopularityAction();
		callback->init(pPacket,_roleUI);
		
		_fightProxy->_bData._callbacks.push_back(callback);
	}
	else
	{
		UpdatePopularityAction callback;
		callback.init(pPacket,_roleUI);
		callback.doAction();
	}
}


void MainUIMediator::updateGoodsDynamic( SCMD16F* param )
{
	sendNotification( Facade_Command, AppFacade_COM_PROXY_CHANGE, (char*)param, ComProxyCommand::UPDATE_GOODS_DYNAMIC );
}

/**
* –¬ ÷“˝µº√‚∑—ƒ‹∑Ò√‚∑—«ÂCD 
* @param param
*/
void MainUIMediator::freeClearCDHandler( SCMD1DF* param )
{			
//	CDManage.freeDic[param.a_cdType.value] = 1;
//	if(_cdList)
//	_cdList.addFreeGuildByType(param.a_cdType.value);
//			
//	switch(param.a_cdType.value){
////				case CDManage.TRAINING:
////					var trainMediator:TrainViewMediator = this.facade.retrieveMediator(TrainViewMediator.NAME) as TrainViewMediator;
////					if(trainMediator.trainView)
////						trainMediator.trainView.addFreeCDArrow();
////					break;
//		case CDManage.STRENGTHEN:
//			var strengMediator:MainStrengMediator = this.facade.retrieveMediator(MainStrengMediator.NAME) as MainStrengMediator;
//			if(strengMediator.strengPanel)
//				strengMediator.strengPanel.addFreeCDArrow();
//			break;
//	}
}

void MainUIMediator::startListener()
{
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_WORLD_TIME_BROADCAST, gameTimeHandler);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_WORLD_CLEAR_CD_RESULT,delCDHandler);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_WORLD_UPDATE_CD,updateCDHandler);

	//_wSocket.addCmdListener(SocketCMDConst.WMSG_WORLD_UPDATE_HP, updateHpHandler);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_UPDATE_SILVER,updateSilverHandler);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_UPDATE_GOLD,updateGoldHandler);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_WORLD_REQ_ENCHANT_INFO,updateStoneHandler);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_UPDATE_VIGOUR,updateEnergy);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_UPDATE_PRACTICE,updatePracticeHandler);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_UPDATE_POPULARITY,updatePopularityHandler);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_WORLD_ITEM_INFO, updateGoodsDynamic);

	//_wSocket.addCmdListener(SocketCMDConst.WMSG_WORLD_ONLINE_AWARD_INFO_RETURN, initRewardOnline);//初始化在线奖励
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_WORLD_ACTIVEDAY_AWARD_INFO_RESP, initRewardActivity);//活跃天数
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_WORLD_BUY_VIGOUR_INFO_RESP,initBuyEnergy);
	//_wSocket.addCmdListener(SocketCMDConst.XMSG_ERROR_RESPONSE, errorResponse);
	//_gSocket.addCmdListener(SocketCMDConst.XMSG_ERROR_RESPONSE, errorResponse); // _gateSocket也有统一错误包 

	//_wSocket.addCmdListener(SocketCMDConst.WMSG_WORLD_FCM_UPDATE,onIndulgeHandler);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_WORLD_GUIDE_CDCONDITION, freeClearCDHandler);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_WORLD_GET_THREATEN_RESP, updateThreatenHandler);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_WORLD_VIP_AWARD_INFO_RESP, vipReceiveGoldHandler);//vip领金币

	//_wSocket.addCmdListener(SocketCMDConst.WMSG_SILVERMINE_OPENTIME, mineOpenTime);  // 银矿时间 

	RoleManage *pRoleManage = RoleManage::Instance();
	AccountInfoVo *pAccountInfo = pRoleManage->accountInfo();
	if(pAccountInfo)
	{
		pAccountInfo->addEventListener(Event::CHANGE_VIPLEV, this, callfuncND_selector(MainUIMediator::changeVipLev));
	}
	//_roleManage.roleInfo.playerBaseInfo.addEventListener(LiveThingVo.CHANGELEV, changeRoleLevHandler);	//监听角色等级更新
	//_roleManage.roleInfo.playerBaseInfo.addEventListener(PlayerBaseVo.CHANGEEXP, changeRoleExpHandler);	//监听角色等级更新
	//_roleManage.accountInfo.addEventListener(AccountInfoVo.CHANGE_CRYSTAL_LEV, mainCrystalLevHandler);

	//_roleManage.roleInfo.playerBaseInfo.addEventListener(LiveThingVo.CHANGEHP, changeHpHandler);	//监听角色血量更新
	//_roleManage.roleInfo.playerBaseInfo.addEventListener(LiveThingVo.CHANGEMAXHP, changeHpHandler);	//监听角色血量上限更新
	//_roleManage.accountInfo.addEventListener(AccountInfoVo.CHANGE_ENERGY, changeEnergyHandler);	//监听角色精力更新
	//_roleManage.accountInfo.addEventListener(AccountInfoVo.CHANGE_SILVER_LIM, changeSilverLim);		//监听银币上限更新
	//_roleManage.accountInfo.addEventListener(AccountInfoVo.CHANGE_VIPLEV, changeVipLev);		//监听VIP等级更新
	////			_roleManage.accountInfo.addEventListener(AccountInfoVo.CHANGE_CRYSTAL_LEV, changeCrystalLev);	
	//_roleManage.accountInfo.addEventListener(AccountInfoVo.CHANGE_GOLDCOUNT, changeGoldCount);

	//_roleUI.addEventListener(RoleUI.ADD_ENERGY,onAddEnergy);

	//_dispatcher.addEventListener(GameDispatcher.REQ_ENERGY,onRequestEnergy);
	//_dispatcher.addEventListener(GameDispatcher.VIEW_GOOD, viewGoodsInfoHandler);
	////			_dispatcher.addEventListener(GameDispatcher.DEL_FREECD_ARROW, delFreeCDArrorHandler);
	//_dispatcher.addEventListener(GameDispatcher.SHOW_WORLD_SCENE, showWorldSceneHandler);

	//_indulge.addEventListener(IndulgeNotice.CLEAR_COUNT,onClearCount);
	//_indulge.addEventListener(IndulgeNotice.FCM_STAGE,FcmTypeChange);
	//_dispatcher.addEventListener(GameDispatcher.SHOW_FCM,onFCMHandler);
	//_globalManage.addEventListener(GlobalManage.FCM_STATE_CHANGE, onFCMChange);
}

void MainUIMediator::changeVipLev( CCNode *pNode, void *pData )
{
	if((_roleUI = ViewManager::getInstance()->_roleUI) != NULL)
	{
		AccountInfoVo *pAccountInfo = RoleManage::Instance()->accountInfo();
		if(pAccountInfo)
		{
			_roleUI->setVipLev(pAccountInfo->vipLev());
			if(ViewManager::getInstance()->_pDailyTaskExView)
			{
				ViewManager::getInstance()->_pDailyTaskExView->onVipChanged();
			}
		}
	}
}

void MainUIMediator::updateStoneHandler( SCMD2D5* param )
{
	if(param->a_add > 0){
		Message::Instance()->show(LangManager::getText("MUI099",param->a_add));
	}
	else if(param->a_add < 0){
		Message::Instance()->show(  LangManager::getText("MUI100",  abs( param->a_add ) )  );	
	}
	RoleManage::Instance()->accountInfo()->stone( param->b_num );
}


//added by chenjian Begin
void MainUIMediator::startupReportUI(int mapId)
{
	closeReportUI();
	if (_secNavigate)
	{
		_secNavigate->setIsReportBtnVisible(true);
	}
}

void MainUIMediator::closeReportUI()
{
	if (_secNavigate)
	{
		_secNavigate->setIsReportBtnVisible(false);
	}
}

void MainUIMediator::setReportUIVisible(bool visible)
{
	if (_secNavigate)
	{
		_secNavigate->setIsReportBtnVisible(true);
	}
}

void MainUIMediator::startUpTokenBar()
{
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_WORLD_FREE_TOKEN_INFO_RESP, updateTokenInfo);
	CCMD24E cmd;
	GameServerSocket::getInstance()->sendMessage( &cmd/*SocketCMDConst.CMSG_WORLD_FREE_TOKEN_INFO_REQUEST*/);		//请求免费令牌信息
}

void MainUIMediator::updateTokenInfo(SCMD24F* cmd)
{
	std::list<SCMD24FNode>::iterator it = cmd->a_tokens.begin();
	for (; it!=cmd->a_tokens.end();it++)
	{
		SCMD24FNode node = *it;
		TokenManager::Instance()->updateToken(node.a_type, node.b_num);
	}
}

//added by chenjian End