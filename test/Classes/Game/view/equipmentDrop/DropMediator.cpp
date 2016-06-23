#include "DropMediator.h"
#include "control/AppFacade.h"
#include "control/backpack/BagProxyCommand.h"
#include "manager/ViewManager.h"
#include "mvc/Facade.h"
#include "model/backpack/BagProxy.h"
#include "model/bank/BankProxy.h"
#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"
#include "model/com/GoodsDynamicManager.h"
#include "model/com/vo/GoodsDynamic.h"
#include "socket/network/GameServerSocket.h"
#include "events/GameDispatcher.h"
#include "manager/PopManage.h"
#include "view/fight/callback/SpecialItemAddAction.h"
#include "model/scene/fight/vo/BattleData.h"
#include "manager/sound/SoundManager.h"
#include "components/DropCheckView.h"
#include "model/player/RoleManage.h"
#include "manager/LayerManager.h"

DropMediator::DropMediator():_dispatcher(0),_dropCheckView(0)
{
	//_bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
	//
	//_dispatcher = GameDispatcher::getInstance();
	//_dispatcher->addEventListener(GameDispatcher::PACK_CHANGE, this, callfuncND_selector(BagMediator::packChange));
	//_dispatcher->addEventListener(PopEventName::SHOW_UI_BAG, this, callfuncND_selector(BagMediator::bagPopHandle));
	////_socket.addCmdListener(SocketCMDConst.WMSG_WORLD_ITEM_ADD_INFO,onSpecialItemAdd); 
}

void DropMediator::openDropCheckView()
{
	DropCheckView* eqview = (DropCheckView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_eqdrop);
	if (eqview)
	{
		eqview->removeFromParentAndCleanup(true);
	}

	if (_dropCheckView)
	{	
		_dropCheckView->release();
		_dropCheckView = 0;
		ViewManager::getInstance()->dropCheckView = 0;				
	}


	_dropCheckView = new DropCheckView();
	_dropCheckView->init();
	LayerManager::intervalLayer->addChild(_dropCheckView, IntervalLayer::IntervalLayerZ_eqdrop, IntervalLayer::IntervalLayerTAG_eqdrop);

	//if(_dropCheckView->getisPop())
	{
		_dropCheckView->setDefaultEqs(RoleManage::Instance()->roleLev(),0);//默认显示人物等级段的武器
	}
	//else
	{
		//_dropCheckView.dispose();
	}

	ViewManager::getInstance()->dropCheckView = _dropCheckView;
}