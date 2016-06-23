#include "ComProxyCommand.h"
#include "model/backpack/BagProxy.h"
#include "../AppFacade.h"
#include "model/com/vo/DynamicLocation.h"
#include "model/bank/BankProxy.h"
#include "model/figure/FigureProxy.h"
#include "model/com/GoodsDynamicManager.h"
#include "view/mainStreng/MainStrengMediator.h"
#include "model/backpack/GoodsManager.h"

ComProxyCommand::ComProxyCommand()
{

}

ComProxyCommand::~ComProxyCommand()
{

}

void ComProxyCommand::execute( int32 command, char* data )
{
	//BagProxy* _bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
	//_figureProxy = facade.retrieveProxy(FigureProxy.NAME) as FigureProxy;
	//_bankProxy = facade.retrieveProxy(BankProxy.NAME) as BankProxy;

	switch( command )
	{
	case UPDATE_GOODS_DYNAMIC:
		updateGoodsDynamic( (SCMD16F*)data );
		break;
	case CHAT_SHOW_DYNAMIC:
		//createChatShowDynamic(  );
		break;
	}
}

void ComProxyCommand::updateGoodsDynamic( SCMD16F* obj )
{
	uint location = obj->a_locationType;
	uint sitNum = obj->b_sitNum;
	uint strength = obj->d_strength;
	uint roleId = obj->c_roleId;	
	GoodsInfo* goodInfo = getGoodsInfo( location, sitNum, roleId );
	if(  goodInfo && ( goodInfo->equip_type != 7 )  )
	{
		GoodsBasic* goodBasic = g_pGoodsManager->getBasicGood( goodInfo->goodId );
		if ( goodBasic )
		{
			goodInfo->strengthen = strength;
			goodInfo->stamina = obj->e_stamina;
			goodInfo->wrist = obj->f_wrist;
			goodInfo->intellect = obj->g_intellect;
			g_pGoodsDynamicManager->createDynamic( goodInfo, goodBasic );
			setDynamicInfo( location, sitNum, roleId );
		}
	}
}

GoodsInfo* ComProxyCommand::getGoodsInfo( uint location, uint grid, uint roleId )
{
	BagProxy* _bagProxy = (BagProxy*)g_pFacade->retrieveProxy( AppFacade_BAG_PROXY_CHANGE );
	BankProxy* _bankProxy = (BankProxy*)g_pFacade->retrieveProxy( AppFacade_BANK_PROXY_CHANGE );
	FigureProxy* _figureProxy = (FigureProxy*)g_pFacade->retrieveProxy( AppFacade_FIGURE_PROXY );

	GoodsInfo* goodInfo = 0;
	switch( location )
	{
	case BAG:
		goodInfo = _bagProxy->goodsInfo( grid );
		break;
	case BANK:
		goodInfo = _bankProxy->goodsInfo( grid );
		break;
	case FIGURE:
		goodInfo = _figureProxy->goodsInfo( roleId, grid );
		break;				
	}
	return goodInfo;
}

void ComProxyCommand::setDynamicInfo( uint location , uint grid, uint roleId )
{
	BagProxy* _bagProxy = (BagProxy*)g_pFacade->retrieveProxy( AppFacade_BAG_PROXY_CHANGE );
	BankProxy* _bankProxy = (BankProxy*)g_pFacade->retrieveProxy( AppFacade_BANK_PROXY_CHANGE );
	FigureProxy* _figureProxy = (FigureProxy*)g_pFacade->retrieveProxy( AppFacade_FIGURE_PROXY );

	struct
	{
		uint location;
		uint sitNum;
		uint roleID;
	} notifyNode;
	notifyNode.location = location;
	notifyNode.sitNum = grid;
	notifyNode.roleID = roleId;

	switch( location )
	{
	case BAG:
		_bagProxy->setDynamicInfo(grid);
		g_pMainStrengMediator->updateStrengTip( (char*)&notifyNode );
		//sendNotification( MainStrengMediator::STRENG_VIEW_TIP, {location:location,sitNum:grid,roleID:roleId} );
		break;
	case BANK:
		_bankProxy->setDynamicInfo( grid );
		break;
	case FIGURE:
		_figureProxy->setDynamicInfo( roleId, grid );
		g_pMainStrengMediator->updateStrengTip( (char*)&notifyNode );
		//sendNotification( MainStrengMediator::STRENG_VIEW_TIP, {location:location,sitNum:grid,roleID:roleId} );
		break;				
	}
}
