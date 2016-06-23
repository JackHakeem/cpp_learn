#ifndef _CD_ENERGYACTION_H_
#define _CD_ENERGYACTION_H_
#include "view/fight/interfaces/BaseAction.h"

USING_NS_CC;

class CDEnergyAction : public BaseAction
{
public:
	CDEnergyAction() {};
	virtual ~CDEnergyAction(){}

	virtual void doAction();
	virtual void delAction(IAction* action);

	void okFunction(CCObject *pSender);
	void cancelFunction(CCObject *pSender);

public:
};

#endif