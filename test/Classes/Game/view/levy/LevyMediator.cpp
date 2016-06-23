#include "LevyMediator.h"
#include "components/LevyView.h"
#include "components/GoldLevyPanel.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "manager/LangManager.h"
#include "manager/ViewManager.h"
#include "socket/command/s32/SCMD321.h"
#include "socket/command/s32/SCMD323.h"
#include "socket/command/s32/SCMD324.h"
#include "socket/command/c32/CCMD322.h"
#include "model/crystal/CrystalProxy.h"
#include "socket/command/c32/CCMD320.h"
#include "Message.h"
#include <cmath>
#include "manager/LayerManager.h"
#include "manager/LevLimitConst.h"

 LevyMediator* g_pLevyMediator = 0;

LevyMediator::LevyMediator()
{
	_levyView = 0;
	_reward = 0;
	_levyNum = 0;
	_uniteNum = 0;        //guild lev
	_starNum = 0;         //start cnt
	firstOpen = false;
	_crysEarthLev = 0;
	_roleLev = 0;
	_crysEfc = 0;
	_earthEfc = 0;
	_levyInfo = 0;
	_goldPanel = 0;
	_tmpRest = 0;

	m_iPreRoleLev = 0;

	GameDispatcher::getInstance()->addEventListener( PopEventName::SHOW_UI_LEVY, this, callfuncND_selector(LevyMediator::loadReportSource) );//发送征收界面信息请求
	GameDispatcher::getInstance()->addEventListener( GameDispatcher::LEVY_TYPE, this, callfuncND_selector(LevyMediator::levyRequestHandler) );//按下按钮请求征收
	GameDispatcher::getInstance()->addEventListener( GameDispatcher::SHOW_GOLD_PANEL, this, callfuncND_selector(LevyMediator::showGoldLevy) );//招财符
}

LevyMediator::~LevyMediator()
{
	CC_SAFE_DELETE(_levyInfo);
}

void LevyMediator::loadReportSource( CCNode* n, void* data )
{
	initHandler();
}

void LevyMediator::showGoldLevy( CCNode* n, void* data )
{
	goldPop();
}

// shangjin
void LevyMediator::goldPop()
{
	if(!_levyView)
	{
		_levyView = new LevyView();					//first open levy
		_levyView->init();
		ViewManager::getInstance()->levyView = _levyView;
		if( !_goldPanel )
		{
			_goldPanel = new GoldLevyPanel;
			_goldPanel->init();
			_levyView->pParentLayerGold->addChild(_goldPanel);
			_goldPanel->setPosition( ccp(POSX(463), POSX(19)) );
			_goldPanel->release();
			
			m_iPreRoleLev = RoleManage::Instance()->roleLev();
		}
		else
		{

		}
	}


	if( !_goldPanel )
	{
		_goldPanel = new GoldLevyPanel;
		_goldPanel->init();
		//_goldPanel->setisPop( true );
		_levyView->pParentLayerGold->addChild(_goldPanel);
		_goldPanel->setPosition( ccp(POSX(463), POSX(19)) );
		_goldPanel->release();
	}
	else
	{
		//_goldPanel->setisPop( !_goldPanel->getisPop() );
	}

	//
	bool var = _levyView->getisPop() ;
	_levyView->setisPop( !_levyView->getisPop() );

	_levyView->release(); //LH20120108

	//
	_levyView->pParentLayerGold->setIsVisible(true);
	_levyView->pParentLayer->setIsVisible(false);
	//
	
	CCMD322 cmd;
	cmd.writeByte( (int8)1 );//2
	GameServerSocket::getInstance()->sendMessage( &cmd );	//CMSG_WORLD_GET_IMPOSE_INFO
}

// wangguoenci
void LevyMediator::initHandler()
{
	if(!_levyView)
	{
		_levyView = new LevyView();					//first open levy
		_levyView->init();
		ViewManager::getInstance()->levyView = _levyView;
		if( !_goldPanel )
		{
			_goldPanel = new GoldLevyPanel;
			_goldPanel->init();
			_levyView->pParentLayerGold->addChild(_goldPanel);
			_goldPanel->setPosition( ccp(POSX(463), POSX(19)) );
			_goldPanel->release();


			m_iPreRoleLev = RoleManage::Instance()->roleLev();
		}
	}

	if( !_goldPanel )
	{
		_goldPanel = new GoldLevyPanel;
		_goldPanel->init();
		//_goldPanel->setisPop( true );
		_levyView->pParentLayerGold->addChild(_goldPanel);
		_goldPanel->setPosition( ccp(POSX(463), POSX(19)) );
		_goldPanel->release();
	}
	else
	{
		//_goldPanel->setisPop( !_goldPanel->getisPop() );
	}

	bool var = _levyView->getisPop() ;
	_levyView->setisPop( !_levyView->getisPop() );
	_levyView->release(); //LH20120108

	//
	_levyView->pParentLayerGold->setIsVisible(false);
	_levyView->pParentLayer->setIsVisible(true);
	//
	if ( RoleManage::Instance()->roleLev() >= LevLimitConst::Limit_GoldLevy )
	{
		if (m_iPreRoleLev < LevLimitConst::Limit_GoldLevy)
		{
			m_iPreRoleLev = RoleManage::Instance()->roleLev();
			if (_goldPanel)
			{
				_goldPanel->initGoldPannel();
				if (_goldPanel->openTxt)
				{
					_goldPanel->openTxt->setIsVisible(false);
					_goldPanel->openTxt->removeFromParentAndCleanup(true);
				}
			}
		}
	}

	CrystalProxy* _crysProxy = (CrystalProxy*)g_pFacade->retrieveProxy( AppFacade_CRYSTAL_PROXY_CHANGE );
	if ( _crysProxy )
		_crysEarthLev = _crysProxy->getCrystalLev( CrystalType::CRYSTAL_TU );
	_roleLev  = RoleManage::Instance()->roleLev();

	CCMD322 cmd;
	cmd.writeByte( (int8)0 );//1
	GameServerSocket::getInstance()->sendMessage( &cmd );	//CMSG_WORLD_GET_IMPOSE_INFO
	
	CCMD322 cmd2;
	cmd2.writeByte( (int8)1 );//1
	GameServerSocket::getInstance()->sendMessage( &cmd2 );	//CMSG_WORLD_GET_IMPOSE_INFO
}

/**
*通过公式计算征收所得 
* @param uniteNum
* @param int
* @param starNum
*/		
void LevyMediator::doSomeMath( int uniteNum, int starNum )
{
	uint iValue = (uint)ceil(  (double)( (_crysEfc+_earthEfc)*(100+uniteNum/2+starNum)/100 )  );
	_levyView->reward( iValue );
}
		
void LevyMediator::levyRequestHandler( CCNode* n, void* data )
{
	CCMD320 cmd;
	cmd.a_type = *(int*)data;
	GameServerSocket::getInstance()->sendMessage( &cmd );	//CMSG_WORLD_IMPOSE

	LayerManager::loadingPic->socketWait_old( WMSG_WORLD_IMPOSE_RESULT );

	//jae 20120801：special pro for error
	if ( cmd.a_type == 2 )
	{
		CCMD322 cmd322;
		cmd322.writeByte( (int8)1 );
		GameServerSocket::getInstance()->sendMessage( &cmd322 );	//CMSG_WORLD_GET_IMPOSE_INFO
	}
}
		
void LevyMediator::levyInitHandler( SCMD323* param )
{  	//levy info
	if( _levyView &&
		(param->a_type==0)
		)
	{
		CC_SAFE_DELETE(_levyInfo);
		_levyInfo = new LevyInfoVo;
		_levyInfo->rest = param->b_rest;
		_levyInfo->max = param->c_max;
		_levyInfo->reward = param->g_reward;			
		_levyInfo->cost = param->h_cost;
		_reward = param->g_reward;
		_uniteNum = param->e_uniteNum;
		_starNum = param->f_starNum;
		_levyView->setInfo( _levyInfo );	//update according init info
		_levyView->setParamInfo( _starNum, _uniteNum, _crysEarthLev, _roleLev );
		firstOpen= true;
	}
	if( _goldPanel &&
		(param->a_type==1) )
	{
		_goldPanel->reward = param->g_reward;
		_goldPanel->setInfo( param->h_cost, param->g_reward, param->b_rest );
	}
}
		
void LevyMediator::levyResultHandler( SCMD321* param )
{   //levy result
	if( ( _tmpRest==1 ) && ( param->d_rest==0 ) )
	{
//		_dispatcher.dispatchEvent(new Event(GameDispatcher.NO_LEVY_LEFT));
	}
	_tmpRest = param->d_rest;
	if( param->a_isSuccess == 0 )  //0 for success
	{
		if( _levyView )
		{
			_levyNum++; 
			switch ( param->b_type )
			{
				case 1:
				_levyView->rest( param->d_rest );    //rest cnt
				_levyView->limit( param->e_limit );
				_levyView->setParamInfo( param->l_starNum, param->k_uniteLev, _crysEarthLev, _roleLev );
				break;
			}
		}
		if( _goldPanel && (param->b_type==2) )
		{
			//_goldPanel->reward = param->i_silver;
			_goldPanel->setInfo( param->c_levyCost, _goldPanel->reward, param->d_rest );
		}			
	}
	else
	{
		Message::Instance()->show( note( param->a_isSuccess ) );
	}
}	
		
string LevyMediator::note( uint type  )
{ //tips
	string note = "";
	switch (type)
	{
	case 0: 
		note = LangManager::getText("LVY001");
		break;
	case 1: 
		note = LangManager::getText("LVY002");
		break;
	case 2: 
		note = LangManager::getText("LVY003");
		break;
	case 3:
		note = LangManager::getText("LVY004");
		break;
	case 4:
		note = LangManager::getText("LVY005");
		break;
	case 5:
		note = LangManager::getText("LVY006");
		break;
	}
	return note;
}
		
void LevyMediator::guildImpose( SCMD324* param )
{
	char txt[128];
	sprintf( txt, ValuesUtil::Instance()->getString("LVY007").c_str(), param->a_silver );
	Message::Instance()->show( txt );
}