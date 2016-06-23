#include "SCMD151.h"
#include "view/login/LoginMediator.h"


int32 SCMD151::Execute()
{
	if(!Read())
	{
		return 1;
	}

	return SCMD151Handler::Execute(this);
}

bool SCMD151::Read()
{
	_tasks.clear();
	int16 taskCount = readShort();
	
	for(int16 i=0; i<taskCount; ++i)
	{
		SCMD151Node newNode;
		newNode._id = readShort();
		newNode._type = readByte();
		newNode._finish = readByte();
		int16 requireCount = readShort();
		//cocos2d::CCLog("==================151,id=%d,requireCount=%d", newNode._id, requireCount);
		for(int16 j=0; j<requireCount; ++j)
		{
			SCMD151Node1 newNode1;
			newNode1._id = readInt();
			newNode1._nowCount = readShort();
			//cocos2d::CCLog("==================151,node=%d,nowCount=%d", newNode1._id, newNode1._nowCount);
			newNode._taskTip.push_back(newNode1);
		}
		_tasks.push_back(newNode);
	}
	return true;
}


uint32 SCMD151Handler::Execute( SCMD151 *pPacket )
{
	if(!pPacket)
	{
		return 1;
	}
	LoginMediator *loginMediator = (LoginMediator *) g_pFacade->retrieveMediator(AppFacade_LOGIN_MEDIATOR);
	loginMediator->taskAccept((char *)pPacket);
	return 0;
}
