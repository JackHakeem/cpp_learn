#ifndef _VIEWCOMMAND_H_
#define _VIEWCOMMAND_H_

#include "mvc/SimpleCommand.h"

class ViewCommand :public SimpleCommand
{
public:
	ViewCommand(){}
	~ViewCommand(){}

	virtual void execute(int32 command, char* data);
};

#endif

