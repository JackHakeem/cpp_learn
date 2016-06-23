#ifndef _CDEVENT_H__
#define _CDEVENT_H__

#include "BaseType.h"
#include "utils/Timer.h"

class CDEvent
{
public:
	CDEvent(){}
	~CDEvent(){}
	CDEvent( std::string typeStr, int uType, int iLock, Number nTime )
	{
		time = nTime;
		cdType = (int)uType;
		lock = iLock;
	}

public:
	Number time;
	int cdType;
	int lock;	//1 locked 0 not locked
};

#endif