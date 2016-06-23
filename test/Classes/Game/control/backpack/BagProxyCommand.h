#ifndef _BAGPROXYCOMMAND_H_
#define _BAGPROXYCOMMAND_H_

#include "mvc/SimpleCommand.h"



class BagProxyCommand:public SimpleCommand
{
public:
	enum 
	{
		CREATE_GOODS_LIST = 0,
		UPDATE_GOODS_LIST,
	};

public:
	~BagProxyCommand(){}
	virtual void execute(int32 command, char* data);

private:
	//BagProxy* 
};

#endif