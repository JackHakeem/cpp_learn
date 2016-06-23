#ifndef _MEDIATOR_H_
#define _MEDIATOR_H_

#include "Notifier.h"

class Mediator:public Notifier
{
public:
	virtual void sendNotification(int type, int appfacade, char* body, int command);
	virtual void handleNotification(int M2Vcmd, char* data){};
private:

};


#endif