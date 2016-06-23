#include "BagProxyCommand.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "model/backpack/BagProxy.h"


void BagProxyCommand::execute(int32 command, char* data)
{
	BagProxy* _bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
	switch(command)
	{
	case CREATE_GOODS_LIST:
		_bagProxy->createList(data);
		break;
	case UPDATE_GOODS_LIST:
		_bagProxy->updateGoods(data);
		break;
	default:
		break;
	}
}
