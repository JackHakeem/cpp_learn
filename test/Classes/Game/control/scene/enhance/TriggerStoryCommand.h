#ifndef HLQS_TriggerProxyCommand_H_
#define HLQS_TriggerProxyCommand_H_

#include "cocos2d.h"
#include "mvc/SimpleCommand.h"

USING_NS_CC;

class GameServerSocket;

class TriggerStoryCommand : public SimpleCommand
{
public:
	TriggerStoryCommand();
	~TriggerStoryCommand();

public:
	virtual void excute(int command, char* data);
	void enterMap();

protected:

private:
	GameServerSocket * _wSocket;
	int _mapId;
};


#endif