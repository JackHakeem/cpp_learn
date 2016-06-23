#include "MainStrengMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "socket/network/GameServerSocket.h"
#include "model/player/RoleManage.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "utils/flash/CCIEventDispatcher.h"
#include "components/MainStrengView.h"
#include "manager/ViewManager.h"
#include "components/StrengPanel.h"
#include "model/figure/EquipmentManager.h"
#include "model/com/GoodsDynamicManager.h"
#include "model/streng/vo/StrengGoodsVo.h"
#include "socket/command/c30/CCMD308.h"
#include "model/backpack/BagProxy.h"
#include "socket/command/c18/CCMD180.h"
#include "socket/command/s18/SCMD181.h"
#include "model/com/vo/DynamicLocation.h"
#include "Message.h"
#include "utils/ValuesUtil.h"
#include "components/MeltingPanel.h"
#include "model/com/vo/GoodsDynamic.h"
#include "socket/command/c2d/CCMD2D2.h"
#include "socket/command/s2d/SCMD2D3.h"
#include "socket/command/c2d/CCMD2D6.h"
#include "socket/command/s2d/SCMD2D7.h"
#include "manager/LangManager.h"
#include "model/crystal/CrystalProxy.h"
#include "socket/command/c2d/CCMD2D8.h"
#include "socket/command/c16/CCMD16E.h"
#include "socket/command/s17/SCMD17D.h"
#include "socket/command/c17/CCMD17C.h"
#include "manager/CDManage.h"
#include "events/CDEvent.h"
#include "model/newhand/NewhandManager.h"
#include "model/newhand/vo/TestNewhand.h"
#include "model/newhand/vo/NewhandConst.h"
#include "socket/command/c2d/CCMD2DE.h"
#include "../notify/NotifyManager.h"
#include "../notify/NotifyType.h"

MainStrengMediator* g_pMainStrengMediator = 0;

MainStrengMediator::MainStrengMediator()
{
	_roleManage = RoleManage::Instance();
	_dispatcher = GameDispatcher::getInstance();

	_mainStrengView = 0;
	_strengPanel = 0;
	_meltingPanel = 0;
	_magicPanel = 0;
	_inheritPanel = 0;

	_roleManage = RoleManage::Instance();

	_dispatcher->addEventListener( PopEventName::SHOW_UI_STRENG, this,
		callfuncND_selector(MainStrengMediator::mainOpenPop) );
	_dispatcher->addEventListener(GameDispatcher::SHOW_STRENG_CLICK,
		this, callfuncND_selector(MainStrengMediator::equipmentOnclickHandler) );
	_dispatcher->addEventListener(GameDispatcher::MELTING_GOODS_CHANGE,
		this, callfuncND_selector(MainStrengMediator::gridClickHandler) );
	_dispatcher->addEventListener(GameDispatcher::MAGIC_REQUEST, this,
		callfuncND_selector(MainStrengMediator::equipmentMagicHandler) );
	_dispatcher->addEventListener( GameDispatcher::INHERIT_REQUEST, this,
		callfuncND_selector(MainStrengMediator::heritageClickHandler) );

	CDManage::Instance()->addEventListener( CDManage::CDCHANGED, this, callfuncND_selector(MainStrengMediator::cdChangedHandler) ); 
}

MainStrengMediator::~MainStrengMediator()
{
}

void MainStrengMediator::handleNotification( int M2Vcmd, char* data )
{
	switch(M2Vcmd)
	{
	case STRENG_VIEW_TIP:
		updateStrengTip( data );
		break;
	}
}

void MainStrengMediator::mainOpenPop(CCNode* n, void* data)
{
	mainViewPop();
}


/**
 * main view
 *
 */
void MainStrengMediator::mainViewPop()
{
	if (!_mainStrengView)
	{
		_mainStrengView = new MainStrengView();
		_mainStrengView->init();
		ViewManager::getInstance()->_mainStrengView = _mainStrengView;
	}
	if ( _mainStrengView->getisPop() )
	{
		_mainStrengView->setisPop(false);
		//LH20120108
		_mainStrengView->release();
	}
	else
	{
		_mainStrengView->setDefaultStrengPanel();
		//_mainStrengView.openMagicPanel(_roleManage.accountInfo.crystalLev);
		_mainStrengView->setisPop(true);
		_mainStrengView->release();
	}
}

/**
 *  mainboard tab change
 * @param e
 *
 */
void MainStrengMediator::tabChange( int type )
{
	//var type:int=e.param.type;
	//var skin:MovieClip=e.param.panel as MovieClip;
	switch (type)
	{
		case 1: // streng
			if ( !_strengPanel )
			{
				_strengPanel = ViewManager::getInstance()->strengPanel;
			}
			//_strengPanel->resetStrengCreate(); // reset figure list	
			openStreng();
			//var hasCD:Boolean=NewhandManager.getInstance().isOpenButton(NewhandConst.ENABLE_STRENG_CD);
			//_strengPanel.showNoCDText(hasCD);
			break;
		case 2: //melting
			{
				if ( !_meltingPanel )
				{ 
					_meltingPanel = _mainStrengView->meltingPanel;
					//_meltingPanel.addEventListener(MeltingPanel.PAGE_CHANGE, bagPageChange);
					_mainStrengView->addEventListener( MainStrengView::MELTING_CLICK, this, callfuncND_selector(MainStrengMediator::meltingClickHandler));
				}
				_meltingPanel->clear();
				BagProxy* _bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
				_meltingPanel->createMeltingList( _bagProxy->_goodsList );
				_meltingPanel->updateSparInfo( _roleManage->accountInfo()->stone() );
				_meltingPanel->roleVipLev( _roleManage->accountInfo()->vipLev() );
			}
			break;
		case 3: //magic
			{
				if ( !_magicPanel )
				{ 
					_magicPanel = _mainStrengView->magicPanel;
					//_mainStrengView->addEventListener( MainStrengView::MELTING_CLICK, this, callfuncND_selector(MainStrengMediator::figureClickHandler));
				}
				//_magicPanel->resetStrengCreate(); // reset figure list
				_magicPanel->updateSparInfo( RoleManage::Instance()->accountInfo()->stone() );
				_magicPanel->roleVipLev( RoleManage::Instance()->accountInfo()->vipLev() );

				CrystalProxy* _crystalProxy	= (CrystalProxy*)g_pFacade->retrieveProxy(AppFacade_CRYSTAL_PROXY_CHANGE);
				_magicPanel->crystalLev( _crystalProxy->getCrystalLev( 39 ) );
				openMagic();
			}
			break;
		case 4: //chuanceng
			{
				if ( !_inheritPanel )
				{ 
					_inheritPanel = _mainStrengView->inheritPanel;
				}
				_inheritPanel->clear();
			
				BagProxy* _bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
				_inheritPanel->creatEquipmentList( &_bagProxy->_goodsList );
				break;
			}
	}
}

/** -------------------------------------------------------- Streng -------------------------------------------------------- **/


void MainStrengMediator::openStreng()
{
	int mainRoleId(0);
	if ( RoleManage* pRoleManage = RoleManage::Instance() )
	{
		if ( AccountInfoVo* pAccountInfoVo = pRoleManage->accountInfo() )
		{
			mainRoleId = pAccountInfoVo->roleId;
		}
	}
	EquipmentManager* pEquipmentManager = EquipmentManager::Instance();
	if (  pEquipmentManager && !pEquipmentManager->getEquipment( mainRoleId )  )
	{
		// no equip
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if ( !pSocket ) return;
		CCMD308 packet308;
		packet308.a_byte=0;
		pSocket->sendMessage(&packet308);
	}
	else
	{
		createList();
	}
}

/**
 *  initial prob main board
 *
 */
void MainStrengMediator::createList()
{
	if ( _strengPanel )
	{
		_strengPanel->openStreng( CDManage::Instance()->getLockBytype(CDManage::STRENGTHEN) );

		//if ( !_strengPanel->figureItem() )
		//{
		//	_strengPanel->bagClickHandler();
		//}
		
		if ( RoleManage::Instance()->roleLev() <= 20 )
		{
			// execute streng prob
			_strengPanel->updateStriengPropAtFirst(100);
		}
		else
		{
			CCMD17C cmd;
			GameServerSocket::getInstance()->sendMessage( &cmd );	//CMSG_WORLD_SYS_EQUIPSTREN_PROB
		}
	}
}

void MainStrengMediator::getBagEquipment()
{
	if (_strengPanel)
	{
		BagProxy* _bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
		_strengPanel->creatBagEquipmentList( &_bagProxy->_goodsList );
	}
}

/**
* streng CD changed notice
* */
void MainStrengMediator::cdChangedHandler( CCNode* n, void* data )
{
	CDEvent* e = (CDEvent*)data;
	if( e->cdType == CDManage::STRENGTHEN )
	{
		if(_strengPanel)
		{
			_strengPanel->CDchange( e->lock );
		}
		//if(ViewManager.getInstance().cdList&&RoleManage.getInstance().roleLev<=36)
		//{
		//	if (ViewManager.getInstance().cdList.getNewHandItem(CDManage.STRENGTHEN)&&e.lock==0)
		//		obGlow = new ObjectGlow(ViewManager.getInstance().cdList.getNewHandItem(CDManage.STRENGTHEN));
		//}
	}
}

/**
 * Choose Equip（wear or in bag）
 * @param e
 *
 */
void MainStrengMediator::onTabClick( int roleID )
{
	if (!_strengPanel)
		return;

	if (roleID != 0)
	{
		if ( EquipmentManager::Instance()->getEquipment(roleID) == 0 )
		{
	//		_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_MERCENARY_EQUIP_INFO, new Int8(0));
			// Haven't equiment details in, send request
			GameServerSocket* pSocket = GameServerSocket::getInstance();
			if ( !pSocket ) return;
			CCMD308 packet308;
			packet308.a_byte=0;
			pSocket->sendMessage(&packet308);
		}
		else
		{
			bool bHasEquip = _strengPanel->creatRoleEquipmentList(roleID);
			_strengPanel->setAttriVisible(bHasEquip);	
		}
	//	//new hand direct，Click someone
		//if(NewhandManager::Instance()->_nextEventId == NewhandConst::EVENT_STRENG_SELECT_MERC)
		if((!NewhandManager::Instance()->_nextEventIdList.empty()) 
			&& (NewhandManager::Instance()->_nextEventIdList.front() == NewhandConst::EVENT_STRENG_SELECT_MERC))
		{
			PlayerInfoVo *pInfo = RoleManage::Instance()->getMercenary(roleID);
			int typeId = -1;
			if(NewhandManager::Instance()->_pCurScript)
			{
				typeId = NewhandManager::Instance()->_pCurScript->typeId;
			}
			if(pInfo == NULL || typeId == -1)
			{
				return;
			}
			if(typeId == pInfo->figureBaseInfo.mercId || 
				(typeId == 999 && pInfo->playerBaseInfo.isRole))
			{
				//Doyang 20120712
				TestNewhand *pTestNewhand = new TestNewhand("evt", NULL, NewhandConst::EVENT_STRENG_SELECT_MERC);
				GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::TEST_NEW_HAND, 
					pTestNewhand);
				CC_SAFE_DELETE(pTestNewhand);
			}
		}
	}
	else
	{
		getBagEquipment();
	//	_strengPanel.addEventListener(StrengPanel.PAGECHANGE, getBagEquipment);
	}
}

/**
 * Update tips
 * @param param
 *
 */
void MainStrengMediator::updateStrengTip( char* obj )
{
	struct NotifyNode
	{
		uint location;
		uint sitNum;
		uint roleID;
	} param;

	param = *(NotifyNode*)obj;

	GoodsInfo* info;
	BagProxy* _bagProxy = (BagProxy*)g_pFacade->retrieveProxy( AppFacade_BAG_PROXY_CHANGE );
	if ( param.location == FIGURE )
		info = EquipmentManager::Instance()->getEquip( param.roleID, param.sitNum );
	else
		info = _bagProxy->goodsInfo( param.sitNum );

	if ( _strengPanel && _strengPanel->getIsVisible() )
	{
		_strengPanel->updateTip( info->id );
	}
	if ( _magicPanel && _magicPanel->getIsVisible() )
	{
		_magicPanel->updateTip( info->id );
	}
	if (_inheritPanel&&_inheritPanel->getIsVisible())
	{
		_inheritPanel->updateTip( info->id );
	}
	
}

/**
* Send prop dynamic detail request
* @param*************************************************************************************************************** location
* @param sitNum
* @param roleId
*
*/
void MainStrengMediator::sendSocketDynamic( int location, int sitNum, int roleId /*= 0*/ )
{
	CCMD16E cmdDym;
	cmdDym.a_locationType = location;
	cmdDym.b_sitNum = sitNum;
	cmdDym.c_roleId = roleId;
	GameServerSocket::getInstance()->sendMessage( &cmdDym ); // CMSG_WORLD_ITEM_INFO
}

void MainStrengMediator::equipmentOnclickHandler(CCNode* n, void* data)
{
	if (!data)
		return;

	int UseType = *(int*)data;

	struct sdata
	{
		int UseType;
		StrengGoodsVo* sdataStrengGoodsVo;
	} param1;

	struct sdataType2
	{
		int UseType;
		int probability;
		int strengtype;
		int vip;
		StrengGoodsVo* sdataStrengGoodsVo;
	} param2;

	StrengGoodsVo* strengGoodsVo;
	if ( UseType == 2 )
	{
		param2 = *(sdataType2*)data;
		strengGoodsVo = param2.sdataStrengGoodsVo;
	}
	else
	{
		param1 = *(sdata*)data;
		strengGoodsVo = param1.sdataStrengGoodsVo;
	}

	if (!strengGoodsVo)
		return;

	GoodsInfo* pGoodInfo = strengGoodsVo->StrengGoodsInfo;
	if (!pGoodInfo)
		return;

	switch (UseType)
	{
		case 1: // Get prob detail
			{
				GoodsDynamic* goodsDynamic = g_pGoodsDynamicManager->getGoodsDynamic( pGoodInfo->id );
				if ( goodsDynamic )
				{
					sendSocketDynamic( strengGoodsVo->type, strengGoodsVo->sitGrid, strengGoodsVo->roleId );
				}
			}
			break;
		case 2: // Streng Degrete
			{
				CCMD180 cmdStreng;
				cmdStreng.a_typeSit = param2.sdataStrengGoodsVo->type;
				cmdStreng.b_sit = param2.sdataStrengGoodsVo->sitGrid;
				cmdStreng.c_isVIP = param2.vip;
				cmdStreng.d_strengType = param2.strengtype;
				cmdStreng.e_probability = param2.probability;
				cmdStreng.f_roleID = param2.sdataStrengGoodsVo->roleId;
				GameServerSocket::getInstance()->sendMessage( &cmdStreng );	// CMSG_WORLD_ITEM_STRENGTHEN

				LayerManager::loadingPic->socketWait_old( WMSG_WORLD_ITEM_STRENGTHEN_RESULT );
			}
			break;
		case 6: // Check Prob Detail
			if ( _strengPanel && _strengPanel->getIsVisible() )
			{
				_strengPanel->viewEquipmentInfo( pGoodInfo->id, pGoodInfo->goodId );
				//// New hand director，Click Equipment with him
				//if(NewhandManager.getInstance().nextEventId==NewhandConst.EVENT_STRENG_SELECT_EQUIP){
				//	var goodBasic:GoodsBasic = GoodsManager.getInstance().getBasicGood(e.param.goodId);
				//	if(NewhandManager.getInstance().curScript.typeId==goodBasic.equip_type){
				//		_dispatcher.dispatchEvent(new ParamEvent(GameDispatcher.TEST_NEW_HAND, 
				//			{type:"evt", id:NewhandConst.EVENT_STRENG_SELECT_EQUIP}));
				//	}
				//}
			}
			if ( _magicPanel && _magicPanel->getIsVisible() )
			{
				_magicPanel->viewEquipmentInfo( pGoodInfo->id, pGoodInfo->goodId );
			}
			break;
	}
}

/**
* Prob packet response
* */
void MainStrengMediator::sockStrengInfo( SCMD181* param )
{
	string arry[12];

	ValuesUtil* pValuesUtil = ValuesUtil::Instance();
	char txt[54];
	for ( int i = 0; i < 12; i++ )
	{
		sprintf( txt, "STG%03d", i+1 );
		arry[i] = pValuesUtil->getString( txt );
	}	

	BagProxy* _bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);

	EquipmentManager* pEquipmentManager = EquipmentManager::Instance();

	uint isSuccess = param->a_isSuccess;
//	GoodsInfo* info;
//
//	if ( param->b_typeSit == FIGURE )
//		info = pEquipmentManager->getEquip( param->g_roleID, param->c_sit );
//	else
//		info = _bagProxy->goodsInfo( param->c_sit );

	//CrystalProxy* _crystalProxy = (CrystalProxy*) g_pFacade->retrieveProxy(AppFacade_CRYSTAL_PROXY_CHANGE);
	if ( isSuccess == 0 || isSuccess == 10 )
	{
		ccColor3B color  = { 0, 255, 0 };
		uint typeSit = (uint)param->b_typeSit;
		uint sit = (uint)param->c_sit;
		int roleID = param->g_roleID;
		uint strengLevl = (uint)param->h_strengLevle;
		//GoodsInfo* aGoodInfo = 0;
		sendSocketDynamic( typeSit, sit, roleID );

		if ( RoleManage::Instance()->roleLev() >= 20 && _strengPanel &&_strengPanel->getIsVisible() )
		{
			// Larger than 20,then update prob
			_strengPanel->updateStrengProp( (uint)param->e_probability, (uint)param->f_strengChange );
		}
		if ( param->d_isVIP == 1 )
		{
			//d_isVIP = 1 level up  
			if (_strengPanel)
				_strengPanel->playStrengEffect( isSuccess == 0 ? false : true ); //param  >>> Critical or not
			Message::Instance()->show( arry[isSuccess], color );
		}
		else
		{
			Message::Instance()->show( pValuesUtil->getString("STG013"), color );
			if ( strengLevl == 0 && _strengPanel )
			{
				_strengPanel->strengLevLow();
			}
		}
	}
	else
	{
		ccColor3B color  = { 255, 0, 0 };
		Message::Instance()->show( arry[isSuccess], color );
		if (isSuccess == 7)
		{ // When strengthen probability change need to apply for a but level 20 has to change, and not before
			if ( RoleManage::Instance()->roleLev() <= 20 && _strengPanel->getIsVisible() )
			{
				_strengPanel->updateStriengPropAtFirst( 100 );
			}
			else
			{
				CCMD17C cmd;
				GameServerSocket::getInstance()->sendMessage( &cmd );	//CMSG_WORLD_SYS_EQUIPSTREN_PROB
			}
		}
	}


	// LH20121018 for newhand
	NewhandManager::Instance()->touchNextEvent(119);
}

/**
* Streng prob
* */
void MainStrengMediator::sockStrengPROBchange( SCMD17D* param )
{
	_strengPanel->updateStrengProp( (int)param->a_Probability, (int)param->b_Trend );
	
	// LH20121107
	if (param->a_Probability == 100)
	{
		if( (_mainStrengView && !_mainStrengView->getisPop())
			|| !_mainStrengView)
		{
			NotifyManager::Instance()->addNotification(NotifyType::NType_Strength);
		}
	}
}


StrengPanel* MainStrengMediator::getStrengPanel()
{
	return _strengPanel;
}

/** -------------------------------------------------------- Melting -------------------------------------------------------- **/
/* page change
* @param e
*
*/
void  MainStrengMediator::bagPageChange(  )
{
	if ( !_meltingPanel )
		return;
	//_meltingPanel.createBagList(e.param.page);
}

void MainStrengMediator::gridClickHandler( CCNode* n, void* data )
{
	if (!data)
		return;

	int UseType = *(int*)data;

	struct sdata
	{
		int UseType;
		GoodsInfo* goodInfo;
	} param1;

	struct sdataType2
	{
		int UseType;
		GoodsInfo* info;
		int sitNum;
		int page;
		int type;
	} param2;

	GoodsInfo* goodsInfo;
	if ( UseType == 2 )
	{
		param2 = *(sdataType2*)data;
		goodsInfo = param2.info;
	}
	else
	{
		param1 = *(sdata*)data;
		goodsInfo = param1.goodInfo;
	}

	if ( !goodsInfo )
		return;

	switch ( UseType )
	{
		case 1: //check dynamic
			{
				GoodsDynamic* goodsDynamic = g_pGoodsDynamicManager->getGoodsDynamic( goodsInfo->id );
				if ( !goodsDynamic )
				{
					sendSocketDynamic( BAG, goodsInfo->sitGrid, 0 );
				}
			}
			break;
		case 2: //drag prop
			{
				if ( goodsInfo->type == 2 )
				{
					//if ( goodsInfo->strengthen > 0 )
					//{
					//	LangManager::msgShow("STG014");
					//	return;
					//}
					GoodsDynamic* goods = g_pGoodsDynamicManager->getGoodsDynamic( goodsInfo->id );
					if (  ( goods->u_stamina + goods->v_wrist + goods->w_intellect ) > 0  )
					{
						LangManager::msgShow("STG015");
						return;
					}
				}

				int sitNum = param2.sitNum; //bag pos（melting bag）
				int page = param2.page; //page index in melting bag
				int type = param2.type; //melting sit pos（3 total）
				if ( !_meltingPanel )
					return;
				_meltingPanel->dragGrid( goodsInfo, sitNum, page, type );
			}
			break;
	}
}

void MainStrengMediator::meltingClickHandler( CCNode* n, void* data )
{
	if (!data)
		return;
	
	struct sdata
	{
		int id1;
		int id2;
		int id3;
		int vip;
	} param;

	param = *(sdata*)data;

	if (RoleManage::Instance()->roleLev() < 50){
		LangManager::msgShow("STG016");
		return;
	}
	int gold = RoleManage::Instance()->accountInfo()->gold();
	switch (param.vip){
	case 3:
		if (gold < 20){
			LangManager::msgShow("STG017");
		}
		break;
	case 5:
		if (gold < 60){
			LangManager::msgShow("STG018");
		}
		break;
	case 7:
		if (gold < 100){
			LangManager::msgShow("STG019");
		}
		break;
	}
	CCMD2D2 cmd;
	cmd.a_vip = param.vip;
	cmd.b_id1 = param.id1;
	cmd.c_id2 = param.id2;
	cmd.d_id3 = param.id3;
	GameServerSocket::getInstance()->sendMessage( &cmd );// CMSG_WORLD_SMELT

	LayerManager::loadingPic->socketWait_old( WMSG_WORLD_SMELT );
}

void MainStrengMediator::returnMeltingInfo( SCMD2D3* param )
{
	if (!_meltingPanel)
		return;
	int type = param->a_type;
	int num = param->b_sparBum;
	if ( type == 1 )
	{
		if( num == _meltingPanel->_sparNum )
		{
			LangManager::msgShow("STG020");
			//Message::Instance()->show( ValuesUtil::Instance()->getString( "STG020" ) );
		}
	//	_meltingPanel.playEffect();
		_meltingPanel->updateSparInfo(num);
	}
	else
	{
		LangManager::msgShow("STG021");
		//Message::Instance()->show( ValuesUtil::Instance()->getString( "STG021" ) );
	}
	_meltingPanel->clear();
	BagProxy* _bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
	_meltingPanel->createMeltingList( _bagProxy->_goodsList );
}

/** -------------------------------------------------------- magic -------------------------------------------------------- **/

void MainStrengMediator::openMagic()
{
	int mainRoleId(0);
	if ( AccountInfoVo* pAccountInfoVo = RoleManage::Instance()->accountInfo() )
	{
		mainRoleId = pAccountInfoVo->roleId;
	}

	if (  !EquipmentManager::Instance()->getEquipment( mainRoleId )  )
	{
		// no equip
		CCMD308 packet308;
		packet308.a_byte = 0;
		GameServerSocket::getInstance()->sendMessage(&packet308);
	}
	else
	{
		createMagicList();
	}
}

void MainStrengMediator::createMagicList()
{
	if ( _magicPanel )
	{
		_magicPanel->openMagic();
		if ( !_magicPanel->figureItem() )
		{
			_magicPanel->bagClickHandler(0);
		}
	}
}

void MainStrengMediator::getMagicBagEquipment()
{
	if ( _magicPanel )
	{
		BagProxy* _bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
		_magicPanel->creatBagEquipmentList( &_bagProxy->_goodsList );
	}
}

/**
* client --> server magic request
* @param e
*/
void MainStrengMediator::equipmentMagicHandler( CCNode* n, void* data )
{
	struct sdata
	{
		int type;
		int sit;
		int id;
		int vip;
	} param;
	param = *(sdata*)data;

	if (param.vip == 3){
		if (RoleManage::Instance()->accountInfo()->gold() < 50){
			LangManager::msgShow("STG022");
			return;
		}
	}
	CCMD2D6 cmdMagic;
	cmdMagic.a_type = param.type;
	cmdMagic.b_sit = param.sit;
	cmdMagic.c_id = param.id;
	cmdMagic.d_vip = param.vip;
	GameServerSocket::getInstance()->sendMessage( &cmdMagic );	//	CMSG_WORLD_ENCHANT

	LayerManager::loadingPic->socketWait_old( WMSG_WORLD_ENCHANT );
}

/**
* magic result
* @param param
*
*/
void MainStrengMediator::returnMagicResult( SCMD2D7* param )
{
	if (!_magicPanel)
		return;

	int type = param->a_type; //魔化是否成功：0，成功；1，失败，低于成功率；2，晶体不够；3，装备不符合要求；4，魔化属性达到上限
	int num = param->c_sparNum; //剩余魔晶石数量
	switch ( type )
	{
		case 0:
			{
				int att = param->b_attribute; //魔化属性：0，体格；1，腕力；2智力
				if ( att == 0 )
					LangManager::msgShow("STG023");
				else if (att == 1)
					LangManager::msgShow("STG024");
				else
					LangManager::msgShow("STG025");

				int location = param->e_location;
				int sit = param->f_sit;
				int roleId = param->g_roleId;
				// 临时更改 加魔化属性
				if( location == 3 && roleId>0 )
				{
					PlayerInfoVo* info = RoleManage::Instance()->getMercenary(roleId);
					if( info )
					{
						if( att == 0 )
						{
							info->figureBaseInfo.plus_sta += 1;
						}
						else if( att == 1 )
						{
							info->figureBaseInfo.plus_str += 1;
						}
						else if ( att == 1 )
						{
							info->figureBaseInfo.strength += 1;
							info->figureBaseInfo.plus_str += 1;
						}
						else
						{
							info->figureBaseInfo.plus_int += 1;
						}
						// LH20121020
						RoleManage::Instance()->updateMercenaryEx(roleId , info);
					}
				}

				sendSocketDynamic(location, sit, roleId);
				_magicPanel->updateSparInfo( num );
				//_magicPanel.playEffect();
			}
			break;
		case 1:
			LangManager::msgShow("STG026");
			_magicPanel->updateSparInfo(num);
			break;
		case 2:
			LangManager::msgShow("STG027");
			_magicPanel->updateSparInfo(num);
			break;
		case 3:
			LangManager::msgShow("STG028");
			_magicPanel->updateSparInfo(num);
			break;
		case 4:
			LangManager::msgShow("STG006");
			_magicPanel->updateSparInfo(num);
			break;
		case 5:
			LangManager::msgShow("STG029");
			_magicPanel->updateSparInfo(num);
			break;
	}
}

/**
* figure or bag click，show info on right
* @param roleID	:role ID，0:bag
*
*/
void MainStrengMediator::figureClickHandler( int roleID )
{
	if (!_magicPanel)
		return;

	if (roleID != 0)
	{
		if ( !EquipmentManager::Instance()->getEquipment(roleID) )
		{
			CCMD308 cmd;
			cmd.a_byte = 0;
			GameServerSocket::getInstance()->sendMessage( &cmd );	// CMSG_WORLD_MERCENARY_EQUIP_INFO
		}
		else
		{
			_magicPanel->creatRoleEquipmentList(roleID);
		}
	}
	else
	{
		getMagicBagEquipment();
	}
}

/** -------------------------------------------------------- 传承 -------------------------------------------------------- **/

/**
* 客户端 --> 服务端 请求传承
* @param e
*
*/
//void MainStrengMediator::inheritClickHandler( CCNode* n, void* data )
//{
//	int gold = RoleManage::Instance()->accountInfo()->gold();
//
//	struct sData
//	{
//		int	vip;
//		int	cost;
//		int	sourcePos;
//		int	sourceSit;
//		int	sourceRoleId;
//		int	inheritPos;
//		int	inheritSit;
//		int	inheritRoleId;
//	} param;
//	param = *(sData*)data;
//
//	switch ( param.vip )
//	{
//		case 4:
//			if (gold < param.cost)
//			{
//				LangManager::msgShow("STG030");
//			}
//			break;
//		case 6:
//			if (gold < param.cost)
//			{
//				LangManager::msgShow("STG031");
//			}
//			break;
//		case 9:
//			if (gold < param.cost)
//			{
//				LangManager::msgShow("STG032");
//			}
//			break;
//	}
//
//	CCMD2DA cmdInherit;
//	cmdInherit.a_vip = param.vip;
//	cmdInherit.b_sPos = param.sourcePos;
//	cmdInherit.c_sSit = param.sourceSit;
//	cmdInherit.d_sRoleId = param.sourceRoleId;
//	cmdInherit.e_sPos = param.inheritPos;
//	cmdInherit.f_sSit = param.inheritSit;
//	cmdInherit.g_sRoleId = param.inheritRoleId;
//	GameServerSocket::getInstance()->sendMessage( &cmdInherit );	//CMSG_WORLD_INHERI
//
//	LayerManager::loadingPic->socketWait_old( WMSG_WORLD_INHERI );
//}
//
///**
//* returnInheritList
//* @param param
//*
//*/
//void MainStrengMediator::returnInheritList( SCMD2D9* param )
//{
//	if ( param->a_goodsArray.size() == 0 || !_inheritPanel )
//	{
//		return;
//	}
//	if ( _inheritPanel )
//	{
//		_inheritPanel->createInheritList( param->a_goodsArray );
//	}
//
//}
//
///**
//* returnInheritResult
//* @param param
//*
//*/
//void MainStrengMediator::returnInheritResult( SCMD2DB* param )
//{
//	if ( param->a_type == 0 )
//	{
//		LangManager::msgShow("STG034");
//	}
//	else
//	{
//		int location1 = param->c_location;
//		int sit1 = param->d_sit;
//		int roleId1 = param->e_roleId;
//		int location2 = param->g_location;
//		int sit2 = param->h_sit;
//		int roleId2 = param->i_roleId;
//		sendSocketDynamic( location1, sit1, roleId1 );
//		sendSocketDynamic( location2, sit2, roleId2 );
//		CCMD2D8 cmd;
//		GameServerSocket::getInstance()->sendMessage( &cmd );	//CMSG_WORLD_INHERITABLE_INFO
//		LangManager::msgShow("STG033");
//
//		LayerManager::loadingPic->socketWait_old( WMSG_WORLD_INHERITABLE_INFO );
//	}
//}


/** -------------------------------------------------------- 装备传承 -------------------------------------------------------- **/

/**
* 客户端 --> 服务端 请求传承
* @param e
*
*/

void MainStrengMediator::heritageClickHandler( CCNode* n, void* data )
{
	int gold = RoleManage::Instance()->accountInfo()->gold();
	int silver = RoleManage::Instance()->accountInfo()->silver();

	struct sData
	{
		int type;
		int	cost;
		int	sourcePos;
		int	sourceSit;
		int	sourceRoleId;
		int	inheritPos;
		int	inheritSit;
		int	inheritRoleId;
	} param;
	param = *(sData*)data;

	if (param.type==0)
	{
		if (silver < param.cost)
		{
			LangManager::msgShow("GLD004");
			return;
		}
	} 
	else
	{
		if (gold < param.cost)
		{
			LangManager::msgShow("COM602");
			return;
		}
	}	
	
	_inheritPanel->clear();

	CCMD2DE cmdInherit;
	cmdInherit.a_type = param.type;
	cmdInherit.b_sPos = param.sourcePos;
	cmdInherit.c_sSit = param.sourceSit;
	cmdInherit.d_sRoleId = param.sourceRoleId;
	cmdInherit.e_sPos = param.inheritPos;
	cmdInherit.f_sSit = param.inheritSit;
	cmdInherit.g_sRoleId = param.inheritRoleId;
	GameServerSocket::getInstance()->sendMessage( &cmdInherit );	//CMSG_WORLD_INHERI

	LayerManager::loadingPic->socketWait_old( WMSG_WORLD_INHERI );
}


/**
* returnInheritResult
* @param param
*/
void MainStrengMediator::returnHeritageResult( SCMD2DF* param )
{
	if ( param->a_type == 0 )
	{
		LangManager::msgShow("STG034");
	}
	else
	{
		int location1 = param->c_location;
		int sit1 = param->d_sit;
		int roleId1 = param->e_roleId;
		int location2 = param->g_location;
		int sit2 = param->h_sit;
		int roleId2 = param->i_roleId;

		sendSocketDynamic( location1, sit1, roleId1 );
		sendSocketDynamic( location2, sit2, roleId2 );

		BagProxy* _bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
		_inheritPanel->creatEquipmentList( &_bagProxy->_goodsList );

		LangManager::msgShow("STG033");

		LayerManager::loadingPic->socketWait_old( WMSG_WORLD_INHERITABLE_INFO );
	}
}