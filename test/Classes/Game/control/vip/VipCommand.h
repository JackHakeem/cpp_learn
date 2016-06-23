#ifndef _VIP_COMMAND_H_
#define _VIP_COMMAND_H_
#include "mvc/SimpleCommand.h"

class VipCommand : public SimpleCommand
{
public:
	enum VipCommandType 
	{
		REWARD_UPDATE = 0,
	};

	virtual void execute( int32 command, char* data ) ;

};
#endif