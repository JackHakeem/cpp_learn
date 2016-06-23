#include "TowerMediator.h"
#include "manager/PopEventName.h"
#include "manager/GlobalManage.h"
#include "model/player/RoleManage.h"
#include "events/GameDispatcher.h"
#include "socket/command/c3b/CCMD3B4.h"
#include "socket/network/GameServerSocket.h"
#include "socket/command/c3a/CCMD3AD.h"
#include "socket/command/c3b/CCMD3AD.h"
#include "socket/command/c3a/CCMD3AF.h"
#include "socket/command/c3b/CCMD3BA.h"
#include "socket/command/c3b/CCMD3B2.h"
#include "socket/command/c3c/CCMD3CA.h"
#include "socket/command/c3c/CCMD3CD.h"
#include "manager/CDManage.h"
#include "socket/command/c3c/CCMD3CC.h"
#include "socket/command/c3c/CCMD3CE.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "control/tower/TowerCommand.h"
#include "utils/ValuesUtil.h"
#include "Confirm.h"
#include "components/TowerRank.h"
#include "manager/LangManager.h"
#include "components/TowerPageNav.h"
#include "manager/ViewManager.h"
#include "manager/GlobalManage.h"
#include "socket/command/c3c/CCMD3C1.h"
#include "socket/command/c3d/CCMD3DE.h"
#include "manager/TouchLayerEnum.h"


extern TowerMediator* g_pTowerMediator = 0;

TowerMediator::TowerMediator()
{
	_isInTowerFightPanel = false;
	_towerView = 0;

	GameDispatcher::getInstance()->addEventListener( PopEventName::SHOW_UI_TOWER,
		this, callfuncND_selector(TowerMediator::popHandler) );

	g_pTowerMediator = this;
	_towerProxy  = 0;
	_towerRank = 0;
}


void TowerMediator::handleNotification( int M2Vcmd, char* data )
{
	if (!_towerProxy)
	{
		_towerProxy = (TowerProxy*)g_pFacade->retrieveProxy( AppFacade_TOWER_PROXY_CHANGE );
	}
	
	switch(M2Vcmd)
	{
	case UPDATE_PANEL_1:
		{
			TowerPanel1Vo* vo = (TowerPanel1Vo*)data;
			updatePanel1(vo);
		}
		break;
	case UPDATE_PANEL_2:
		{
			TowerPanel2Vo* vo = (TowerPanel2Vo*)data;
			updatePanel2(vo);
		}
		break;
	case UPDATE_RANK_LIST:
		{
			TowerRankListVo* vo = (TowerRankListVo*)data;
			updateRanking(vo);
		}
		break;
	case TOWER_FIGHT_END:
		towerFightEnd(*(int*)data);
		break;
	}
}

void TowerMediator::popHandler( CCNode* n, void* data )
{
	if(/*g_pGlobalManage->isOnBusiness() ||*/
		RoleManage::Instance()->accountInfo()->team > 0)
	{ 
			//Alert.show(LangManager.getText("TWR026"));
			return;
	}
	
	openTowerView();
}

void TowerMediator::openTowerView()
{
	_towerView = ViewManager::getInstance()->_pTowerView;
	if(!_towerView)
	{
		_towerView = new TowerView();
		_towerView->init();

		ViewManager::getInstance()->_pTowerView = _towerView;
		//StageProxy.addListener(resize);
		//startSocketListener();
		startViewListener(); 
	}


	_towerView->setisPop( !_towerView->getisPop() );
	_towerView->release();

	if (_towerView->getisPop())
	{
		_towerView->_panelEnter->setIsVisible(true);
		_towerView->_panelFight->setIsVisible(false);
		g_pTowerMediator->_isInTowerFightPanel = false;
		_towerView->_panelFight->_isInit = false;
		_towerView->_panelFight->reset();
		_towerView->_panelFight->FightLock(true);
	}

	if (_towerView && _towerView->_panelFight)
		_towerView->_panelFight->unGUA(0);

	CCMD3CE cmd1;
	GameServerSocket::getInstance()->sendMessage(&cmd1);

	CCMD3B2 cmd2;
	GameServerSocket::getInstance()->sendMessage(&cmd2);
	//_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_REQ_HIDDEN_MONSTER_AWARD);
	//_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_ENTER_TOWER_GATE);
}

/**
* ������ͼ��� 
*/
void TowerMediator::startViewListener()
{
	_towerView->addEventListener(TowerView::OPEN_TOWER_RANK, this, callfuncND_selector(TowerMediator::preTowerRank));
	_towerView->addEventListener(TowerView::ENTER_TOWER_FIGHT,  this, callfuncND_selector(TowerMediator::enterTowerFight));
	_towerView->addEventListener(TowerView::ON_TOWER_INSPIRE,  this, callfuncND_selector(TowerMediator::onTowerInspire));
	_towerView->addEventListener(TowerView::ON_TOWER_FIGHT,  this, callfuncND_selector(TowerMediator::onTowerFight));
	_towerView->addEventListener(TowerView::FIGHT_HIDE_BOSS,  this, callfuncND_selector(TowerMediator::fightHideBoss));
	_towerView->addEventListener(TowerView::ON_LEAVE_TOWER,  this, callfuncND_selector(TowerMediator::onLeaveTower));
	_towerView->addEventListener(TowerView::ON_VISIBLE_CHANGE,  this, callfuncND_selector(TowerMediator::onVisibleChange));
	_towerView->addEventListener(TowerView::ON_TAKE_AWARD,  this, callfuncND_selector(TowerMediator::onTakeTowerAward));
	//_roleManage.accountInfo.addEventListener(AccountInfoVo.CHANGE_CRYSTAL_LEV, onCrystalLevChange);
}

/**===============================�������˷��ؽ��===============================*/

//�򿪻����������Ϣ
void TowerMediator::cmdInitTower( SCMD3B3* cmd )
{
	sendNotification(Facade_Command,
		AppFacade_TOWER_PROXY_CHANGE, (char*)cmd, TowerCommand::UPDATE_PANEL_1);
}

void TowerMediator::updatePanel1( TowerPanel1Vo* vo )
{
	if(_towerView)
		_towerView->updatePanel1(vo);
}

//����˷�������boss��������
void TowerMediator::cmdBoxTip( SCMD3CF* cmd )
{
	if(_towerView)
		_towerView->updateBoxTip(cmd->a_rewards);
}

//����˷��ش��������Ϣ
void TowerMediator::cmdUpdateTowerInfo( SCMD3B5* cmd )
{
	sendNotification(Facade_Command,
		AppFacade_TOWER_PROXY_CHANGE, (char*)cmd, TowerCommand::UPDATE_PANEL_2);
}

void TowerMediator::updatePanel2( TowerPanel2Vo* vo )
{
	if(_towerView)
		_towerView->updatePanel2(vo);
}

//����˷���ս�������Ϣ(����ս�ɹ�������Ӧ��¥�㽱��)
void TowerMediator::cmdTowerFightResult( SCMD3B7* cmd )
{
	if(_towerView)
		_towerView->updatePanelGUA(cmd);

	sendNotification(Facade_Command,
		AppFacade_TOWER_PROXY_CHANGE, (char*)cmd, TowerCommand::TOWER_FIGHT_RESULT);
	//sendNotification(AppFacade.TOWER_PROXY_CHANGE, cmd, TowerCommand.TOWER_FIGHT_RESULT);
}

//����˷��������������λ��Ϣ
void TowerMediator::cmdTowerRanking( SCMD3CB* cmd )
{
	sendNotification(Facade_Command,
		AppFacade_TOWER_PROXY_CHANGE, (char*)cmd, TowerCommand::TOWER_RANKING);
	//sendNotification(AppFacade.TOWER_PROXY_CHANGE, cmd, TowerCommand.TOWER_RANKING);
}

void TowerMediator::updateRanking(TowerRankListVo* vo)
{
	_towerRank = (TowerRank*)LayerManager::intervalLayer->getChildByTag(
		IntervalLayer::IntervalLayerTAG_towerRank);
	if(_towerRank)
	{
		if ( !_towerRank->leaveNameFighting )
		{
			_towerRank->resetTouchDispatcher();
			_towerRank->setIsVisible(true);
			_towerRank->updateRanking(vo);
		}
		else
		{
			if (_towerRank->m_bClickRank && !_towerRank->needFight())
			{
				if ( (_towerRank->_preRank!=vo->myRank) || (vo->myRank==0) )
				{
					_towerRank->updateRanking(vo);
				}
				else
				{
					_towerRank->resetTouchDispatcher();
					_towerRank->setIsVisible(true);
					_towerRank->m_bClickRank = false;
					LangManager::msgShow("TOWR116");

					_towerRank->updateRanking(vo);
				}
			}
		}
	}
}

//����˷��ع�����
void TowerMediator::cmdInspire(SCMD3AE* cmd)
{
	if(_towerView)
		_towerView->updateInspire(cmd);
}

//����ս���������أ��ѱ� towerFightEndCallback �� onRankMeCallback �����
void TowerMediator::towerFightEnd(int battleType)
{
	if(!_towerView || !_isInTowerFightPanel)
		return;
	//12->������ս����13->����Bossս����14->����ս��
	if(battleType==12 || battleType==13) {
		if (_towerView->getisPop())
		{
			_towerView->setisPop(true);
		}
		_towerView->enterTowerFight2();
		if(_towerProxy->waitFightEnd)
		{
			_towerProxy->waitFightEnd = false;
			_towerView->updatePanel2(_towerProxy->_panel2Vo);
		}
		if(_towerProxy->showLottery)
		{
			_towerProxy->showLottery = false;
			//LotteryView->showLottery();
		}
	}
	else if(battleType==14)
	{
		//if(_towerRank)
		//	_towerRank.isPop = true;
		_towerRank = (TowerRank*)LayerManager::intervalLayer->getChildByTag(
			IntervalLayer::IntervalLayerTAG_towerRank);
		_towerRank->setIsVisible(true);
	}
}


/**==============================������ͼ����ɷ����¼�==============================*/

//���������ս������
void TowerMediator::enterTowerFight(CCNode *pNode, void *pData)
{
	//int lev = RoleManage::Instance()->roleLev();
	//int beginFloor = 0;
	//if(lev <= 60){
	//	beginFloor = 41;
	//}else if(lev <= 80){
	//	beginFloor = 61;
	//}else if(lev <= 100){
	//	beginFloor = 81;
	//}else if(lev <= 120){
	//	beginFloor = 101;
	//}
	CCMD3B4 cmd;
	cmd.a_floor = 1/*beginFloor*/;

	//if(_towerProxy->numFree > 0)
	{
		cmd.b_isPay = 0;
		GameServerSocket::getInstance()->sendMessage(&cmd);
		//_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_APPLY_CLIMB_TOWER, cmd);
		if(_towerView)
			_towerView->enterTowerFight2();
	}
	//else
	//{
	//	int vip = RoleManage::Instance()->accountInfo()->vipLev();
	//	if(vip < 5)
	//	{
	//		//Alert.show(LangManager.getText("TWR027"));

	//		Confirm* pConfirm = new Confirm();
	//		pConfirm->initWithParam( ValuesUtil::Instance()->getString("TWR027").c_str(),
	//			_towerView, menu_selector(TowerView::cancelToLeave),
	//			menu_selector(TowerView::cancelToLeave));
	//		LayerManager::tipsLayer->addChild(pConfirm,
	//			TipsLayer::TipsLayerZ_confirmFrame,
	//			TipsLayer::TipsLayerTAG_confirmFrame);
	//		pConfirm->release();
	//		return;
	//	}
	//	else
	//	{
	//		_towerView->m_enterNeedGold = 100 + _towerProxy->numPay * 20;

	//		Confirm* pConfirm = new Confirm();
	//		pConfirm->initWithParam( LangManager::getText("TWR028", _towerView->m_enterNeedGold).c_str(),
	//			_towerView, menu_selector(TowerView::okFunctionFightIn),
	//			menu_selector(TowerView::cancelToLeave));
	//		LayerManager::tipsLayer->addChild(pConfirm,
	//			TipsLayer::TipsLayerZ_confirmFrame,
	//			TipsLayer::TipsLayerTAG_confirmFrame);
	//		pConfirm->release();
	//	}
	//}
}

//�������
void TowerMediator::onTowerInspire(CCNode *pNode, void *pData)
{
	CCMD3AD cmd;
	cmd.a = *(int*)pData;
	GameServerSocket::getInstance()->sendMessage(&cmd);
	//_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_TOWER_INSPIRE, new Int8(int(e.param)));
}

//������ͨ¥��ս��
void TowerMediator::onTowerFight(CCNode *pNode, void *pData)
{
	int isGUA = *(int*)pData;
	GameDispatcher::getInstance()->addEventListener(
		GameDispatcher::BATTLE_CALLBACK, this,
		callfuncND_selector(TowerMediator::towerFightEndCallback) );


	CCMD3B6 cmd;
	cmd.a_isGUA = isGUA;
	GameServerSocket::getInstance()->sendMessage(&cmd);
	//������Ҫͬ��3B7
	LayerManager::loadingPic->socketWait( WMSG_WORLD_RESULT_CLIMB_TOWER, 0, 0);
	//_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_START_CLIMB_TOWER);
}

//��������Bossս��
void TowerMediator::fightHideBoss(CCNode *pNode, void *pData)
{
	GameDispatcher::getInstance()->addEventListener(
		GameDispatcher::BATTLE_CALLBACK, this,
		callfuncND_selector(TowerMediator::towerFightEndCallback) );

	CCMD3AF cmd;
	GameServerSocket::getInstance()->sendMessage(&cmd);
	//_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_TOWER_CHALLENGE_HIDDEN_MONSTER);
}

//��ͨ¥��ս��������bossս�������ص�
void TowerMediator::towerFightEndCallback(CCNode *pNode, void *pData)
{
	GameDispatcher::getInstance()->removeEventListener(GameDispatcher::BATTLE_CALLBACK);


	if(!_towerView || !_isInTowerFightPanel) return;
	if ( !_towerView->getisPop() )
	{		
		_towerView->setisPop(true);
		_towerView->release();

		if (g_pGlobalManage->getTowerGUA() != 0 && _towerView && _towerView->_panelFight)
		{
			_towerView->_panelFight->onGUA(0);	
		}

	}
	_towerView->enterTowerFight2();
	_towerView->_panelFight->m_bFightLock = false;
	_towerView->_panelFight->_btnBeginImg->setIsEnabled(true);
 	if(_towerProxy->waitFightEnd){
 		_towerProxy->waitFightEnd = false;
 		_towerView->updatePanel2(_towerProxy->_panel2Vo);
 	}
 	if(_towerProxy->showLottery){
 		_towerProxy->showLottery = false;
 		//LotteryView->showLottery();
 	}
}

//��������
void TowerMediator::onLeaveTower(CCNode *pNode, void *pData)
{
	//LotteryView.onExit(null);


	//CCMD3BA cmd1;
	//GameServerSocket::getInstance()->sendMessage(&cmd1);
	//TOWR110

	CCMD3DE cmd3de;
	GameServerSocket::getInstance()->sendMessage(&cmd3de);

	//_towerView->m_enterNeedGold = 100 + _towerProxy->numPay * 20;

	//Confirm* pConfirm = new Confirm();
	//pConfirm->initWithParam( LangManager::getText("TOWR110", _towerView->m_enterNeedGold).c_str(),
	//	_towerView, menu_selector(TowerView::okFunctionLeaveTower),
	//	menu_selector(TowerView::cancelToLeave));
	//LayerManager::tipsLayer->addChild(pConfirm,
	//	TipsLayer::TipsLayerZ_confirmFrame,
	//	TipsLayer::TipsLayerTAG_confirmFrame);
	//pConfirm->release();

	//CCMD3B2 cmd2;
	//GameServerSocket::getInstance()->sendMessage(&cmd2);


	//_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_LEAVE_TOWER);
	//_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_ENTER_TOWER_GATE);
}

void TowerMediator::leaveTowerListener(SCMD3DF* cmd)
{
	if (cmd->a_errorcode==0)
	{
		if (_towerView)
		{
			_towerView->_panelEnter->setIsVisible(true);
			_towerView->_panelFight->setIsVisible(false);
			g_pTowerMediator->_isInTowerFightPanel = false;
			_towerView->_panelFight->_isInit = false;
			_towerView->_panelFight->reset();
		}

		CCMD3B2 cmd2;
		GameServerSocket::getInstance()->sendMessage(&cmd2);
	}
	else
	{
		LangManager::msgShow("TOWR109");
	}
}

void TowerMediator::onVisibleChange(CCNode *pNode, void *pData)
{
	_isInTowerFightPanel = *(bool*)pData;
	//if(!_isInTowerFightPanel) LotteryView.onExit(null);
}

void TowerMediator::onTakeTowerAward(CCNode *pNode, void *pData)
{
	CCMD3C1 cmd;
	GameServerSocket::getInstance()->sendMessage(&cmd);
}

//��֮ˮ���ȼ��仯
void TowerMediator::onCrystalLevChange(CCNode *pNode, void *pData)
{
	int lev = RoleManage::Instance()->roleLev();
	switch(lev)
	{
	//ˮ������������
	case 61:
	case 81:
	case 101:
		{
			CCMD3BA cmd;
			GameServerSocket::getInstance()->sendMessage(&cmd);
			//_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_LEAVE_TOWER);
		}
		break;
	default:
		//Do nothing.
		break;
	}
}

/*------------------------------------------------------------------------------------------------------------------------*/

//�򿪻��������а�
void TowerMediator::preTowerRank(CCNode *pNode, void *pData)
{
	openTowerRank();
}

void TowerMediator::openTowerRank()
{
	_towerRank = (TowerRank*)LayerManager::intervalLayer->getChildByTag(
		IntervalLayer::IntervalLayerTAG_towerRank);
 	if(!_towerRank)
 	{
 		_towerRank = new TowerRank();
		_towerRank->init();
		LayerManager::intervalLayer->addChild(
			_towerRank, IntervalLayer::IntervalLayerZ_towerRank, IntervalLayer::IntervalLayerTAG_towerRank);
		_towerRank->release();
 		//StageProxy.addListener(resize);

		_towerRank->_pageNav->addEventListener(TowerPageNav::PAGE_CHANGE,
			this, callfuncND_selector(TowerMediator::onPageChange));
		_towerRank->addEventListener(TowerRank::RANK_ME,
			this, callfuncND_selector(TowerMediator::rankMe));
 	}
	else
	{
		_towerRank->resetTouchDispatcher();
		_towerRank->leaveNameFighting = false;

		_towerRank->_listContainer->currentScreen = _towerProxy->getrankVo()->page;
		updateRanking( _towerProxy->getrankVo() );
	}
	_towerRank->setIsVisible(true);

	if (!_towerProxy->getpanel1Vo())
	{
		return;
	}
	int lev = /*RoleManage::Instance()->roleLev()*/_towerProxy->getpanel1Vo()->maxFloor;
	int page = 0;
	if(lev <= 40){
		page = 9;
	}else if(lev <= 60){
		page = 7;
	}else if(lev <= 80){
		page = 5;
	}else if(lev <= 100){
		page = 3;
	}else if(lev <= 120){
		page = 1;
	}
	CCMD3CA cmd;
	cmd.a_sit = page;
	GameServerSocket::getInstance()->sendMessage(&cmd);
	//_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_REQ_RANKLIST_BY_PAGE, new Int16(1));
}

//���а�ҳ���ı�
void TowerMediator::onPageChange(CCNode *pNode, void *pData)
{
	int page = *(int*)pData; 

	if (!_towerProxy->getpanel1Vo())
	{
		return;
	}
	int lev = /*RoleManage::Instance()->roleLev()*/_towerProxy->getpanel1Vo()->maxFloor;
	int pageLimit = 0;
	if(lev <= 40){
		pageLimit = 9;
	}else if(lev <= 60){
		pageLimit = 7;
	}else if(lev <= 80){
		pageLimit = 5;
	}else if(lev <= 100){
		pageLimit = 3;
	}else if(lev <= 120){
		pageLimit = 1;
	}

	if ( (page<pageLimit) || (page>(pageLimit+3)) )
	{
		LangManager::msgShow("TOWR108");
		return;
	}

	CCMD3CA cmd;
	cmd.a_sit = page;
	GameServerSocket::getInstance()->sendMessage(&cmd);
	//_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_REQ_RANKLIST_BY_PAGE, new Int16(page));
}

//����������
void TowerMediator::rankMe(CCNode *pNode, void *pData)
{
	CCMD3CD* cmd = (CCMD3CD*)pData;
	if(cmd->b_isPay == 0)
	{
		int cdType = CDManage::Instance()->getLockBytype(CDManage::FIGHT);
		if(cdType == 1)
		{
			//Alert.show(LangManager.getText("TWR030"),"", 0);
			LangManager::msgShow("TWR030");
			return;
		}
		int energy = RoleManage::Instance()->accountInfo()->energy();
// 		int token = TokenManager.getInstance().getNum(TokenManager.TOKEN_PK);
// 		if(energy + token <= 0)
// 		{
// 			//Alert.show(LangManager.getText("TWR031"),"", 0);
// 			return;
// 		}


		_towerRank = (TowerRank*)LayerManager::intervalLayer->getChildByTag(
			IntervalLayer::IntervalLayerTAG_towerRank);
		if (_towerRank)
		{
			//_towerRank->dispear(0);
			_towerRank->setIsVisible(false);
			_towerRank->setIsTouchEnabled(false);
			_towerRank->_listContainer->setIsTouchEnabled(false);
		}
		
	}
	
	GameDispatcher::getInstance()->addEventListener(GameDispatcher::BATTLE_CALLBACK, this,
		callfuncND_selector(TowerMediator::onRankMeCallback));
	GameServerSocket::getInstance()->sendMessage(cmd);

	CCMD3CC cmd2;
	GameServerSocket::getInstance()->sendMessage(&cmd2);

	//_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_REPLACE_RANK, cmd);
	//_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_REQ_MY_RANK);	//��λ���Լ�����ҳ
}

//����ս�������ص�
void TowerMediator::onRankMeCallback(CCNode *pNode, void *pData)
{
	_towerRank = (TowerRank*)LayerManager::intervalLayer->getChildByTag(
		IntervalLayer::IntervalLayerTAG_towerRank);
	if (_towerRank)
	{
		if (_towerRank->_preRank==_towerProxy->getrankVo()->myRank)
		{
			LangManager::msgShow("TOWR105");
		} 
		else
		{
			LangManager::msgShow("TOWR104");	// success
		}

		_towerRank->m_bClickRank = false;
		_towerRank->leaveNameFighting = false;
		_towerRank->_listContainer->currentScreen = _towerProxy->getrankVo()->page;
		updateRanking( _towerProxy->getrankVo() );
		
	}
	GameDispatcher::getInstance()->removeEventListener(GameDispatcher::BATTLE_CALLBACK);
}

/*res����ֵ�ĺ���
	0:�ɹ�
	1����һ��û������ TOWR114
	2���Ѿ���ȡ������ TOWR115
	3���ò㲻������������ TOWR111
	4����ұ����ո��������ű���
	5������
	*/
void TowerMediator::takeAwardListener( SCMD3C2* pPacket )
{
	switch (pPacket->c_resultNo)
	{
	case 0:
		LangManager::msgShow("TOWR113");
		break;
	case  1:
		LangManager::msgShow("TOWR114");
		break;
	case 2:
		LangManager::msgShow("TOWR115");
		break;
	case 3:
		LangManager::msgShow("TOWR111");
		break;
	case 4:
		LangManager::msgShow("TOWR112");
		break;
	}
}

/**===========================================================================*/