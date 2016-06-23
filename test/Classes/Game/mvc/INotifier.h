#ifndef _INOTIFIER_H_
#define _INOTIFIER_H_
#include "BaseType.h"
#define MAX_MODEL 50

class INotifier:public cocos2d::CCNode
{
public:
	virtual ~INotifier(){}
public:
	virtual void handleNotification(int M2Vcmd, char* data){};
	virtual void sendNotification(int type, int appfacade, char* body, int command){};
	virtual void execute(int32 command, char* data){};
};

#endif