#ifndef _HLQS_GuestMediator_H_
#define _HLQS_GuestMediator_H_

#include "cocos2d.h"
#include "mvc/Mediator.h"

USING_NS_CC;

class GuestMediator : public Mediator
{
public:
	GuestMediator();
	virtual ~GuestMediator(){}
};

#endif