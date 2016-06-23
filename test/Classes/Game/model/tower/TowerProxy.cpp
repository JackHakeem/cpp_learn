#include "TowerProxy.h"
#include "mvc/Facade.h"
#include "view/tower/TowerMediator.h"
#include "control/AppFacade.h"

TowerProxy::TowerProxy()
{
	_panel1Vo = 0;
	_panel2Vo = 0;
	_rankVo = 0;
	numFree = 0;
	numPay = 0;
	waitFightEnd = false;
	showLottery = false;
}

TowerProxy::~TowerProxy()
{
	CC_SAFE_DELETE(_panel1Vo);
	CC_SAFE_DELETE(_panel2Vo);
	CC_SAFE_DELETE(_rankVo);

}

TowerPanel1Vo* TowerProxy::getpanel1Vo()
{
	return _panel1Vo;
}

void TowerProxy::setpanel1Vo(TowerPanel1Vo* value)
{
	CC_SAFE_DELETE(_panel1Vo);
	_panel1Vo = value;
	sendNotification(Facade_Mediator,
		AppFacade_TOWER_PROXY_CHANGE, (char*)value, TowerMediator::UPDATE_PANEL_1);
}

TowerPanel2Vo* TowerProxy::getpanel2Vo()
{
	return _panel2Vo;
}

void TowerProxy::setpanel2Vo(TowerPanel2Vo* value)
{
	CC_SAFE_DELETE(_panel2Vo);
	_panel2Vo = value;
	if(waitFightEnd == false)
	{
		sendNotification(Facade_Mediator,
			AppFacade_TOWER_PROXY_CHANGE, (char*)value, TowerMediator::UPDATE_PANEL_2);
	}
}

TowerRankListVo* TowerProxy::getrankVo()
{
	return _rankVo;
}

void TowerProxy::setrankVo(TowerRankListVo* value)
{
	CC_SAFE_DELETE(_rankVo);
	_rankVo = value;
	sendNotification(Facade_Mediator,
		AppFacade_TOWER_PROXY_CHANGE, (char*)value, TowerMediator::UPDATE_RANK_LIST);
}
