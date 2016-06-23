#include "BankProxyCommand.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "model/bank/BankProxy.h"


void BankProxyCommand::execute(int32 command, char* data)
{
	BankProxy* _bankProxy = (BankProxy*)g_pFacade->retrieveProxy(AppFacade_BANK_PROXY_CHANGE);
	switch(command)
	{
	case CREATE_GOODS_LIST:
		_bankProxy->createList(data);
		break;
	case UPDATE_GOODS_LIST:
		_bankProxy->updateGoods(data);
		break;
	default:
		break;
	}
}