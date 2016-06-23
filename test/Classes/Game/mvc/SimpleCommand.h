#ifndef _SIMPLECOMMAND_H_
#define _SIMPLECOMMAND_H_

#include "Notifier.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

class SimpleCommand:public Notifier
{
public:
	virtual ~SimpleCommand(){};
	
	virtual void execute(int32 command, char* data){};

	virtual void sendNotification(int type, int appfacade, char* body, int command);	
};

#endif