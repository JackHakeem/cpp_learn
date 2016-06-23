#ifndef _BANKPROXYCOMMAND_H_
#define _BANKPROXYCOMMAND_H_

#include "mvc/SimpleCommand.h"



class BankProxyCommand:public SimpleCommand
{
public:
	enum 
	{
		CREATE_GOODS_LIST = 0,
		UPDATE_GOODS_LIST,
	};

public:
	~BankProxyCommand(){}
	virtual void execute(int32 command, char* data);

private:
	//BagProxy* 
};

#endif