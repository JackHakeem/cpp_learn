#pragma once
#include "mvc/SimpleCommand.h"

class OnlineRewardProxy;

class OnlineRewardCommand : public SimpleCommand
{
public:
	OnlineRewardCommand();
	virtual ~OnlineRewardCommand();
	virtual void execute(int32 command, char* data);

	void updateOLInfo(char * data);
	void updateADInfo(char * data);

public:
	enum
	{
		REWARD_OL_UPDATE = 0 , 
		REWARD_AD_UPDATE,
	};

protected:
private:
	OnlineRewardProxy * _pRewardProxy;
};