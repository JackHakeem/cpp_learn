#include "TriggerStoryCommand.h"
#include "socket/network/GameServerSocket.h"
#include "socket/command/c11/CCMD116.h"

TriggerStoryCommand::TriggerStoryCommand()
{
	_wSocket = GameServerSocket::getInstance();
}

TriggerStoryCommand::~TriggerStoryCommand()
{

}

void TriggerStoryCommand::excute(int command, char* data)
{
	int storyId = *(int *)data;
	switch(storyId){
	case 1024:
		_mapId = 1001;
		break;
	}
	if(_mapId!=0)
	{
		enterMap();
	}
}

void TriggerStoryCommand::enterMap()
{
	CCMD116 cmd;
	cmd.triggerId = (int16)_mapId;
	if (_wSocket)
	{
		_wSocket->sendMessage(&cmd);
	}
}