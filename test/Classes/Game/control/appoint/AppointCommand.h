#ifndef _APPOINT_COMMAND_H_
#define _APPOINT_COMMAND_H_
#include "mvc/SimpleCommand.h"


class AppointCommand : public SimpleCommand
{
public:

	enum
	{
		INIT_INFO = 0,
		APPOINT_RESULT,
		RECEIVE_RESULT,
		BLESS_RESULT
	};

	virtual void execute( int32 command, char* data );
	void initInfo(char *pData);
	void appointResult(char *pData);
	void receiveResult(char *pData);
	void blessResult(char *pData);
	void setExchangeType(int value);
	void sortGoods();
};

#endif