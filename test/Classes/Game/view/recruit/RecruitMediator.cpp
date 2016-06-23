#include "RecruitMediator.h"
#include "socket/command/s30/SCMD305.h"
#include "socket/command/s30/SCMD303.h"
#include "socket/command/s30/SCMD301.h"
#include "socket/command/s30/SCMD300.h"
#include "components/RecruitView.h"
#include "manager/ViewManager.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "model/player/RoleManage.h"
#include "socket/command/s29/SCMD291.h"
#include "socket/network/GameServerSocket.h"
#include "socket/command/c29/CCMD290.h"
#include "control/recruit/RecruitCommand.h"
#include "model/recruit/RecruitProxy.h"
#include "socket/command/c30/CCMD306.h"
#include "socket/command/c30/CCMD302.h"
#include "socket/command/c30/CCMD304.h"
#include "Message.h"
#include "utils/ValuesUtil.h"
#include "socket/command/c30/CCMD307.h"
#include "model/backpack/BagProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "model/figure/EquipmentManager.h"
#include "model/train/vo/TrainManager.h"
#include "manager/LangManager.h"
#include "socket/command/c30/CCMD308.h"
#include "socket/command/c31/CCMD317.h"
#include "model/skill/vo/SkillType.h"

RecruitMediator::RecruitMediator()
{
	_recruitView = 0;
	_equipmentManager = 0;
	_trainManager = 0;
	_recruitProxy = 0;

	GameDispatcher::getInstance()->addEventListener( PopEventName::SHOW_UI_RECRUIT, this, callfuncND_selector(RecruitMediator::viewPopHandler) );
}

RecruitMediator::~RecruitMediator()
{

}

void RecruitMediator::handleNotification( int M2Vcmd, char* data )
{
	switch(M2Vcmd)
	{
	case DATA_CHANGE:
		proxyDataHandler( data );
		break;
	case RECRUIT_MERC:
		recruitMerc( (int)data );
		break;
	case DISMISS_MERC:
		dismissMerc( data );
		break;
	}
}

/**
* key board listening[R]
*/
void RecruitMediator::viewPopHandler( CCNode* n, void* data )
{
	viewPop();
}

void RecruitMediator::viewPop()
{
	if(!_recruitView)
	{
		_recruitView = new RecruitView();
		if ( !_recruitView->init() )
		{
			return;
		}
		//_recruitView.addEventListener(PopContainer.CLOSE_CONTAINER, closeHandler);
		//_recruitView.addEventListener(PopContainer.OPEN_CONTAINER, openHandler);
		ViewManager::getInstance()->recruitView = _recruitView;

		_equipmentManager = EquipmentManager::Instance();
		_trainManager = TrainManager::Instance();
		_recruitProxy = (RecruitProxy*)g_pFacade->retrieveProxy( AppFacade_RECRUIT_PROXY_CHANGE );

		_recruitView->setDefault();
	}


	if( _recruitView && !_recruitView->getisPop() ) 
	{
		_recruitView->setisPop( true/*!_recruitView->getisPop()*/ );

		_recruitView->release();

		CCMD290 cmd;
		GameServerSocket::getInstance()->sendMessage( &cmd );	//CMSG_REP_CAN_HIRE_MAX_MER_NUM
		refreshView();
	}
}
		
void RecruitMediator::closeHandler()
{
	//stopViewListener();
	//stopSocketListener();
}
		
void RecruitMediator::openHandler()
{
	//startViewListener();
	//startSocketListener();
}
		
void RecruitMediator::refreshView()
{
	if( _recruitView )
	{
		updateRecruitPanel();
		_recruitView->setTroops( RoleManage::Instance()->accountInfo()->roleNum, RoleManage::Instance()->accountInfo()->roleLim );
		_recruitView->setMyExp(  RoleManage::Instance()->accountInfo()->popularity() );
	}
}
		
void RecruitMediator::updateRecruitPanel()
{
	_recruitProxy->cleanRecruitList();
	CCMD306 cmd;
	GameServerSocket::getInstance()->sendMessage( &cmd );	//CMSG_WORLD_MERCENARY_EMPLOYNPC	请求可招剧情佣兵列表
}
 
/**
* 监听Proxy数据发生改变
*/
void RecruitMediator::proxyDataHandler( char* data )
{
	if( _recruitView && _recruitView->getIsVisible() && _recruitView->getisPop() )
	{
		//if( !_recruitView->_info )
		//{  // 当 info 不存在 即 初次打开面板 当前item为null
		//	firstOpen();
		//}
		freshPanel();
	}
}
		
void RecruitMediator::firstOpen()
{
	int pagesize = 8;
	vector<RecruitInfo> infos;
	//switch( _recruitView->_curIndex )
	//{  
	//	case 0:  /**剧情*/
	//		infos = _recruitProxy->storyList();
	//		break;
	//	case 1:  /**名声*/
	//		infos = _recruitProxy->fameList();
	//		break;
	//}
	/**名声*/
	infos = _recruitProxy->fameList();
	uint length = infos.size();
	//if( length == 0 )
	//{
	//	if( _recruitProxy->_fameList.size() > 0 )
	//	{
	//		_recruitView->setDefault(1); // 将默认tab设为名声佣兵
	//		return;
	//	}
	//}
	uint totalPage = (length%pagesize==0) ? (length/pagesize) : (length/pagesize + 1);
	int startNum = (_recruitView->_page -1) * pagesize;		//0开始
	vector<RecruitInfo> arr;
	for ( uint i = 0; i < pagesize; i++ )
	{
		int index = startNum + i;
		if ( index >0 && ( index < infos.size() ) )
		{
			arr.push_back( infos[index] );
		}
	}
	_recruitView->createRecruitPanel( arr, _recruitView->_page, totalPage, pagesize );
}
		
		
void RecruitMediator::freshPanel()
{
	int pagesize = 8;
	vector<RecruitInfo> infos;
	//switch( _recruitView->_curIndex )
	//{  
	//case 0:  /**剧情*/
	//	infos = _recruitProxy->storyList();
	//	break;
	//case 1:  /**名声*/
	//	infos = _recruitProxy->fameList();
	//	break;
	//}
	/**名声*/
	infos = _recruitProxy->fameList();
	uint length = infos.size();
	uint totalPage = (length%pagesize==0) ? (length/pagesize) : (length/pagesize + 1);
	_recruitView->createRecruitPanel( infos, _recruitView->_page, totalPage, pagesize );
}
 
/**
* @param event index page pagesize
*/
void RecruitMediator::changePageHandler()
{
	freshPanel();
}
		
void RecruitMediator::popuChangeHandler()
{
	//if(!_recruitView)return;
	//if(_recruitView.isPop && _recruitView.curIndex==1){
	//	freshPanel();
	//}
}

/**
* recruitMercHandler
* @param event  mercId ID
*/
void RecruitMediator::recruitMercHandler( int mercId )
{
	AccountInfoVo* pInfo = RoleManage::Instance()->accountInfo();
	if ( !pInfo )
	{
		return;
	}
	if(  pInfo->roleLim < (pInfo->roleNum+1)  )
	{
		LangManager::msgShow("R0001");
		return;
	}

	if( _recruitProxy->getRecruitSilver(mercId) > pInfo->silver() )
	{
		LangManager::msgShow("R0002");
		return;
	}
	CCMD302 cmd;
	cmd.a_prototypeId = (int16)mercId;
	GameServerSocket::getInstance()->sendMessage( &cmd );	// CMSG_WORLD_MERCENARY_RECRUIT

	LayerManager::loadingPic->socketWait_old( WMSG_WORLD_MERCENARY_RECRUIT );
}
		
/**
* recruitMerc
*/
void RecruitMediator::recruitMerc( int id )
{
	LangManager::msgShow("RCR023");
	//Message::Instance()->show( ValuesUtil::Instance()->getString("RCR023") );

	if( !EquipmentManager::Instance()->getEquipment(id) )
	{
		CCMD308 cmd;
		cmd.a_byte = 0;
		GameServerSocket::getInstance()->sendMessage( &cmd );//CMSG_WORLD_MERCENARY_EQUIP_INFO
	}

	CCMD307 cmd;
	cmd.a_byte = id;
	GameServerSocket::getInstance()->sendMessage( &cmd );	// CMSG_WORLD_MERCENARY_BASE_INFO
	LayerManager::loadingPic->socketWait_old( WMSG_WORLD_MERCENARY_BASE_INFO );

	//Message.show("【"+RoleManage.getInstance().getMercenary(id).playerBaseInfo.name+"】"+LangManager.getText("RCR025"));
	PlayerInfoVo* pPlayerInfoVo = RoleManage::Instance()->getMercenary(id);
	if ( pPlayerInfoVo )
	{

		string msg = LangManager::getText( "RCR025", pPlayerInfoVo->playerBaseInfo.name.c_str() );
		Message::Instance()->show( msg );
		//LangManager::msgShow( "RCR025", pPlayerInfoVo->playerBaseInfo.name );
	}
	refreshView();
}
		
void RecruitMediator::dismissMerc( char* data )
{
	LangManager::msgShow("RCR024");
	//Message::Instance()->show( ValuesUtil::Instance()->getString("RCR024") );
 	refreshView();

	//by LH 0730
// 	CCMD317 cmd;
// 	cmd.a_type = 1;
// 	GameServerSocket * pSocket = GameServerSocket::getInstance();
// 	if (pSocket)
// 	{
// 		pSocket->sendMessage(&cmd);
// 	}
	
}
		
/**
* dismissMercHandler
*/
void RecruitMediator::dismissMercHandler( int mercId )
{
	BagProxy* _bagProxy = (BagProxy*)g_pFacade->retrieveProxy( AppFacade_BAG_PROXY_CHANGE );
	if( _bagProxy->getSpaceGridNum() < EquipmentManager::Instance()->getEquipmentNum(mercId) )
	{
		LangManager::msgShow("R0003");
		//Message::Instance()->show( ValuesUtil::Instance()->getString("R0003") );
		return;
	}
	if( TrainManager::Instance()->_trainDic.find(mercId) != TrainManager::Instance()->_trainDic.end() )
	{
		LangManager::msgShow("R0004");
		//Message::Instance()->show( ValuesUtil::Instance()->getString("R0004") );
		return;
	}

	CCMD304 cmd;
	cmd.a_mercenaryId = mercId;
	GameServerSocket::getInstance()->sendMessage( &cmd ); // CMSG_WORLD_MERCENARY_DISMISS
	LayerManager::loadingPic->socketWait_old( WMSG_WORLD_MERCENARY_DISMISS );
}
		
/**
* rookieListListener
*/
void RecruitMediator::rookieListListener( SCMD300* param )
{
	sendNotification( Facade_Command, AppFacade_RECRUIT_PROXY_CHANGE, (char*)param, RecruitCommand::INIT_ROOKIE_LIST );
}
/**
* dismissListListener
*/
void RecruitMediator::dismissListListener( SCMD301* param )
{
	sendNotification( Facade_Command, AppFacade_RECRUIT_PROXY_CHANGE, (char*)param, RecruitCommand::INIT_DISMISS_LIST );
}
/** 
* 监听招募佣兵返回包
*/
void RecruitMediator::recruitListener( SCMD303* param )
{
	sendNotification( Facade_Command, AppFacade_RECRUIT_PROXY_CHANGE, (char*)param, RecruitCommand::RECRUIT_MERC );
}
/** 
* 解雇佣兵返回包
*/
void RecruitMediator::dismissListener( SCMD305* param )
{
	sendNotification( Facade_Command, AppFacade_RECRUIT_PROXY_CHANGE, (char*)param, RecruitCommand::DISMISS_MERC );
}
	  
void RecruitMediator::mercLimListener( SCMD291* param )
{
	RoleManage::Instance()->accountInfo()->roleLim = param->a_mercLim + 1; // add role hero
	if( _recruitView && _recruitView->getisPop() )
	{
		_recruitView->setTroops( RoleManage::Instance()->accountInfo()->roleNum, RoleManage::Instance()->accountInfo()->roleLim );
	}
}