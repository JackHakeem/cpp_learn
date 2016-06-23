#include "SilverMineMediator.h"
#include "model/player/RoleManage.h"
#include "events/GameDispatcher.h"
#include "model/crystal/CrystalProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/scene/SceneWorldMediator.h"
#include "manager/LangManager.h"
#include "manager/GlobalManage.h"
#include "./component/MineView.h"
#include "model/silverMine/SilverConst.h"
#include "model/silverMine/SilverMineProxy.h"
#include "manager/LayerManager.h"
#include "socket/command/c2e/CCMD2E2.h"
#include "socket/command/c2e/CCMD2E4.h"
#include "socket/command/c2e/CCMD2E5.h"
#include "socket/command/c2e/CCMD2E7.h"
#include "socket/command/c2e/CCMD2EA.h"
#include "socket/command/c36/CCMD368.h"
#include "socket/command/s2e/SCMD2E3.h"
#include "socket/command/s2e/SCMD2E6.h"
#include "socket/command/s36/SCMD369.h"
#include "socket/command/s2e/SCMD2EB.h"
#include "socket/command/s36/SCMD367.h"
#include "socket/command/s2e/SCMD2E9.h"
#include "manager/ViewManager.h"
#include "model/silverMine/vo/SilverMineVo.h"
#include "./component/MinePanel.h"
#include "./component/MineBg.h"
#include "socket/command/s2e/SCMD2E8.h"
#include "manager/CDManage.h"
#include "Confirm.h"
#include "manager/PopManage.h"
#include "./component/MineTips.h"
#include "./component/MineRank.h"
#include "manager/LevLimitConst.h"

SilverMineMediator::SilverMineMediator()
{
	_mineView = 0;
	_roleManage = RoleManage::Instance();
	_crystalProxy = (CrystalProxy*) g_pFacade->retrieveProxy(AppFacade_CRYSTAL_PROXY_CHANGE);//this.facade.retrieveProxy(CrystalProxy.NAME) as CrystalProxy;

	_dispatcher = GameDispatcher::getInstance();
			
	_mineProxy = (SilverMineProxy*) g_pFacade->retrieveProxy(AppFacade_SilverMine_PROXY_CHANGE);//this.facade.retrieveProxy(SilverMineProxy.NAME) as SilverMineProxy;
	_dispatcher->addEventListener(GameDispatcher::INTO_SILVERMINE, this, callfuncND_selector(SilverMineMediator::openSilverMineHandler));
}

SilverMineMediator::~SilverMineMediator()
{}

void SilverMineMediator::openSilverMineHandler(CCNode* node, void* data)
{
	bool canEnter = checkCanEnterMine();
	if(canEnter){
		//this->sendNotification(Facade_Mediator, AppFacade_SilverMine_PROXY_CHANGE, 0, SceneWorldMediator::CLOSE_WORLD_SCENE);
		//PopUpManager.closeAllWindows();
		openSilverMine();
	}
}

/**
	* �ӿ���ʱ�����𣬵����쿪������ս ����ʱ���ݶ�Ϊ����8�㵽8��� Ȼ��ÿ�������һ��
	�����ȼ�:�����֮ˮ���ȼ�40������
	* @return 
 	*/		
bool SilverMineMediator::checkCanEnterMine()
{
	if(_roleManage->roleLev() < LevLimitConst::Limit_SilverBattle)
	{
		
		char path[256] = {0};
		sprintf(path , ValuesUtil::Instance()->getString("SLM015").c_str() , LevLimitConst::Limit_SilverBattle);
		Message::Instance()->show(path , ccc3(233,12,25) , 1);
		return false;  //
	}
	//if(GlobalManage.getInstance().isOnBusiness){
	//	LangManager.msgShow("SLM017");
	//	return false;
	//}
	if(_roleManage->_accountInfo.team > 0)
	{
		LangManager::msgShow("SLM018");
		return false;
	}
			
	bool canEnter = false;
	canEnter = g_pGlobalManage->inMineTime();
	return canEnter;
}

void SilverMineMediator::startSocketListener()
{
	//stopSocketListener();
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_SILVERMINE_ENTER_RES, handleEnterRes);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_SILVERMINE_INFO, handleInfoList);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_SILVERMINE_MOVE_RES, handleMoveRes);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_SILVERMINE_BATTLE, handleBattle);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_SILVERMINE_DIG_RES, handleDigRes);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_SILVERMINE_TOKEN_RES, handleToken);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_SILVERMINE_RANK, handleRank);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_SILVERMINE_INSPIRE_RES, handleInspire);
}

Number SilverMineMediator::getserverTime()
{
	return CDManage::Instance()->getServerTime()*0.001;
}

void SilverMineMediator::moveMineHandler(CCNode* node, void* data)
{
	bool isReady = CDManage::Instance()->getCDReady(CDManage::SILVERMINE_MOVE);
	if (!isReady)
	{
		LangManager::msgShow("SLM020");
		return;
	}
	//uint severTimer = CDManage::Instance()->getServerTime()*0.001;	 // ���� 
	//if(_mineProxy->getmoveCD() > severTimer)
	//{
	//	LangManager::msgShow("SLM020");
	//	return;
	//}
	int mineID = *(int*)data;
	sendMoveAction(mineID);
}

/*�ͻ��������ƶ�*/
void SilverMineMediator::sendMoveAction(int mineId)
{
	CCMD2E7 cmd;
	cmd.a_mineId = mineId;
	GameServerSocket::getInstance()->sendMessage(&cmd);
}

/**
	* �˳�����ս���� 
	*/		
void SilverMineMediator::closeSilverMine(CCNode* node, void* data)
{
	if(_mineView) 
	{
 		LayerManager::silverMineLayer->removeChild(_mineView, true);
		closeSceneUI(false);//��ʾ������
	}
			
	startSocketListener();
			
	_mineProxy->isInMine = false;
	sendQuitMine();

	//LH20121120
	if (ViewManager::getInstance()->mainNavigate)
	{
		ViewManager::getInstance()->mainNavigate->showVScrollAndTaskUIView(true);
	}
}

/*����˳�����ս��ͼ*/
void SilverMineMediator::sendQuitMine()
{
	CCMD2E4 cmd;
	GameServerSocket::getInstance()->sendMessage(&cmd);
}

/*�ڿ�����*/
void SilverMineMediator::handleRank(SCMD367* param)
{
	if(_mineView){
		_mineView->updateRank(param->a_ranks);
	}
}

void SilverMineMediator::handleNotification(int M2Vcmd, char* data)
{
	switch(M2Vcmd)
	{
	case TIME_END:
		timeToEnd();
		break;
	default:
		break;
	}
}


void SilverMineMediator::timeToEnd()
{
	if(!_mineView)return;
	//if(_mineProxy/* && !_mineProxy->isInMine*/)return;

	//�ر�TIP��
	{
		MineTips* oldp = (MineTips*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_silverMineTips);
		if (oldp)
		{
			oldp->removeFromParentAndCleanup(true);
		}
	}
	//�ر�������
	{
		MineRank* oldp = (MineRank*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_silverMineRank);
		if (oldp)
		{
			oldp->removeFromParentAndCleanup(true);
		}
	}

	//����ȷ�Ͽ�
	Confirm* pConfirm = new Confirm();
	pConfirm->initWithParam(ValuesUtil::Instance()->getString("SLM019"), this, menu_selector(SilverMineMediator::confirmToQuit),menu_selector(SilverMineMediator::confirmToQuitCancel));
	LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
	pConfirm->release();

}

void SilverMineMediator::confirmToQuitCancel(CCObject* pSender)
{
//			_dispatcher.removeEventListener(GameDispatcher.CRYSTAL_LEVEL_CHANGE, crystalLevHandler);
			
	_mineView->dispatchEvent(SilverConst::EXIT_MINE_VIEW, 0);
	//this.facade.removeMediator(SilverMineMediator.NAME);
//	this.facade.removeProxy(SilverMineProxy.NAME);
			
	//_mineView.dispose();
	//ɾ��ȷ�Ͽ�
	CCNode* pConfirm = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm)
		pConfirm->removeFromParentAndCleanup(true);
}

void SilverMineMediator::confirmToQuit(CCObject* pSender)
{
//			_dispatcher.removeEventListener(GameDispatcher.CRYSTAL_LEVEL_CHANGE, crystalLevHandler);
			
	_mineView->dispatchEvent(SilverConst::EXIT_MINE_VIEW, 0);
	//this.facade.removeMediator(SilverMineMediator.NAME);
//	this.facade.removeProxy(SilverMineProxy.NAME);
			
	//_mineView.dispose();
	//ɾ��ȷ�Ͽ�
	CCNode* pConfirm = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm)
		pConfirm->removeFromParentAndCleanup(true);
}

/*��������ս��֪ͨ*/
void SilverMineMediator::handleBattle(SCMD2E9* param)
{
	//_mineProxy.winRow = param.f_winRow; // ������ʤ��Ϣ
	//_mineView.updateWinRow(_mineProxy.winRow);
			
	if(param->g_backHome==1){ // �Ƿ�ش�Ӫ��0����1���ǣ�
		int mineID = _mineView->getMineIDByCamp(_mineProxy->getcampId());
		if(-1!=mineID){
			LangManager::msgShow("SLM027");
			_mineView->setMyMine(mineID);
		}
	}
			
	//var report:String = makeReport(param);
	//_mineView.updateReport(report); 
}


void SilverMineMediator::openSilverMine()
{
	if (_mineView)
	{
		LayerManager::silverMineLayer->removeChild(_mineView, true);
		_mineView = 0;
	}

	if(!_mineView)
	{
		_mineView = new MineView();
		_mineView->init();
		_mineView->addEventListener(SilverConst::EXIT_MINE_VIEW, this, callfuncND_selector(SilverMineMediator::closeSilverMine));
		_mineView->addEventListener(SilverConst::MOVE_MINE, this, callfuncND_selector(SilverMineMediator::moveMineHandler));
		_mineView->addEventListener(SilverConst::DIG_MINE,  this, callfuncND_selector(SilverMineMediator::digMineHandler));
		//_mineView->addEventListener(SilverConst::LOOK_REPORT, lookReportHandler);
		//_mineView->addEventListener(SilverConst::USE_TOKEN, useTokenHandler);
		_mineView->addEventListener(SilverConst::DO_INSPIRE, this, callfuncND_selector(SilverMineMediator::doInspireHandler));
				
		_mineView->updatePracInsTips(_roleManage->roleLev()*10);
				
		_roleManage->roleInfo()->playerBaseInfo.addEventListener(LiveThingVo::CHANGELEV, this, callfuncND_selector(SilverMineMediator::roleLevHandler));
 	}
	
	
	closeSceneUI(true);
			
	LayerManager::silverMineLayer->addChild(_mineView, 0, 1);
	_mineView->release();
	startSocketListener();

			
	_mineProxy->isInMine = true;
	sendEnterMine();  
}

/*�����������ս��ͼ*/
void SilverMineMediator::sendEnterMine()
{
	CCMD2E2 cmd;
	GameServerSocket::getInstance()->sendMessage(&cmd);
}

/*������������*/
void SilverMineMediator::roleLevHandler(CCNode* node, void* data)
{
	if(_mineView){
 		_mineView->updatePracInsTips( _roleManage->roleLev() * 10);
 	}
}

void SilverMineMediator::doInspireHandler(CCNode* node, void* data)
{
	int type = *(int*)data;
	if(0==type)
	{  // ��ҹ���
		if( _roleManage->_accountInfo.gold() < 5){
			LangManager::msgShow("S3");
			return;
		}
	}
	else{  // ��������
		if(_roleManage->_accountInfo.practice() < _roleManage->roleLev()*10){
			LangManager::msgShow("S4");
			return;
		}
	}
 	sendInspire(type);
}

void SilverMineMediator::sendInspire(int type)
{
	CCMD368 cmd;
	cmd.a_type = type;
	GameServerSocket::getInstance()->sendMessage(&cmd);
}

void SilverMineMediator::closeSceneUI(bool hide)
{
	if(hide)
	{
		g_pPopManage->handleCloseHandler();		
		g_pGlobalManage->setIsShowAllUILock(true);
		g_pGlobalManage->showAllUIEx(false);
		ViewManager::getInstance()->_scene->setIsTouchEnabled(false);
	/*	if(ViewManager::getInstance()->_secNavigate){
			ViewManager::getInstance()->_secNavigate->setIsVisible(false);
		}
		if(ViewManager::getInstance()->taskFollowView){ 
			ViewManager::getInstance()->taskFollowView->setIsVisible(false);
		}
		if(ViewManager::getInstance()->smallMapUI){
			ViewManager::getInstance()->smallMapUI->setIsVisible(false);
		}*/
		
		//g_pGlobalManage->gameView.removeChild(LayerManager.newhandLayer);	
	}
	else
	{
		g_pGlobalManage->setIsShowAllUILock(false);
		g_pGlobalManage->showAllUIEx(true);
		
		if(ViewManager::getInstance()->_secNavigate){
			ViewManager::getInstance()->_secNavigate->setIsVisible(true);
		}
		if(ViewManager::getInstance()->taskFollowView){ 
			ViewManager::getInstance()->taskFollowView->setIsVisible(true);
		}
		if(ViewManager::getInstance()->smallMapUI){
			ViewManager::getInstance()->smallMapUI->setIsVisible(true);
		}
		ViewManager::getInstance()->_scene->setIsTouchEnabled(true);
		//GlobalManage.getInstance().gameView.addChild(LayerManager.newhandLayer);		
	}
//	sendNotification(MainUIMediator::SET_REPORT_VISIBLE, !hide);
	LayerManager::sceneLayer->setIsVisible(!hide);

	//LH20121120
	if (ViewManager::getInstance()->mainNavigate)
	{
		ViewManager::getInstance()->mainNavigate->showVScrollAndTaskUIView(false);
	}
}

/*�����������ս��ͼ���*/
void SilverMineMediator::handleEnterRes(SCMD2E3* param)
{
	if(param->a_ret>=0 && param->a_ret<=2){
		_mineProxy->setcampId(param->a_ret);
		_mineView->setMyCamp(_mineProxy->getcampId());  // �����ҵ�������Ӫ 

		sendUpdateMineList();  // ����ɹ� ���������б� 
	}
	else
	{
		_mineView->_minePanel->move2mine(0, true);
		switch(param->a_ret)
		{
			case -1:
				LangManager::msgShow("SLM022");
				break;
			case -2:
				LangManager::msgShow("SLM023");
				break;
			case -3:
				LangManager::msgShow("SLM024");
				break;
			case -4:
				LangManager::msgShow("SLM025");
				break;
			default:
				LangManager::msgShow("SLM025");
				break;
		}
	}
}

/*�ͻ�����������ս��Ϣ*/
void SilverMineMediator::sendUpdateMineList()
{
	CCMD2E5 cmd;
	GameServerSocket::getInstance()->sendMessage(&cmd);
}

/*��������ս�б���Ϣ����*/
void SilverMineMediator::handleInfoList(SCMD2E6* param)
{
	if(param->a_intime!=1){  // ��1 �Ȳ�������սʱ�� 
		LangManager::msgShow("SLM026");
		return;
	}
	for (std::list<SCMD2E6Node>::iterator it = param->m_mineArr.begin(); it != param->m_mineArr.end(); it++)
	{
		SCMD2E6Node node = *it;
		SilverMineVo silverMineVo;
		silverMineVo.id = node.a_mineId;
		silverMineVo.online = node.b_online;
		silverMineVo.campId = node.c_mineType;
		silverMineVo.isDouble = (node.d_isDouble!=0)?1:0;
		_mineProxy->getmineArr().push_back(silverMineVo);
	}
	
	_mineProxy->setmoveCD(param->b_actionCD);
	_mineProxy->setinActionCD(param->c_inActionCD==1);
			
	_mineProxy->setdigCD(param->d_digCD);
	_mineProxy->setinDigCD(param->e_inDigCD==1);
			
	_mineProxy->setmineID(param->f_mineId);
	_mineProxy->setonMine(param->g_onMine);
		
	_mineView->updateAttPlus(param->h_attPlus);//�����ӳ�

	_mineView->updateDefPlus(param->i_defPlus);//�����ӳ�

	_mineView->setMyCamp(_mineProxy->getcampId());

	_mineView->updateMinePanel(_mineProxy->getmineArr());
	_mineView->setMyMine(_mineProxy->getmineID());
	//		
	_mineView->updateDigCD(_mineProxy->getdigCD(), _mineProxy->getinDigCD());
	_mineView->updateMoveCD(_mineProxy->getmoveCD(), _mineProxy->getinActionCD());
	//		
	_mineView->updateMineInfo(_mineProxy->getmineID(), _mineProxy->getonMine());
	_mineView->updateSilver(param->l_silver);

 	if(!showNoteFlag)
	{
		showNoteFlag = true;
		showNote();
	}
}

void SilverMineMediator::showNote()
{
	//_mineView->showNote();
}

/*������  ���� 0��� 1����*/
void SilverMineMediator::handleInspire(SCMD369* param)
{
	if(_mineView)
	{
		if( param->b_ret == 0)
		{
			_mineView->updateAttPlus(param->c_attPlus);
			_mineView->updateDefPlus(param->d_defPlus);
			LangManager::msgShow("SLM046");
		}
		else
		{
			LangManager::msgShow("SLM045");
		}
	}
}

/*���������ƶ����*/
void SilverMineMediator::handleMoveRes(SCMD2E8* param)
{
	_mineProxy->setmoveCD(param->c_actionCD);
	_mineProxy->setinActionCD(param->d_inCD==1);
	_mineProxy->setdigCD(param->e_digCD);
	_mineProxy->setinDigCD(param->f_inDigCD==1);
	_mineProxy->setonMine(param->h_online);
			
	if(param->b_moveRet==0){  // �ƶ������0���ƶ���Ŀ������1��ԭ��ͣ��  2����ս����
		_mineProxy->setmineID(param->a_mineId);
		_mineView->setMyMine(_mineProxy->getmineID());
	}
			
	_mineView->updateMoveCD(_mineProxy->getmoveCD(), _mineProxy->getinActionCD());
	_mineView->updateDigCD(_mineProxy->getdigCD(), _mineProxy->getinDigCD());
	_mineView->updateMineInfo(_mineProxy->getmineID(), _mineProxy->getonMine());			
		
}

		
void SilverMineMediator::digMineHandler(CCNode* node, void* data)
{
	uint digcd = _mineProxy->getdigCD();
	uint severTimer = CDManage::Instance()->getServerTime()*0.001;	 // ���� 
	//Number st = getserverTime();

	//if(_mineProxy->getdigCD() > severTimer){  // �ڿ�CDδ��
	//	LangManager::msgShow("SLM021");
	//	return;
	//}
	bool isReady = CDManage::Instance()->getCDReady(CDManage::SILVERMINE_DIG);
	if (!isReady)
	{
		LangManager::msgShow("SLM021");
		return;
	}
			
	if(_mineProxy->getmineID()==0 || _mineProxy->getmineID()==27 || _mineProxy->getmineID()==30){ // ��ǰ�ڴ�Ӫ�����ڿ�
		LangManager::msgShow("SLM050");
		return;
	}
			
	int digMode = *(int*)data;  // �ɼ�ģʽ  �ɼ�ģʽ��0����ͨ�ɼ���1���ƽ�ɼ���2���׽�ɼ���
			
	// ��Ҳɼ����н����ж�
	if((digMode==1 && _roleManage->_accountInfo.gold()<5)||(digMode==2 && _roleManage->_accountInfo.gold()<10) ){  // 5���
		LangManager::msgShow("COM602");
		return;
	}
			
	// �����ڿ����� 
	sendMiningDig(digMode);
}

/*�ͻ��˲ɼ�����*/
void SilverMineMediator::sendMiningDig(int digMode)
{
	CCMD2EA cmd;
	cmd.a_pickMode = digMode;
	GameServerSocket::getInstance()->sendMessage(&cmd);
}

/*��������ɼ���� �ɼ���������ڵ����㣺�ɼ�����������С���㣺�ɼ�ʧ�ܴ����룩*/
void SilverMineMediator::handleDigRes(SCMD2EB* param)
{
	if(param->a_result>0){
		LangManager::msgShow("SLM034");
		_mineProxy->setdigCD(param->b_digCD);
		_mineProxy->setinDigCD(param->c_inCD==1);
		_mineView->updateDigCD(_mineProxy->getdigCD(), _mineProxy->getinDigCD());
	}
	else{
		LangManager::msgShow("SLM035");
	}
}