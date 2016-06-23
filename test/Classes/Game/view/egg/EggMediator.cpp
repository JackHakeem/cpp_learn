#include "EggMediator.h"
#include "socket/command/s40/SCMD401.h"
#include "socket/command/s40/SCMD403.h"
#include "socket/command/s40/SCMD405.h"
#include "socket/command/s40/SCMD407.h"
#include "socket/command/s40/SCMD409.h"
#include "socket/command/s40/SCMD40B.h"
#include "socket/command/s40/SCMD40D.h"
#include "socket/command/c40/CCMD400.h"
#include "socket/command/c40/CCMD40A.h"
#include "socket/command/c40/CCMD402.h"
#include "socket/command/c40/CCMD404.h"
#include "socket/command/c40/CCMD406.h"
#include "socket/command/c40/CCMD408.h"
#include "socket/command/c40/CCMD40C.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "control/egg/EggCommand.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "components/PoolView.h"
#include "manager/ViewManager.h"
#include "model/player/RoleManage.h"
#include "model/egg/EggProxy.h"
#include "manager/LayerManager.h"
#include "components/ReserveDepot.h"
#include "components/WashPanel.h"
#include "model/player/vo/AccountInfoVo.h"
#include "components/NumSelectBox.h"

EggMediator::EggMediator()
{
	/** 许愿池 */
	_poolView = 0;
	/** 心愿宝箱 */
	_depotView = 0;
	/** 洗礼面板 */
	_washPanel = 0;
	/** 拾取数量选择框 */
	_selectBox = 0;
	_eggProxy = 0;
	_roleManage = 0;

	_roleManage = RoleManage::Instance();
	_dispatcher = GameDispatcher::getInstance();

	_dispatcher->addEventListener(PopEventName::SHOW_UI_EGG_NUMBOX, this, callfuncND_selector(EggMediator::openNumSelectBox));
	/** 监听UI弹出框 */
	_dispatcher->addEventListener(PopEventName::SHOW_UI_EGG_POOL, this, callfuncND_selector(EggMediator::uiLoadHandler));
	_dispatcher->addEventListener(PopEventName::SHOW_UI_EGG_WASH, this, callfuncND_selector(EggMediator::openWashPanel));
	/** 监听开蛋事件 */
	_dispatcher->addEventListener(OPEN_EGG, this, callfuncND_selector(EggMediator::openEggHandler) );
	/** 监听洗礼事件 */
	_dispatcher->addEventListener(WASH_EGG, this, callfuncND_selector(EggMediator::washEggHandler) );
	/** 监听拾取事件 */
	_dispatcher->addEventListener(GET_EGG, this, callfuncND_selector(EggMediator::getEggHandler) );
	/** 监听一键拾取事件 */
	_dispatcher->addEventListener(GET_ALL, this, callfuncND_selector(EggMediator::getAllHandler) );

	_roleManage->accountInfo()->addEventListener(Event::CHANGE_GOLD, this, callfuncND_selector(EggMediator::changeGold));

	_eggProxy = (EggProxy*)g_pFacade->retrieveProxy(AppFacade_EGG_CHANGE);

	_dispatcher->addEventListener(PopEventName::SHOW_UI_EGG_DEPOT, this, callfuncND_selector(EggMediator::openDepot));

	initEvent();
}

EggMediator::~EggMediator()
{}

void EggMediator::initEvent()
{
	/** 监听许愿事件 */
	_dispatcher->addEventListener(PLEGE_EGG, this, callfuncND_selector(EggMediator::plegeEggHandler));
}

void EggMediator::plegeEggHandler(CCNode* pSender, void* data)
{
	if (!data)
		return;

	struct sdata
	{
		int type;
		int times;
	};
	sdata eparam = *(sdata*)data;


	int gold = 0;
	if(eparam.times == 1){
		gold = 10;
	}else if(eparam.times == 10){
		gold = 95;
	}else{
		gold = 450;
	}
	if(_roleManage->accountInfo()->gold() < gold)
	{
		LangManager::msgShow("EGG019");
		//Alert.show(LangManager.msgShow("EGG019"),Sentence.PROMPT,1,okFunction,null,LangManager.msgShow("COM659"),Sentence.CANCEL);
		return;
	}
			
	if(eparam.type == 2 && !(_roleManage->accountInfo()->vipLev() >= 1 && _roleManage->accountInfo()->vipLev() <= 10)){
		return;
	}

	CCMD402 cmd;
	cmd.a_type = eparam.type;
	cmd.b_num =  eparam.times;
	GameServerSocket::getInstance()->sendMessage(&cmd);
}

void EggMediator::handleNotification( int M2Vcmd, char* data )
{
	switch(M2Vcmd)
	{
	case  REWARD_HISTORY:
		initRewardInfo();
		break;
	case  DEPOT_INFO:
		initDepotInfo();
		break;
	default:
		break;
	}
}

void EggMediator::openDepot(CCNode* pSender, void* data)
{
	ReserveDepot* _depotView = (ReserveDepot*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_reserveDepot);
	if (!_depotView)
	{
		_depotView = new ReserveDepot();
		_depotView->init();
		LayerManager::intervalLayer->addChild(_depotView, IntervalLayer::IntervalLayerZ_reserveDepot, IntervalLayer::IntervalLayerTAG_reserveDepot);
		_depotView->release();
	}

	_depotView->setIsVisible(true);
}

/** 打开拾取数量选择框 */		
void EggMediator::openNumSelectBox(CCNode* pSender, void* data)
{
	struct sdata
	{
		int eggId;
		std::string name;
		int num;
	};
	sdata d = *(sdata*)data;

	if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_egg_NumSelectBox))
	{
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_egg_NumSelectBox,true);
	}

	NumSelectBox* _numSelectBox = new NumSelectBox();
	_numSelectBox->init();
	_numSelectBox->setPosition(ccp(0, 0));
	LayerManager::tipsLayer->addChild(_numSelectBox, TipsLayer::TipsLayerZ_egg_NumSelectBox, TipsLayer::TipsLayerTAG_egg_NumSelectBox);
	_numSelectBox->release();


	_numSelectBox->setInfo(d.eggId, d.name, d.num);


}

/** 初始化许愿历史奖励，包括自己的和服务器所有玩家的 */
void EggMediator::initRewardInfo()
{
	if(_poolView && _poolView->getisPop())
	{
		//_poolView.setCurrency(_eggProxy.currencyNum);
		_poolView->updateMyReward(_eggProxy->getmyRewards());
		_poolView->updateOtherReward(_eggProxy->getotherRewards());
	}
}

/** 初始化心愿宝箱里的蛋蛋信息*/
void EggMediator::initDepotInfo()
{
	if(_poolView && _poolView->getisPop())
	{
		_poolView->updateEggNumInDepot(_eggProxy->geteggNum());
		//_poolView->updatePrize(_eggProxy->getprizeEggs());
	}

	ReserveDepot* _depotView = (ReserveDepot*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_reserveDepot);
	if (!_depotView)
	{
		_depotView = new ReserveDepot();
		_depotView->init();
		LayerManager::intervalLayer->addChild(_depotView, IntervalLayer::IntervalLayerZ_reserveDepot, IntervalLayer::IntervalLayerTAG_reserveDepot);
		_depotView->release();
		_depotView->setIsVisible(false);	
	}


	if (_depotView)
	{
		_depotView->updateEggNum(_eggProxy->geteggNum());

		_depotView->buildList();
	}
}


void EggMediator::uiLoadHandler()
{
	openPoolView();
}

/** 打开许愿池面板 */
void EggMediator::openPoolView()
{
	/*if(GlobalManage.getInstance().isOnBusiness){
		Message.show(LangManager.msgShow("EGG025"),0xff0000);
		return;
	}*/
	if (_poolView)
	{
		_poolView->release();
		_poolView = 0;
	}

	if(!_poolView)
	{
		_poolView = new PoolView();
		_poolView->init();
		ViewManager::getInstance()->poolView = _poolView;
	}
	_poolView->setisPop(!_poolView->getisPop());
			
	if(_poolView->getisPop())
	{
		//是否Vip判断是否显示圣光许愿池
		if(_roleManage->accountInfo()->vipLev() >= 1 && _roleManage->accountInfo()->vipLev() <= 10)
		{
			_poolView->setTab(false);//true
		}else{
			_poolView->setTab(false);
		}
		//设置剩余金币数				
		_poolView->setGold(_roleManage->accountInfo()->gold());
		//向服务端请求许愿的历史奖励（包括自己的和玩家的）
		CCMD400 cmd;
		GameServerSocket::getInstance()->sendMessage(&cmd);
		//向服务端请求宝箱的蛋蛋信息，用于初始化特殊奖励区域
		LayerManager::loadingPic->socketWait( WMSG_EGG_DEPOT, 0, 0);
		CCMD40A cmd2;
		GameServerSocket::getInstance()->sendMessage(&cmd2);
		
	}
}

/** 服务端返回许愿币个数以及自己许愿的收获记录和其他玩家的收获记录 */
void EggMediator::cmdHistoryHandler(SCMD401* param)
{
	sendNotification(Facade_Command, AppFacade_EGG_CHANGE, (char *)param, EggCommand::HISTORY_RESULT);
}

/** 服务端返回临时仓库中的内容 */
void EggMediator::cmdDepotHandler(SCMD40B* param)
{
	sendNotification(Facade_Command, AppFacade_EGG_CHANGE, (char *)param, EggCommand::DEPOT_RESULT);
}


/** 服务端返回许愿返回码 */
void EggMediator::cmdPlegeHandler(SCMD403* param)
{
	int type = param->a_type;
	if(type == 0){//许愿成功
		LangManager::msgShow("EGG007");
		//if(_poolView){
		//	_poolView.playEffect();
		//}

		//向服务端请求宝箱的蛋蛋信息，用于初始化特殊奖励区域
		LayerManager::loadingPic->socketWait( WMSG_EGG_DEPOT, 0, 0);//BattlePlay::getInstance(), callfuncND_selector(BattlePlay::waitSCMD133Timeout)
		CCMD40A cmd2;
		GameServerSocket::getInstance()->sendMessage(&cmd2);
		
	}else if(type == 1){
		LangManager::msgShow("COM602");
	}else if(type == 2){
		LangManager::msgShow("EGG012");
	}else{
		LangManager::msgShow("WRB012");
	}
}

/** 开蛋 */
void EggMediator::openEggHandler(CCNode* pSender, void* data)
{
	struct sdata 
	{
		int eggId;
	};

	sdata eparam = *(sdata*)data;

	LayerManager::loadingPic->socketWait( WMSG_EGG_DEPOT, 0, 0);//BattlePlay::getInstance(), callfuncND_selector(BattlePlay::waitSCMD133Timeout)
	CCMD404 cmd;
	cmd.a_id = eparam.eggId;
	GameServerSocket::getInstance()->sendMessage(&cmd);
	
}
/** 洗礼 */
void EggMediator::washEggHandler(CCNode* pSender, void* data)
{
	if(_roleManage->accountInfo()->gold() < 20)
	{
		LangManager::msgShow("COM602");
		return;
	}

	struct sdata 
	{
		int eggId;
	};

	sdata eparam = *(sdata*)data;

	CCMD408 cmd;
	cmd.a_id = eparam.eggId;
	GameServerSocket::getInstance()->sendMessage(&cmd);
}

/** 拾取 */
void EggMediator::getEggHandler(CCNode* pSender, void* data)
{
	struct sdata 
	{
		int eggId;
		int num;
	};

	sdata eparam = *(sdata*)data;

	LayerManager::loadingPic->socketWait( WMSG_EGG_DEPOT, 0, 0);
	CCMD406 cmd;
	cmd.a_id = eparam.eggId;
	cmd.b_num = eparam.num;
	GameServerSocket::getInstance()->sendMessage(&cmd);
}

/** 一键拾取 */
void EggMediator::getAllHandler(CCNode* pSender, void* data)
{
	LayerManager::loadingPic->socketWait( WMSG_EGG_DEPOT, 0, 0);
	CCMD40C cmd;
	GameServerSocket::getInstance()->sendMessage(&cmd);
}

/** 服务端返回开蛋返回码 */
void EggMediator::cmdOpenHandler(SCMD405* param)
{
	int type = param->a_type;
	int eggId = param->b_eggId;
	int goodsId = param->c_goodsId;
	int goodsNum = param->d_goodsNum;
	if(type == 0)
	{//开蛋成功
		LangManager::msgShow("EGG008");
		struct sdata
		{
			int eggId;
			int goodsId;
			int goodsNum;
		};

		sdata d;
		d.eggId = eggId;
		d.goodsId = goodsId;
		d.goodsNum = goodsNum;
		openWashPanel(PopEventName::SHOW_UI_EGG_WASH, (char*)&d);
	}else if(type == 1){
		LangManager::msgShow("EGG013");
	}else{
		LangManager::msgShow("WRB012");
	}
}

/** 打开洗礼面板 */
void EggMediator::openWashPanel(int name, char* data)
{


	if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_egg_washPanel))
	{
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_egg_washPanel,true);
	}

	WashPanel* _washPanel = new WashPanel();
	_washPanel->init();
	_washPanel->setPosition(ccp(0, 0));
	LayerManager::tipsLayer->addChild(_washPanel,TipsLayer::TipsLayerZ_egg_washPanel,TipsLayer::TipsLayerTAG_egg_washPanel);
	_washPanel->release();

	struct sdata
	{
		int eggId;
		int goodsId;
		int goodsNum;
	};

	sdata eparam = *(sdata*)data;


	_washPanel->_eggId = eparam.eggId;
	_washPanel->updateGoods(eparam.goodsId,eparam.goodsNum);
}

/** 服务端返回拾取返回码 */
void EggMediator::cmdPickHandler(SCMD407* param)
{
	int type = param->a_type;
	if(type == 0){//拾取成功
		

		WashPanel* _washPanel = (WashPanel*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_egg_washPanel);
		if (_washPanel)
			_washPanel->removeFromParentAndCleanup(true);

		NumSelectBox* _selectBox = (NumSelectBox*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_egg_NumSelectBox);
		if (_selectBox)
			_selectBox->removeFromParentAndCleanup(true);

		LangManager::msgShow("EGG009");
	}else if(type == 1){
		LangManager::msgShow("EGG013");
		LayerManager::loadingPic->socketWait( WMSG_EGG_DEPOT, 0, 0);
	}else if(type == 2){
		LangManager::msgShow("EGG014");
		LayerManager::loadingPic->socketWait( WMSG_EGG_DEPOT, 0, 0);
	}else if(type == 3){
		LangManager::msgShow("EGG015");
		LayerManager::loadingPic->socketWait( WMSG_EGG_DEPOT, 0, 0);
	}else if(type == 4){
		LangManager::msgShow("EGG016");
		LayerManager::loadingPic->socketWait( WMSG_EGG_DEPOT, 0, 0);
	}else{
		LangManager::msgShow("WRB012");	
		LayerManager::loadingPic->socketWait( WMSG_EGG_DEPOT, 0, 0);
	}
}

void EggMediator::changeGold(CCObject* pSender, void* data)
{
	if(_poolView)
	{
		_poolView->setGold(_roleManage->accountInfo()->gold());
	}
}

/** 服务端返回洗礼返回码 */
void EggMediator::cmdWashHandler(SCMD409* param)
{
	int type = param->a_type;
	int goodsId = param->b_goodsId;
	int num = param->c_num;
	if(type == 0){//洗礼成功
		LangManager::msgShow("EGG010");	

		WashPanel* _washPanel = (WashPanel*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_egg_washPanel);
		if (_washPanel)
 			_washPanel->updateGoods(goodsId, num);
		/*if(_washPanel && _washPanel.isPop){
			_washPanel.playEffect();
		}*/
		if(_poolView){
			//_poolView->updatePrizeGoods(_washPanel.eggId,goodsId,num);
		}
		if(_depotView){
			//_depotView.updatePrizeGoods(_washPanel.eggId,goodsId,num);
		}
	}else if(type == 1){
		LangManager::msgShow("EGG013");	
	}else{
		LangManager::msgShow("WRB012");	
	}
}

/** 服务端一键拾取返回码 */
void EggMediator::cmdPickAllHandler(SCMD40D* param)
{
	int type = param->a_type;
	if(type == 0){//洗礼成功
		LangManager::msgShow("EGG011");	
	}else if(type == 1){
		LayerManager::loadingPic->releaseLock(WMSG_EGG_DEPOT);
		LangManager::msgShow("EGG017");	
	}else{
		LayerManager::loadingPic->releaseLock(WMSG_EGG_DEPOT);
		LangManager::msgShow("EGG018");	
	}
}