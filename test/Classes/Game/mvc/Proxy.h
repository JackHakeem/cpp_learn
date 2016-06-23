#ifndef _PROXY_H_
#define _PROXY_H_

#include "Notifier.h"

//Module layer
class Proxy:public Notifier
{
public:
	virtual void sendNotification(int type, int appfacade, char* body, int command);
private:
	
};

#endif