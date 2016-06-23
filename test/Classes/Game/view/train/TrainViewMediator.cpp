#include "TrainViewMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "control/train/TrainCommand.h"
#include "manager/ViewManager.h"
#include "socket/command/c35/CCMD359.h"
#include "socket/network/GameServerSocket.h"
#include "socket/command/s35/SCMD352.h"
#include "model/train/vo/TrainManager.h"
#include "socket/command/c35/CCMD355.h"
#include "socket/command/c35/CCMD357.h"
#include "socket/command/s35/SCMD358.h"
#include "socket/command/c35/CCMD35B.h"
#include "socket/command/s35/SCMD35C.h"
#include "socket/command/c35/CCMD353.h"
#include "manager/PopEventName.h"
#include "events/GameDispatcher.h"
#include "model/figure/LevelExpManage.h"
#include "model/figure/vo/LevelExpVo.h"
#include "Message.h"
#include "utils/ValuesUtil.h"
#include "events/CDEvent.h"
#include "model/player/RoleManage.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "model/scene/vo/LiveThingVo.h"
#include "manager/LangManager.h"
#include "model/figure/vo/RoleLimConst.h"
#include "model/player/vo/PlayerBaseVo.h"
#include "model/scene/SceneManager.h"
#include "model/scene/SceneProxy.h"
#include "Confirm.h"
#include "model/newhand/NewhandManager.h"
#include "manager/LevLimitConst.h"

TrainViewMediator::TrainViewMediator()
{
	_trainView = NULL;
	_trainProxy = (TrainProxy*)g_pFacade->retrieveProxy( AppFacade_TRAIN_PROXY_CHANGE );
	_trainManager = TrainManager::Instance();
	_cdManage = CDManage::Instance();
	_roleManage = RoleManage::Instance();

	m_buyPosNeedGold = 0;

	GameDispatcher::getInstance()->addEventListener( PopEventName::SHOW_UI_TRAIN, this, callfuncND_selector(TrainViewMediator::showUIHandler) );
}

TrainViewMediator::~TrainViewMediator()
{

}

void TrainViewMediator::handleNotification( int M2Vcmd, char* data )
{
	switch(M2Vcmd)
	{
	case BEGIN_TRAINING:
		beginTraining(data);
		break;
	case END_TRAINING:
		endTraining(data);
		break;
	case RAPIC_LEAP:
		rapicLeap(data);
		break;
	case UPDATE_TRAIN_MODE:
		//updateTrainMode(data);
		break;
	}
}

void TrainViewMediator::viewPop()
{
	if(!_trainView)
	{
		_trainView = new TrainView();
		//_trainView.addEventListener(PopContainer.CLOSE_CONTAINER, closeHandler);
		//_trainView.addEventListener(PopContainer.OPEN_CONTAINER, openHandler);
		_trainView->_rapicGold = _trainProxy->getRapicGold();
		ViewManager::getInstance()->trainView = _trainView;
		_trainView->init();

		//_trainView.addEventListener(TrainView.SELECT_MERC, selectMercHandler);  // special handle
		//selectMercHandler( _roleManage->accountInfo()->roleId );
	}

	//_trainView.isPop = !_trainView.isPop;
	_trainView->setisPop( !_trainView->getisPop() );

	if( _trainView->getisPop() )
	{

		//FigureMediator* figureM = (FigureMediator*)g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);
		//if ( figureM->_figureMainView && figureM->_figureMainView->_figureV )
		//{
		//	selectMercHandler( figureM->_figureMainView->_figureV->currentId() );
		//}
		//else
		//{
		//	selectMercHandler( _roleManage->accountInfo()->roleId );
		//}

		_trainView->createMercList( _trainManager->getTrainDic() );
		selectMercHandler( _trainView->_mercId );
		_trainView->updateTrainNumTips( _trainManager->getTrainNum(), _trainManager->getTrainLim() );
		//var hasCd:Boolean = NewhandManager.getInstance().isOpenButton(NewhandConst.ENABLE_TRAIN_CD);
		//_trainView.showNoCDText(hasCd);

		_trainView->reinitcd();

		
		// new hand
		if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Train) == NewhandManager::Flag_New)
		{
			NewhandManager::Instance()->touchNextScript("p" , "TRAIN");
		}
	}
}

void TrainViewMediator::showUIHandler(CCNode* n, void* data)
{
	viewPop();
}

/** 
* train List Listener
* @param 
*/ 
void TrainViewMediator::trainListListener( char* data )
{
	sendNotification( Facade_Command, AppFacade_TRAIN_PROXY_CHANGE, data, TrainCommand::INIT_TRAIN_LIST );
}

/**
* train time end
* @param event0
*/
void TrainViewMediator::trainTimeEndHandler(int id)
{
	//var merc:PlayerInfoVo = event.param as PlayerInfoVo;
	if( id == _trainView->_mercId )
    {
        vector<TimeInitStruct> infos = _trainProxy->getTimeList();
		_trainView->openTimePanel(infos);        
    }
}

/**
* startTrainHandler
* @param event  info.id :ID
*/
void TrainViewMediator::startTrainHandler( int mercId , int type, int model, int gold, int silver )
{
	PlayerInfoVo* playerInfoVo = RoleManage::Instance()->getMercenary(mercId);

	if( !playerInfoVo )
		return;
	
	if( RoleManage::Instance()->roleLev()< playerInfoVo->playerBaseInfo.lev())
	{
		LangManager::msgShow( "TRN010", playerInfoVo->playerBaseInfo.name );
		return;
	}

	if( (TrainManager::Instance()->getTrainNum()+1) > TrainManager::Instance()->getTrainLim() )
	{
		LangManager::msgShow( "T0005");
		return;
	}

	if( silver > RoleManage::Instance()->accountInfo()->silver() )
	{
		LangManager::msgShow( "T0006");
		return;
	}

	if( (type==1) &&
		(gold > RoleManage::Instance()->accountInfo()->gold())
		)
	{
		LangManager::msgShow( "T0007");
		return;
	}

	CCMD359 cmd;
	cmd.a_playerId = mercId;
	cmd.b_type = type;
	cmd.c_mode = model;
	GameServerSocket::getInstance()->sendMessage( &cmd );

	LayerManager::loadingPic->socketWait_old( WMSG_WORLD_TRAIN_RESP );
}

		
/**
* endTrainHandler
* @param event
*/
void TrainViewMediator::endTrainHandler( int mercId )
{
	CCMD357 cmd;
	cmd.a_playerId = (int32)mercId;
	GameServerSocket* _wSocket = GameServerSocket::getInstance();
	_wSocket->sendMessage( &cmd );

	LayerManager::loadingPic->socketWait_old( WMSG_WORLD_TRAIN_END_RESP );
}
/**
* buyPositionHandler
* @param event
*/
void TrainViewMediator::buyPositionHandler()
{
	CCNode* pConfirmLayer = LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame);
	if (pConfirmLayer)
	{
		return;
	}	

	int curSitNum = RoleManage::Instance()->accountInfo()->trainSitNumLim();
	if( (curSitNum >=2) && (curSitNum < 8) )
	{
		//not more than 8 positions
		int needVip = _trainManager->BUY_SIT_VIP[curSitNum];
		int needGold = _trainManager->BUY_SIT_GOLD[curSitNum];
		//onAlertBuySit( needGold );

		if( needVip > RoleManage::Instance()->accountInfo()->vipLev() )
		{
			m_buyPosNeedGold = 0;

			Confirm* pConfirm = new Confirm();
			std::string stdstr = LangManager::getText("TRN011",needVip);
			pConfirm->initWithParam( stdstr.c_str(), this,
				menu_selector(TrainViewMediator::onAlertBuySit),
				menu_selector(TrainViewMediator::onCancelBuySit),
				LangManager::getText("COM659") );

			LayerManager::windowLayer->addChild(pConfirm,WindowLayer::WindowLayerZ_confirmFrame, WindowLayer::WindowLayerTAG_confirmFrame);
			pConfirm->release();	
		}
		else
		{
			m_buyPosNeedGold = needGold;

			Confirm* pConfirm = new Confirm();
			std::string stdstr = LangManager::getText("TRN012",needGold);
			pConfirm->initWithParam( stdstr.c_str(), this,
				menu_selector(TrainViewMediator::onAlertBuySit),
				menu_selector(TrainViewMediator::onCancelBuySit)
				);
			LayerManager::windowLayer->addChild(pConfirm,WindowLayer::WindowLayerZ_confirmFrame, WindowLayer::WindowLayerTAG_confirmFrame);
			pConfirm->release();
		}
	}
	else
	{
		LangManager::msgShow("TRN013", ccRED);
	}
}


/* process after confirm */
void TrainViewMediator::onAlertBuySit( CCObject* pObject )
{
	if( m_buyPosNeedGold == 0 )
	{
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_VIP, 0);
	}
	else
	{
		if( m_buyPosNeedGold > RoleManage::Instance()->accountInfo()->gold() )
		{
			LangManager::msgShow( "TRN014", ccRED );
		}
		else
		{
			CCMD353 cmd;
			GameServerSocket::getInstance()->sendMessage( &cmd );	//CMSG_WORLD_TRAIN_BUY_PLACE
			LayerManager::loadingPic->socketWait_old( WMSG_WORLD_TRAIN_BUY_PLACE_RESP );
		}
	}

	Confirm* pConfirm = (Confirm*)LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame);
	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);
}

void TrainViewMediator::onCancelBuySit( CCObject* pObject )
{
	Confirm* pConfirm = (Confirm*)LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame);
	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);
}

/**
* rapidLeapHandler type 0Lilian  1gold   
* @param event
*/
void TrainViewMediator::rapidLeapHandler( int mercId, int type )
{
	PlayerInfoVo* playerInfoVo = RoleManage::Instance()->getMercenary(mercId);
	int demandLev = 51 + playerInfoVo->figureBaseInfo.rebornNum * 5;
	int baseLev = playerInfoVo->playerBaseInfo.lev();
	int adLev = playerInfoVo->playerBaseInfo.adLv;

	// CD lock！
	if( type==0 && CDManage::Instance()->getLockBytype(CDManage::TRAINING) )
	{
		LangManager::msgShow( "T0012", ccRED );
		return;
	}

	int mcLev = RoleManage::Instance()->roleLev();
	if( 
		(playerInfoVo->playerBaseInfo.id != RoleManage::Instance()->roleInfo()->playerBaseInfo.id )
		&& ( (baseLev >= mcLev) && (adLev == 0) )
		)
	{
		LangManager::msgShow( "T0013", ccRED );
		return;
	}
//	if( (baseLev==demandLev) && (adLev==0) )
//	{
//		LangManager::msgShow( "TRN022", ccRED );
//		return;
//	}
	//SceneProxy* _sceneProxy = (SceneProxy*)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
	//if(  (RoleLimConst::IsOk(baseLev) != 0) && 
	//	(adLev==0) )
	//{
	//	if( _sceneProxy->getSceneStatus(RoleLimConst::IsOk(baseLev)) <= 0 )
	//	{	
	//		string name = SceneManager::Instance()->getSceneDic( RoleLimConst::IsOk( RoleManage::Instance()->roleLev() ) )->name;
	//		LangManager::msgShow( "TRN021", name, ccRED );
	//		return;
	//	}
	//}
	//int practiceDemand = _trainProxy->getPracticeDemand(mcLev);
	//if( type==0 && RoleManage::Instance()->accountInfo()->practice() < practiceDemand )
	//{
	//	LangManager::msgShow( "T0014", ccRED);
	//	return;
	//}

	if( (type==1) && (RoleManage::Instance()->accountInfo()->gold() < _trainProxy->_rapicGold) )
	{
		LangManager::msgShow( "STG007" , ccRED );
		return;
	}
			
	CCMD35B cmd;
	cmd.a_playerId = mercId;
	cmd.b_type = (int8)type;
	GameServerSocket* _wSocket = GameServerSocket::getInstance();
	_wSocket->sendMessage( &cmd );

	LayerManager::loadingPic->socketWait_old( WMSG_WORLD_TRAIN_SPEED_UP_RESP );
}

/**
* selectMercHandler
* @param event
*/
void TrainViewMediator::selectMercHandler( int mercId )
{
  	openMercPanel( mercId );
}
		
void TrainViewMediator::openMercPanel( int id )
{
	PlayerInfoVo* merc = _roleManage->getMercenary( id );
	if ( !merc ) return;
	
	PlayerBaseVo* playerBaseInfo = &merc->playerBaseInfo;
	if ( !playerBaseInfo ) return;

	playerBaseInfo->addEventListener( LiveThingVo::CHANGELEV, this, callfuncND_selector(TrainViewMediator::updateLevHandler) );
	
	_trainView->updateMercInfo(merc, true);

	TrainVo* trainVo = _trainManager->getVoByMercId(id);
	if( trainVo)
	{	
		_trainView->openTrainPanel(trainVo);
		//ModeInitStruct* pMode = _trainProxy->getModeObj( trainVo->mode );
		//string str = pMode->descMode;
		//_trainView->updateTrainMode( trainVo->mercId, trainVo->mode, str );
	}                                  
	else
	{
        vector<TimeInitStruct> tmpList = _trainProxy->getTimeList();
		_trainView->openTimePanel(tmpList);
	}
	//		
	updateMercExp(id);
	_trainView->updateTrainNumTips( _trainManager->getTrainNum(), _trainManager->getTrainLim() );
	updateRapicTips(id);
	//updateRebornDemand(id);
	//		
	//if(_roleManage.accountInfo.vipLev>=10){
	//	_trainView.setBtnGoldRapicVisible(true);
	//}else{
	//	_trainView.setBtnGoldRapicVisible(false);
	//}
}

		
/**
* beginTraining
*/
void TrainViewMediator::beginTraining( char* obj )
{
	SCMD35A* msg = (SCMD35A*)obj;
	int32 id = msg->a_playerId;
	string mercName = _roleManage->getMercenary(id)->playerBaseInfo.name;
	string str = ValuesUtil::Instance()->getString( "T031" );
	mercName.append( str );
	Message::Instance()->show( mercName );
	
	if(!_trainView) return;
	TrainVo* trainVo = _trainManager->getVoByMercId( id );
	if ( !trainVo ) return;

	_trainView->openTrainPanel(trainVo);

	 updateRapicTips( id );

	 // LH 
	 _trainView->showIsTrained(id);
	 _trainView->setTrainTips();

	////新手引导
	//if(NewhandManager.getInstance().nextEventId == NewhandConst.EVENT_TRIAN_START){
	//	_dispatcher.dispatchEvent(new ParamEvent(GameDispatcher.TEST_NEW_HAND, 
	//		{type:"evt", id:NewhandConst.EVENT_TRIAN_START}));
	//}

	 CCMD355 cmd;
	 cmd.a_playerId = trainVo->mercId;
	 cmd.b_mode = (int8)_trainView->_selectMode;
	 GameServerSocket::getInstance()->sendMessage( &cmd );
}
		
/**
* endTraining update
*/
void TrainViewMediator::endTraining( char* obj )
{
	SCMD358* param = (SCMD358*)obj;
	int id = param->a_playerId;
	string mercName = _roleManage->getMercenary(id)->playerBaseInfo.name;
	string strConfirm = ValuesUtil::Instance()->getString( "T0002" );
	mercName.append( strConfirm );
	Message::Instance()->show( mercName );
	//_msgManage.showMsg(MsgManage.SYSTEM_MSG, "T0002", mercName);
			
	if(!_trainView) return;
    
    vector<TimeInitStruct> tmpList = _trainProxy->getTimeList();
	_trainView->openTimePanel(tmpList);

	// LH 
	_trainView->showIsTrained(id);
	_trainView->setTrainTips();

	//_trainView.removeTrainFlag(obj.mercs);
}

/**
* changeModeListener
* @param
*/
void TrainViewMediator::changeModeListener( char* param )
{
	sendNotification( Facade_Command, AppFacade_TRAIN_PROXY_CHANGE, param, TrainCommand::CHANGE_MODE );
}

/** 
* buyPositionListener
* @param 
*/
void TrainViewMediator::buyPositionListener( SCMD354* param )
{
	//if ( param->a_result == 1 )
	//{
	//	_trainView->SetNotEnoughGold();
	//}

	if( param->a_result == 2 )
	{
		_roleManage->accountInfo()->trainSitNumLim( (int)param->b_posiNum );

		sitNumChangeHandler( (int)param->b_posiNum );
	}

}

/**
* endTrainingListener
* @param 
*/
void TrainViewMediator::endTrainingListener( char* param )
{
	sendNotification( Facade_Command, AppFacade_TRAIN_PROXY_CHANGE, (char*)param, TrainCommand::END_TRAINNING );
}

/**
* startTrainingListener
* @param
*/
void TrainViewMediator::startTrainingListener( SCMD35A* param )
{
	sendNotification( Facade_Command, AppFacade_TRAIN_PROXY_CHANGE, (char*)param, TrainCommand::START_TRAINNING );
}

/**
* rapicLeapListener
* @param 
*/
void TrainViewMediator::rapicLeapListener( char* param )
{
	sendNotification( Facade_Command, AppFacade_TRAIN_PROXY_CHANGE, (char*)param, TrainCommand::RAPIC_LEAP );
}

void TrainViewMediator::updateExpHandler()
{
	//var playerBaseVo:PlayerBaseVo = PlayerBaseVo(event.target);
	//updateMercExp(playerBaseVo.id);
}
		
/**
* updateMercExp
*/
void TrainViewMediator::updateMercExp(int mercId)
{
	PlayerInfoVo* merc = _roleManage->getMercenary(mercId);

 	LevelExpVo* expVo = LevelExpManage::Instance()->getLevelExp( merc->playerBaseInfo.lev() );
	if ( expVo )
	{
		int totalExp =  merc->playerBaseInfo.exp();
		int countExp = expVo->countExp;
		int needExp = expVo->needExp;
		int curExp = totalExp - countExp;
		_trainView->updateMercExp( mercId, curExp, needExp );
	} 
	else
	{
		int curExp (57375);
		int needExp (198180);
		_trainView->updateMercExp( mercId, curExp, needExp );
	}	
}

void  TrainViewMediator::updateLevHandler(CCNode* n, void* data)
{
	if ( !_trainView )	return;

	int id = *(int*)data;
	PlayerInfoVo* merc = _roleManage->getMercenary( id );

	_trainView->updateMercInfo( merc, false );
	//if(_mainView.trainView.mercId == merc.figureBaseInfo.mercId){
	//	_mainView.trainView.playUpEffect();
	//}
}

void TrainViewMediator::sitNumChangeHandler( int trainSit )
{
	_trainManager->setTrainLim( trainSit );
	trainNumHandler();
}

/**
* trainNumHandler
*/
void TrainViewMediator::trainNumHandler()
{
	if(_trainView)
	{
		_trainView->updateTrainNumTips(  _trainManager->getTrainNum(), _trainManager->getTrainLim() );
	}
}

/**
* updateRapicTips
*/
void TrainViewMediator::updateRapicTips( int id )
{
	//PlayerInfoVo* merc = RoleManage::Instance()->getMercenary(id);
	bool showCD = ( CDManage::Instance()->getCDTimeBytype(CDManage::TRAINING) > CDManage::Instance()->getServerTime() ) ? true : false;	
	
	CrystalProxy* _crystalProxy	= (CrystalProxy*)g_pFacade->retrieveProxy(AppFacade_CRYSTAL_PROXY_CHANGE);
	/*
	int yanLev = _crystalProxy->getCrystalLev( CrystalType::CRYSTAL_YAN );
	int huoLev = _crystalProxy->getCrystalLev( CrystalType::CRYSTAL_HUO );
	int yan2Lev = _crystalProxy->getCrystalLev( CrystalType::CRYSTAL_YAN2 );
	*/
	//base on table cfg_functionTrigger
	//the fire crystal levels 8 at the beginning
	int huoLev = 0;
	if (8 > RoleManage::Instance()->roleLev())
	{
		huoLev = 8;
	}
	else
	{
		huoLev = RoleManage::Instance()->roleLev();
	}
	//the yan crystal is opened at level 55 is same to role lv
	int yanLev = 0;
	if (55 <= huoLev)
	{
		yanLev = huoLev;
	}
	int yan2Lev = 0;
	//the yan2 crystal is opened at level 102 is same to role lv
	if (102 <= huoLev)
	{
		yan2Lev = huoLev;
	}

	int mingLev = RoleManage::Instance()->roleInfo()->playerBaseInfo.lev();

	//float fParam = 1.5f;
	//if (_trainView->_mercId==RoleManage::Instance()->accountInfo()->roleId)
	//{
	//	fParam = 1.0f;
	//}
	int exp = _trainProxy->getExpAdded(yanLev,huoLev,yan2Lev)/**fParam*/;

	string tips = LangManager::getText( "TRN009", exp );

	_trainView->updateRapicTips( showCD, tips, exp );
}

/**
* rapicLeap
*/
void TrainViewMediator::rapicLeap( char* data )
{
	SCMD35C obj = *(SCMD35C*)data;
	if(!_trainView) return;

	//CrystalProxy* _crystalProxy	= (CrystalProxy*)g_pFacade->retrieveProxy(AppFacade_CRYSTAL_PROXY_CHANGE);
	PlayerInfoVo* pInfoVo = RoleManage::Instance()->getMercenary(obj.a_playerId);
	string mercName = pInfoVo->playerBaseInfo.name;
	int rapidExp = obj.b_rapidExp;
	int criExp = obj.d_critExp;
	char txt[128];
	if( criExp<=0 )
	{
		sprintf( txt, ValuesUtil::Instance()->getString("T0003").c_str(), mercName.c_str(), rapidExp );
		LangManager::msgStr( txt );
	}
	else
	{
		sprintf( txt, ValuesUtil::Instance()->getString("T0020").c_str(), mercName.c_str(), rapidExp+criExp );
		LangManager::msgStr( txt );
	}

	_trainView->_rapicGold = obj.c_goldPrice;
	updateRapicTips( obj.a_playerId );
	_trainView->updateRapicEffect(obj.a_playerId, rapidExp, criExp);
	_trainView->playCritEffect(criExp);
}

/**
* public var time:Number;
public var cdType:uint;
public var lock:int;	//1:lock 0 release 
* @param event
*/		
void TrainViewMediator::cdChangeHandler( CCNode* n, void* data )
{
	if( !_trainView || !_trainView->getisPop() )
		return;

	CDEvent* pEvent = (CDEvent*)data;

	if( pEvent->cdType == CDManage::TRAINING )
	{
		updateRapicTips( _trainView->_mercId );
	}
}