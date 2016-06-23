#ifndef _TraderProxyCommand_H_
#define _TraderProxyCommand_H_

#include "BaseType.h"
#include "mvc/SimpleCommand.h"
#include "model/trader/TraderProxy.h"
#include "socket/command/s2b/SCMD2B1.h"
#include "socket/command/s2b/SCMD2B2.h"
#include "socket/command/s2b/SCMD2B3.h"
#include "socket/command/s2b/SCMD2B4.h"
#include "socket/command/s2b/SCMD2B6.h"
#include "socket/command/s2b/SCMD2B9.h"
#include "socket/command/s2b/SCMD2BB.h"

class TraderProxyCommand:public SimpleCommand
{
public:
	enum 
	{
		CREATE_HISTORY_LIST,
		CREATE_EVENT_LIST,
		CREATE_BANK_LIST,
		CREATE_GOODS_LIST,
		CREATE_CITY_PRICE_LIST,
		UPDATE_HISTORY_LIST,
		UPDATE_GOODS_LIST,
		UPDATE_BANK_LIST,
		UPDATE_EVENT_LIST,
		REACH_EVENT,
		START_BUSINESS,
		END_BUSINESS,
	};

public:
	TraderProxyCommand();
	~TraderProxyCommand();

	virtual void execute(int32 command, char* data);
	void updateEventList(SCMD2B1* param);
	void updateHistoryList(SCMD2B4* param);
	void updateBankList(SCMD2B3* param);
	void updateItemList(SCMD2B2* param);
	void updateCityPrice(SCMD2B6* param);
	void startBusiness(SCMD2B9* cmd);
	void endBusiness(SCMD2BB* cmd);
	void errorCodeTip(int err);
	std::vector<CCPoint> loadMapData(char* fileName, CCPoint startPoint, CCPoint endPoint);


	TraderProxy* _traderProxy;
};

#endif