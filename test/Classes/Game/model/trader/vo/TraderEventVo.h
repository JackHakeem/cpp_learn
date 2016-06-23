#ifndef _TraderEventVo_H_
#define _TraderEventVo_H_

#include "BaseType.h"

class TraderEventVo
{
public:
	TraderEventVo()
	{
		eventName = "";
		isActive = 0;
	}
	~TraderEventVo()
	{
	}

public:
	int isActive;
	std::list<int> eventArr;
	string eventName;
};
#endif