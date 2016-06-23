#include "CityTraderMediator.h"
#include "manager/PopEventName.h"
#include "events/GameDispatcher.h"
#include "manager/ViewManager.h"
#include "manager/CDManage.h"
#include "socket/command/c2b/CCMD2B0.h"
#include "socket/command/c2b/CCMD2B5.h"
#include "control/trader/TraderProxyCommand.h"
#include "socket/command/c2b/CCMD2BD.h"
#include "model/trader/vo/CityPriceVo.h"
#include "model/trader/TraderManager.h"
#include "socket/command/c2c/CCMD2C1.h"
#include "socket/command/c2b/CCMD2B8.h"
#include "socket/command/c2b/CCMD2BC.h"
#include "socket/command/c2b/CCMD2BA.h"
#include "model/trader/TraderProxy.h"
#include "socket/command/c2c/CCMD2C2.h"
#include "socket/command/c2b/CCMD2BE.h"
#include "../scene/SceneMediator.h"
#include "mvc/Facade.h"
#include "model/scene/ExitManager.h"
#include "socket/command/s11/SCMD111.h"
#include "util/TileUtil.h"
#include "socket/command/c12/CCMD12C.h"
#include "manager/GlobalManage.h"
#include "../notify/NotifyManager.h"
#include "../notify/NotifyType.h"
#include "socket/command/c28/CCMD28E.h"
#include "model/scene/NPCManager.h"
#include "socket/command/c0f/CCMD0F3.h"

extern CityTraderMediator* g_pCityTraderMediator = 0;

CityTraderMediator::CityTraderMediator()
{
	_sequence = 1;

	GameDispatcher::getInstance()->addEventListener( PopEventName::SHOW_UI_CITY_TRADER,
		this, callfuncND_selector(CityTraderMediator::initTrader) );
	GameDispatcher::getInstance()->addEventListener( GameDispatcher::SHOW_ROB_INFO,
		this, callfuncND_selector(CityTraderMediator::initRob) );

	g_pCityTraderMediator = this;
	_initListener = false;

	_traderView = 0;
	_traderProxy = 0;
	_robPanel = 0;
	_myRobPanel = 0;
	_type = 0;
	_traderViewType = 0;
}

void CityTraderMediator::handleNotification( int M2Vcmd, char* data )
{
	if (!_traderProxy)
	{
		_traderProxy = (TraderProxy*)g_pFacade->retrieveProxy( AppFacade_CITY_TRADER_CHANGE );
	}
	switch(M2Vcmd)
	{
	case UPDATE_HISTORY_LIST:
		updateHistory();
		break;
	case UPDATE_GOODS_LIST:
		updateGoods();
		break;
	case UPDATE_BANK_LIST:
		updateBank();
		break;
	case UPDATE_EVENT_LIST:
		updateEvent();
		break;
	case UPDATE_CITY_PRICE_LIST:
		updateCity();
		break;
	case END_BUSINESS_PROCESS:
		reqEndBusiness();
		break;
	case START_RUNNING_BUSINESS:
		startRunningBusiness( (FindVo*)data );
		break;
	}
}

void CityTraderMediator::initTrader(CCNode* n, void* data){
	_type = *(int*)data;
	openHandler();	
}
		
void CityTraderMediator::initRob(CCNode* n, void* data){
	struct StructTemp
	{
		int id;
		string name;
		int lv;
		int type;
	} param;
	param = *(StructTemp*)data;

	_type =param.type;
	_name = param.name;
	_id   = param.id;
	_lv   = param.lv;
	openHandler();
}
		
void CityTraderMediator::openHandler(){
	//if(_initListener == false){
	//	initSocketListener();
	//	_initListener = true;
	//}
	//ModuleLoaderManage.getInstance().load(ResourceName.BUSINESS_PATH, LoadLevel.HIGH, open);
	open();
}

void CityTraderMediator::open(){

	CCMD2B0 cmd2b0;
	GameServerSocket::getInstance()->sendMessage(&cmd2b0/*SocketCMDConst.CMSG_WORLD_TRADE_INIT*/);
	LayerManager::loadingPic->socketWait_old( WMSG_WORLD_TRADE_QUEUE );

	if(_type==1)
	{
		//openTraderView();
	}
	else if (_type==2){
		//openRob();
		CCMD2BE cmd;
		cmd.a_id = _id;
		GameServerSocket::getInstance()->sendMessage(/*SocketCMDConst.CMSG_WORLD_TRADE_INFO*/ &cmd );

		CCMD28E cmd28e;
		cmd28e.accId = _id;
		GameServerSocket::getInstance()->sendMessage(/*SocketCMDConst.*/ &cmd28e );
	}
	else
	{
		//openMyRob();
	}
}

void CityTraderMediator::openTraderView(){
	if(!_traderView){
		_traderView =new TraderView();
		_traderView->init();
		initViewListeners();
		ViewManager::getInstance()->traderView = _traderView;
		_traderView->setisPop(true);
		_traderView->release();
	}

	if (_traderView)
	{
		CC_SAFE_DELETE(_traderProxy->selectedVo);
		SceneProxy* _sceneProxy = (SceneProxy*)g_pFacade->retrieveProxy( AppFacade_SCENE_PROXY );
		_traderProxy->selectedVo = _traderView->getHighestPrice(_traderProxy->_cityPriceList
			, _sceneProxy->sceneInfoVo()->id);
		TraderManager::Instance()->setselectedVo(_traderProxy->selectedVo);
	}
	//CCMD2B5 cmd2b5;
	//GameServerSocket::getInstance()->sendMessage(&cmd2b5/*SocketCMDConst.CMSG_WORLD_TRADE_PRICE*/);
}

void CityTraderMediator::openMyRob(){

 	//CCMD2B0 cmd2b0;
	//GameServerSocket::getInstance()->sendMessage(&cmd2b0/*SocketCMDConst.CMSG_WORLD_TRADE_INIT*/);

	if(!_myRobPanel){
		_myRobPanel = new MyRobPanel();
		_myRobPanel->init();

		//_traderView->addEventListener(TraderView::OPEN_CITY_PANEL,
		//	this, callfuncND_selector(CityTraderMediator::openCityPanel));

		_myRobPanel->setisPop(true);
		_myRobPanel->release();

		//CCMD2BE cmd;
		//cmd.a_id = _id;
		//GameServerSocket::getInstance()->sendMessage(/*SocketCMDConst.CMSG_WORLD_TRADE_INFO*/ &cmd );
	}
	//else{
	//	_myRobPanel->setisPop(!_myRobPanel->getisPop());
	//}
}

void CityTraderMediator::openRob(){
	//CCMD2B0 cmd2b0;
	//GameServerSocket::getInstance()->sendMessage(&cmd2b0/*SocketCMDConst.CMSG_WORLD_TRADE_INIT*/);

	if(!_robPanel){
		_robPanel = new RobPanel();
		_robPanel->init();

		//_traderView->addEventListener(TraderView::OPEN_CITY_PANEL,
		//	this, callfuncND_selector(CityTraderMediator::openCityPanel));

		_robPanel->addEventListener(RobPanel::ROB_THAT_SON_OF_BITCH,
			this, callfuncND_selector(CityTraderMediator::robHim) );
		_robPanel->addEventListener(PopContainer::CLOSE_CONTAINER,
			this, callfuncND_selector(CityTraderMediator::closeHandler ));
		_robPanel->setisPop(true);
		_robPanel->release();
	}
	//else{
	//	_robPanel->setisPop(!_robPanel->getisPop());
	//}
}
	
void CityTraderMediator::closeHandler(CCNode* n, void* data){
	//_robPanel.removeEventListener(RobPanel.ROB_THAT_SON_OF_BITCH,robHim);
	//_robPanel.removeEventListener(PopContainer.CLOSE_CONTAINER,closeHandler);
	//this.sendNotification(SceneMediator.CANCEL_CLICK_TARGET);
	//_robPanel  =null;
} 

void CityTraderMediator::initViewListeners(){
	_traderView->addEventListener(TraderView::OPEN_CITY_PANEL,
		this, callfuncND_selector(CityTraderMediator::openCityPanel));
	_traderView->addEventListener(TraderView::REFRESH_GOODS,
		this, callfuncND_selector(CityTraderMediator::refreshHandler));

	_traderView->addEventListener(TraderView::BUY_ITEM,
		this, callfuncND_selector(CityTraderMediator::buyHandler));
	_traderView->addEventListener(TraderView::GO_TRADE,
		this, callfuncND_selector(CityTraderMediator::goTradeHandler));
	_traderView->addEventListener(TraderView::UNLOCK_BANKS,
		this, callfuncND_selector(CityTraderMediator::unlockHandler));
			
}

/**==========================返回处理后的数据进行面板更新==========================*/

void CityTraderMediator::updateHistory(){
	_traderView->historyChange(_traderProxy->_historyList);
}

void CityTraderMediator::updateGoods(){

	if(_type==1)
	{
		_traderViewType = 1;
		openTraderView();
	}
	else if (_type==2){
		_traderViewType = 2;
		openRob();	
	}
	else if (_type==3)
	{
		_traderViewType = 3;
		openMyRob();
	}
	else
	{
		if (_type==4)
		{
			_traderViewType = 4;
			openTraderView();
		}
	}
	_type = 0;
	if (_traderView)
	{
		_traderView->showTraderGoods(_traderProxy->_itemList);
	}
	if (_robPanel)
	{
		_robPanel->updateData();
	}
}
void CityTraderMediator::updateBank(){
	if (_traderView)
	{
		_traderView->showBankGoods(_traderProxy->_bankList);
	}
//			_traderView->buyNumChange(_traderProxy->buyNum);	
}
void CityTraderMediator::updateEvent(){
	_traderView->eventChange(_traderProxy->_eventList);
}

void CityTraderMediator::updateCity(){

	//if(_cityPanel){
	//	_cityPanel.updateList(_traderProxy->_cityPrice);				
	//}
}

/**==========================处理服务端返回的数据==========================*/
void CityTraderMediator::eventListHandler( SCMD2B1* param ){
	sendNotification(Facade_Command,
		AppFacade_CITY_TRADER_CHANGE, (char*)param, TraderProxyCommand::CREATE_EVENT_LIST);
} 
		
void CityTraderMediator::goodsListHandler(SCMD2B2* param ){
	sendNotification(Facade_Command,
		AppFacade_CITY_TRADER_CHANGE, (char*)param, TraderProxyCommand::CREATE_GOODS_LIST);
}
		
void CityTraderMediator::bankListHandler(SCMD2B3* param){
	sendNotification(Facade_Command,
		AppFacade_CITY_TRADER_CHANGE, (char*)param, TraderProxyCommand::CREATE_BANK_LIST);

	if (_traderView)
	{
		_traderView->buyNumChange(param->a_buyNum);		
	}

	TraderProxy* _traderProxy = (TraderProxy*)g_pFacade->retrieveProxy(AppFacade_CITY_TRADER_CHANGE);
	if (_traderProxy)
	{
		_traderProxy->_restTraderCnt = param->a_buyNum;

		if (_traderProxy && (_traderProxy->_restTraderCnt==0) )
		{
			SecNavigate * pSecNav = (SecNavigate *)ViewManager::getInstance()->_secNavigate;
			if (pSecNav)
			{
				pSecNav->removeButton(SecNavigate::TAG_TRADER);
			}
		}
	}
}

void CityTraderMediator::historyListHandler(SCMD2B4* param){
	sendNotification(Facade_Command,
		AppFacade_CITY_TRADER_CHANGE, (char*)param, TraderProxyCommand::CREATE_HISTORY_LIST);
}

void CityTraderMediator::cityPriceHandler(SCMD2B6* param){
	sendNotification(Facade_Command,
		AppFacade_CITY_TRADER_CHANGE, (char*)param, TraderProxyCommand::CREATE_CITY_PRICE_LIST);
}
		
void CityTraderMediator::reachEventHandler(SCMD2B7* param){
	//DisplayObjectManager.traderEventAchieve(param);
}
		
void CityTraderMediator::startBusiness(SCMD2B9* param){
	if(param->a_err == 0)
		_traderView->setisPop(false);
	sendNotification(Facade_Command,
		AppFacade_CITY_TRADER_CHANGE, (char*)param, TraderProxyCommand::START_BUSINESS);
}
		
void CityTraderMediator::endBusiness(SCMD2BB* param){
	sendNotification(Facade_Command,
		AppFacade_CITY_TRADER_CHANGE, (char*)param, TraderProxyCommand::END_BUSINESS);

	_msgDic.clear();
	if (param->a_err==0)
	{
		NotifyManager::Instance()->removeLayerByType(NotifyType::NType_Trader);
		SecNavigate * pSecNav = (SecNavigate *)ViewManager::getInstance()->_secNavigate;
		if (pSecNav)
		{
			TraderProxy* _traderProxy = (TraderProxy*)g_pFacade->retrieveProxy(AppFacade_CITY_TRADER_CHANGE);
			if (_traderProxy && (_traderProxy->_restTraderCnt-1==0) )
			{
				pSecNav->removeButton(SecNavigate::TAG_TRADER);
			}
			//else
			//{
			//	CCMD2B0 cmd2b0;
			//	GameServerSocket::getInstance()->sendMessage(&cmd2b0/*SocketCMDConst.CMSG_WORLD_TRADE_INIT*/);
			//	LayerManager::loadingPic->socketWait_old( WMSG_WORLD_TRADE_QUEUE );
			//}
		}
	}
}
		
void CityTraderMediator::robInfoPop(SCMD2BF* cmd){
/*	if(_robPanel){
		_robPanel.init(cmd);
	}	*/		
}
/**
	*  1：系统内部错误。（可以不显示给玩家，只显示劫商失败）
	2：精力和劫商令不足
	3：发送的被劫玩家ID错误。（可以不显示给玩家，只显示劫商失败）
	4：被劫玩家超过被劫次数
	5：玩家战斗cd中
	6：cd
	7：请求被劫的玩家不在跑商过程中，或正在被其他玩家打劫 
	* 
	* 
	*/		
void CityTraderMediator::robReply(SCMD2C3* cmd){
	switch (cmd->b_result){
		case 1:
			LangManager::msgShow("TRD022");
			break;
		case 2:
			LangManager::msgShow("TRD023");
			break;
		case 4:
			LangManager::msgShow("TRD024");
			break;
		case 5:
			LangManager::msgShow("TRD025");
			break;
		case 6:
			LangManager::msgShow("TRD102");
			break;
		case 7:
			LangManager::msgShow("TRD103");
			break;
	}
	
}
		
void CityTraderMediator::robResultHandler(SCMD2C4* cmd){
	//if(_fightProxy.battleId!=0){
 //		_fightProxy._bData._callbacks.push(new RobResultAction(cmd));
	//}
	//else{
	//	new RobResultAction(cmd).doAction();
	//}
	if (cmd->c_doubleType==1)
	{
		LangManager::msgShow("TRD104");
	}
	else if (cmd->c_doubleType==2)
	{
		LangManager::msgShow("TRD105");
	}
}
		
void CityTraderMediator::robNoteHandler(SCMD2C5* cmd){

	//var alertBtn:SimpleButton = Reflection.createInstance("ePointMsg3");
	//alertBtn.name = _sequence.toString();
	//LayerManager.sceneUILayer.addChild(alertBtn);
	//alertBtn.addEventListener(MouseEvent.CLICK,showMsg);
	//_noteArr.push(alertBtn);
	//_msgDic[_sequence] = cmd;
	//_num++;
	//_sequence++;
	//tweenThatFucker(alertBtn);
	_msgDic.push_back(*cmd);

	if (_myRobPanel)
	{
		_myRobPanel->updateData();
	}

	NotifyManager::Instance()->addNotification(NotifyType::NType_Trader);
}
//	
//void CityTraderMediator::tweenThatFucker(btn:SimpleButton){
//		var desx:int =  (_num-1)*36 +500;
//		var desy:int =  500;
//		tween1 = new TweenLite(btn,0.6,{x:desx,y:desy});
//}
//		
//void CityTraderMediator::tweenMoveHandler(targetbtn:SimpleButton){
//	var group:TweenGroup = new TweenGroup();
//	var tween:TweenLite;
//	for each(var  btn:SimpleButton in _noteArr){
//		if(int(btn.name)<=int(targetbtn.name)) continue;
//		tween = new TweenLite(btn, 0.5, {x:"-36"});
//		group.tweens.push(tween);
//	}
//	group.align = TweenGroup.ALIGN_START;
//
//}
		
//
//void CityTraderMediator::showMsg(e:MouseEvent){
//	var myName:String = RoleManage.getInstance().accountInfo.name;
//	var cmd:SCMD2C5 = _msgDic[int(e.target.name)];
//	var param:CCMD134 =new CCMD134;
//	param->a_battleId1 = cmd->e_reportId_1;
//	param->b_battleId2 = cmd->f_reportId_2;
//	_noticeManage.noticeBuilder(cmd->b_name,NoticeManager.TRADER_NOTE,param,(cmd->d_lostNum)*(_traderProxy->selectedVo.cityPrice));
////			var str:String = "<font color='#FFCC00'>"+cmd->b_name+"</font>"+" 打劫了你，"+"你的商队运输货物损失"+"<font color='#FF0000'>"+cmd->d_lostNum+"个"+"</font>"+"，是否查看战报"
////			Alert.show(str,"",1,watchThatDamnReport,null,null,null,param,null,5);
//	tweenMoveHandler(e.target as SimpleButton);
//	e.target.removeEventListener(MouseEvent.CLICK,showMsg);
//	if(e.target){
//		e.target.parent.removeChild(e.target);
//	}
//	_num--;
//}

void CityTraderMediator::watchThatDamnReport(CCMD134* param){
	//GameServerSocket::getInstance()->sendMessage(SocketCMDConst.CMSG_WORLD_BATTLE_REPORT_REQUEST, param);

}

void CityTraderMediator::updateRobInfoGet( SCMD28F* param )
{
	if (_robPanel)
	{
		_robPanel->updateGetInfo(param->a_sil, param->b_pop, param->c_beated, param->d_BuyTokenCnt);
	}
}

/**==========================发出操作请求==========================*/
void CityTraderMediator::refreshHandler(CCNode* n, void* data){
	CCMD2BD cdm;
	GameServerSocket::getInstance()->sendMessage(&cdm/*SocketCMDConst.CMSG_WORLD_TRADE_REFLASH*/);
}

void CityTraderMediator::openCityPanel(CCNode* n, void* data){
	//if(!_cityPanel){
	//	_cityPanel = new CitySelectPanel();
	//} 
	//_cityPanel.updateList(_traderProxy->cityPrice);
	//_cityPanel.isPop = true;
	//_cityPanel.addEventListener(CitySelectPanel.SELECT_CITY,citySelectHandler)
}
		
void CityTraderMediator::citySelectHandler(CCNode* n, void* data){
	CityPriceVo* vo = (CityPriceVo*)data;
	_traderView->cityChange(vo);
	_traderProxy->selectedVo = vo;
	TraderManager::Instance()->setselectedVo( vo );
}
		
void CityTraderMediator::buyHandler(CCNode* n, void* data){
	CCMD2C1 cmd;
	cmd.a_buy = *(int*)data;
	GameServerSocket::getInstance()->sendMessage(&cmd/*SocketCMDConst.CMSG_WORLD_TRADE_BUY*/);
}

void CityTraderMediator::goTradeHandler(CCNode* n, void* data){
	CCMD2B8 cmd;
	cmd.a_mapId = *(int*)data;
	GameServerSocket::getInstance()->sendMessage(&cmd);
	//GameServerSocket::getInstance()->sendMessage(SocketCMDConst.CMSG_WORLD_TRADE_BEGIN,e.param as int);
}

void CityTraderMediator::unlockHandler(CCNode* n, void* data){
	CCMD2BC cmd;
	cmd.a = *(int*)data;
	GameServerSocket::getInstance()->sendMessage(&cmd);
	//GameServerSocket::getInstance()->sendMessage(SocketCMDConst.CMSG_WORLD_TRADE_BANK_ADD,e.param as int);
}
		
void CityTraderMediator::reqEndBusiness(){
	return;
	CCMD2BA cmd;
	cmd.a_mapId = _traderProxy->selectedVo->mapId;
	GameServerSocket::getInstance()->sendMessage(&cmd);
	//GameServerSocket::getInstance()->sendMessage(SocketCMDConst.CMSG_WORLD_TRADE_END, _traderProxy->selectedVo->mapId);
}
		
void CityTraderMediator::robHim(CCNode* n, void* data){
	if(CDManage::Instance()->getLockBytype(CDManage::FIGHT)==1){
		LangManager::msgShow("TRD030");
		return;
	}
	CCMD2C2 cmd;
	cmd.a_trade = _id/**(int*)data*/;
	GameServerSocket::getInstance()->sendMessage(&cmd);
	//GameServerSocket::getInstance()->sendMessage(SocketCMDConst.CMSG_WORLD_TRADE_ATTACK_REQ,e.param as int)
}

CityTraderMediator::~CityTraderMediator()
{
	if (_traderProxy)
		CC_SAFE_DELETE(_traderProxy->selectedVo);
}

void CityTraderMediator::startRunningBusiness( FindVo* vo )
{
	CCMD12C cmd12c;
	CCMD0F3 cmd0f3;

	//SceneMediator* pMeditor = (SceneMediator*)g_pFacade->retrieveMediator(AppFacade_SCENE_MEDIATOR);
	SceneProxy* _sceneProxy = (SceneProxy*)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
	//Scene* pSce = pMeditor->_scene;
	//std::vector<int>* exitVec = ExitManager::Instance()->getExitsByMapId(_sceneProxy->sceneInfoVo()->id);
	//if ( exitVec&& (exitVec->begin() != exitVec->end() ))
	{
		//int id = *exitVec->begin();
		//char tmp[32] = {0};
		//std::string s = EXIT_TYPE;
		//sprintf(tmp, "%s%d", s.c_str(), id);
		//std::string tmp_str(tmp);
		//std::map<string, IElement*>::iterator iter = pSce->_elementDic.find(tmp);
		//Exit* exit = (Exit*)(iter->second);
		//CCPoint ePos = exit->getMapStartPoint();

		CCPoint startPoint = ccp( 6, 15);
		CCPoint endPoint = ccp( 47, 68);//TileUtil::Instance()->changePixsToTile(ePos);
		
		PlayerBaseVo playerVo;
		playerVo.accountId = RoleManage::Instance()->accountInfo()->accountId;
		playerVo.name = RoleManage::Instance()->accountInfo()->name;
		playerVo.x = startPoint.x;
		playerVo.y =  startPoint.y;
		playerVo._guildName = RoleManage::Instance()->roleInfo()->playerBaseInfo.guildName();
		playerVo._maxHp = 0;
		playerVo._hp = 0;
		playerVo.energy = 0;
		playerVo.mercId = RoleManage::Instance()->roleInfo()->playerBaseInfo.mercId;
		playerVo._lev = RoleManage::Instance()->roleLev();
		playerVo.threat = 0;
		playerVo._titleId = 0;
		playerVo._mapId = RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId;//
		/*_traderProxy->selectedVo->mapId*/;

		playerVo.cloth = 900;	// 1 run business image
		/*===================Add people to move the path=======================*/
		{
			SCMD111 movePath;
			movePath.a_AccountId = RoleManage::Instance()->accountInfo()->accountId;
			movePath.b_startX = startPoint.x;
			movePath.c_startY = startPoint.y;
			std::vector<CCPoint> searchResults;// = _sceneProxy->findPath(startPoint, endPoint);
			searchResults.push_back(ccp(6.0000000, 15.000000 ));
			searchResults.push_back(ccp(7.0000000, 16.000000 ));
			searchResults.push_back(ccp(8.0000000, 17.000000 ));
			searchResults.push_back(ccp(9.0000000, 18.000000 ));
			searchResults.push_back(ccp(10.000000, 19.000000 ));
			searchResults.push_back(ccp(11.000000, 20.000000 ));
			searchResults.push_back(ccp(12.000000, 21.000000 ));
			searchResults.push_back(ccp(13.000000, 22.000000 ));
			searchResults.push_back(ccp(14.000000, 23.000000 ));
			searchResults.push_back(ccp(15.000000, 24.000000 ));
			searchResults.push_back(ccp(16.000000, 25.000000 ));
			searchResults.push_back(ccp(17.000000, 26.000000 ));
			searchResults.push_back(ccp(18.000000, 27.000000 ));
			searchResults.push_back(ccp(19.000000, 28.000000 ));
			searchResults.push_back(ccp(20.000000, 29.000000 ));
			searchResults.push_back(ccp(21.000000, 30.000000 ));
			searchResults.push_back(ccp(22.000000, 31.000000 ));
			searchResults.push_back(ccp(23.000000, 32.000000 ));
			searchResults.push_back(ccp(24.000000, 33.000000 ));
			searchResults.push_back(ccp(25.000000, 34.000000 ));
			searchResults.push_back(ccp(26.000000, 34.000000 ));
			searchResults.push_back(ccp(27.000000, 35.000000 ));
			searchResults.push_back(ccp(28.000000, 36.000000 ));
			searchResults.push_back(ccp(29.000000, 37.000000 ));
			searchResults.push_back(ccp(30.000000, 38.000000 ));
			searchResults.push_back(ccp(31.000000, 39.000000 ));
			searchResults.push_back(ccp(31.000000, 40.000000 ));
			searchResults.push_back(ccp(31.000000, 41.000000 ));
			searchResults.push_back(ccp(31.000000, 42.000000 ));
			searchResults.push_back(ccp(31.000000, 43.000000 ));
			searchResults.push_back(ccp(31.000000, 44.000000 ));
			searchResults.push_back(ccp(31.000000, 45.000000 ));
			searchResults.push_back(ccp(32.000000, 46.000000 ));
			searchResults.push_back(ccp(33.000000, 47.000000 ));
			searchResults.push_back(ccp(34.000000, 48.000000 ));
			searchResults.push_back(ccp(35.000000, 49.000000 ));
			searchResults.push_back(ccp(36.000000, 50.000000 ));
			searchResults.push_back(ccp(37.000000, 51.000000 ));
			searchResults.push_back(ccp(38.000000, 52.000000 ));
			searchResults.push_back(ccp(39.000000, 53.000000 ));
			searchResults.push_back(ccp(40.000000, 54.000000 ));
			searchResults.push_back(ccp(41.000000, 55.000000 ));
			searchResults.push_back(ccp(42.000000, 56.000000 ));
			searchResults.push_back(ccp(43.000000, 57.000000 ));
			searchResults.push_back(ccp(44.000000, 58.000000 ));
			searchResults.push_back(ccp(45.000000, 59.000000 ));
			searchResults.push_back(ccp(46.000000, 60.000000 ));
			searchResults.push_back(ccp(46.000000, 61.000000 ));
			searchResults.push_back(ccp(46.000000, 62.000000 ));
			searchResults.push_back(ccp(46.000000, 63.000000 ));
			searchResults.push_back(ccp(46.000000, 64.000000 ));
			searchResults.push_back(ccp(46.000000, 65.000000 ));
			searchResults.push_back(ccp(46.000000, 66.000000 ));
			searchResults.push_back(ccp(46.000000, 67.000000 ));
			searchResults.push_back(ccp(47.000000, 68.000000 ));
			std::vector<SCMD111Node> d_path;
			for (int i = 0; i < searchResults.size(); i++)
			{
				SCMD111Node node;
				node.a_x = searchResults[i].x;
				node.b_y = searchResults[i].y;
				d_path.push_back(node);
			}
			movePath.d_path = d_path;
			playerVo.path = movePath;
		}

		cmd12c.d_path = playerVo.path.d_path;

		// skip map path
		SceneMediator* pMeditor = (SceneMediator*)g_pFacade->retrieveMediator(AppFacade_SCENE_MEDIATOR);
		do 
		{
			startPoint = ccp(63, 82)/*ccp(43, 94)*/;
			endPoint = ccp(24, 23);

			//TraderProxyCommand* tradeComand = (TraderProxyCommand*)g_pFacade->retrieveController(AppFacade_CITY_TRADER_CHANGE);
			//std::vector<CCPoint> searchResults = tradeComand->loadMapData(
			//	"assets/mapassets/scene/1002/map.xx", startPoint, endPoint);
			std::vector<CCPoint> searchResults;
			searchResults.push_back(ccp(63.000000, 82.000000));
			searchResults.push_back(ccp(62.000000, 81.000000));
			searchResults.push_back(ccp(60.000000, 79.000000));
			searchResults.push_back(ccp(59.000000, 78.000000));
			searchResults.push_back(ccp(58.000000, 77.000000));
			searchResults.push_back(ccp(57.000000, 76.000000));
			searchResults.push_back(ccp(56.000000, 75.000000));
			searchResults.push_back(ccp(55.000000, 74.000000));
			searchResults.push_back(ccp(54.000000, 73.000000));
			searchResults.push_back(ccp(53.000000, 72.000000));
			searchResults.push_back(ccp(52.000000, 71.000000));
			searchResults.push_back(ccp(51.000000, 70.000000));
			searchResults.push_back(ccp(50.000000, 69.000000));
			searchResults.push_back(ccp(49.000000, 68.000000));
			searchResults.push_back(ccp(48.000000, 67.000000));
			searchResults.push_back(ccp(47.000000, 66.000000));
			searchResults.push_back(ccp(46.000000, 65.000000));
			searchResults.push_back(ccp(45.000000, 64.000000));
			searchResults.push_back(ccp(44.000000, 63.000000));
			searchResults.push_back(ccp(43.000000, 62.000000));
			searchResults.push_back(ccp(42.000000, 61.000000));
			searchResults.push_back(ccp(41.000000, 60.000000));
			searchResults.push_back(ccp(40.000000, 59.000000));
			searchResults.push_back(ccp(39.000000, 58.000000));
			searchResults.push_back(ccp(38.000000, 57.000000));
			searchResults.push_back(ccp(37.000000, 56.000000));
			searchResults.push_back(ccp(36.000000, 55.000000));
			searchResults.push_back(ccp(35.000000, 54.000000));
			searchResults.push_back(ccp(34.000000, 53.000000));
			searchResults.push_back(ccp(33.000000, 52.000000));
			searchResults.push_back(ccp(32.000000, 51.000000));
			searchResults.push_back(ccp(31.000000, 50.000000));
			searchResults.push_back(ccp(30.000000, 49.000000));
			searchResults.push_back(ccp(29.000000, 48.000000));
			searchResults.push_back(ccp(28.000000, 47.000000));
			searchResults.push_back(ccp(27.000000, 46.000000));
			searchResults.push_back(ccp(26.000000, 45.000000));
			searchResults.push_back(ccp(25.000000, 44.000000));
			searchResults.push_back(ccp(25.000000, 43.000000));
			searchResults.push_back(ccp(25.000000, 42.000000));
			searchResults.push_back(ccp(25.000000, 41.000000));
			searchResults.push_back(ccp(25.000000, 40.000000));
			searchResults.push_back(ccp(25.000000, 39.000000));
			searchResults.push_back(ccp(25.000000, 38.000000));
			searchResults.push_back(ccp(25.000000, 37.000000));
			searchResults.push_back(ccp(25.000000, 36.000000));
			searchResults.push_back(ccp(25.000000, 35.000000));
			searchResults.push_back(ccp(25.000000, 34.000000));
			searchResults.push_back(ccp(25.000000, 33.000000));
			searchResults.push_back(ccp(25.000000, 32.000000));
			searchResults.push_back(ccp(25.000000, 31.000000));
			searchResults.push_back(ccp(25.000000, 30.000000));
			searchResults.push_back(ccp(25.000000, 29.000000));
			searchResults.push_back(ccp(25.000000, 28.000000));
			searchResults.push_back(ccp(25.000000, 27.000000));
			searchResults.push_back(ccp(25.000000, 26.000000));
			searchResults.push_back(ccp(25.000000, 25.000000));
			searchResults.push_back(ccp(25.000000, 24.000000));
			searchResults.push_back(ccp(24.000000, 23.000000));

			for (int i = 0; i < searchResults.size(); i++)
			{
				SCMD111Node node;
				node.a_x = searchResults[i].x;
				node.b_y = searchResults[i].y;
				cmd0f3.d_path.push_back(node);
			}
			//cmd0f3.a_mapId = _traderProxy->selectedVo->mapId;
			searchResults.clear();

			startPoint = ccp(34, 38);
			endPoint = ccp(22, 25);
			//searchResults = tradeComand->loadMapData("assets/mapassets/scene/1001/map.xx", startPoint, endPoint);
			searchResults.push_back(ccp(34.000000, 38.000000));
			searchResults.push_back(ccp(33.000000, 37.000000));
			searchResults.push_back(ccp(32.000000, 36.000000));
			searchResults.push_back(ccp(31.000000, 35.000000));
			searchResults.push_back(ccp(30.000000, 34.000000));
			searchResults.push_back(ccp(29.000000, 33.000000));
			searchResults.push_back(ccp(28.000000, 32.000000));
			searchResults.push_back(ccp(27.000000, 31.000000));
			searchResults.push_back(ccp(26.000000, 30.000000));
			searchResults.push_back(ccp(25.000000, 29.000000));
			searchResults.push_back(ccp(24.000000, 28.000000));
			searchResults.push_back(ccp(23.000000, 27.000000));
			searchResults.push_back(ccp(22.000000, 26.000000));
			searchResults.push_back(ccp(21.000000, 25.000000));
			searchResults.push_back(ccp(22.000000, 25.000000));

			for (int i = 0; i < searchResults.size(); i++)
			{
				SCMD111Node node;
				node.a_x = searchResults[i].x;
				node.b_y = searchResults[i].y;
				cmd0f3.e_path.push_back(node);
			}
		} while(0);

		GameServerSocket::getInstance()->sendMessage(&cmd12c);
		GameServerSocket::getInstance()->sendMessage(&cmd0f3);

		//g_pGlobalManage->_tradeMapLimit = true;

		//if(_sceneProxy)
		//	_sceneProxy->addTradePalyer(&playerVo);

		_traderProxy->_traderState = TraderProxy::Trader_State_City1;
		NotifyManager::Instance()->addNotification(NotifyType::NType_Trader);

		_msgDic.clear();
	}
	
}
