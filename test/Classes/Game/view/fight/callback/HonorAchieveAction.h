#pragma once

#include "view/fight/interfaces/BaseAction.h"
#include "bear/manager/DisplayObjectManager.h"

class HonorAchieveAction : public BaseAction
{
public:
	HonorAchieveAction( int honorId, int lastTotalPoint, int totalPoint )
	{
		_honorId = honorId;
		_lastTotalPoint = lastTotalPoint;
		_totalPoint = totalPoint;
	}

	~HonorAchieveAction() {};

	virtual void doAction()
	{
		DisplayObjectManager::getInstance()->loadPassGiftSkin( _honorId );
	}

	virtual	void addAction(IAction* action){};

	virtual	void delAction(IAction* action){};


public:
	int _honorId;
	int _lastTotalPoint;
	int _totalPoint;
};