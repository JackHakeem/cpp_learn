#ifndef _CONTROLCOMMAND_H_
#define _CONTROLCOMMAND_H_

#include "mvc/SimpleCommand.h"

class ControlCommand :public SimpleCommand
{
public:
	ControlCommand(){}
	~ControlCommand(){}

	virtual void execute(int32 command, char* data);
};

#endif