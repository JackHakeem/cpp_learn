#ifndef _SLCQ_Message_Mgr_H_
#define _SLCQ_Message_Mgr_H_

#include "BaseType.h"
#include "../Singleton.h"

class MessageMgr : public Singleton<MessageMgr> , public CCObject
{
public:
	MessageMgr();
	~MessageMgr();

	void start();
	void stop();

	void sendMessage(int msgType , void * data);
//	void recvMessage(int msgType , void * data);

	struct Msg
	{
		int msgType;
		void * data;
		Msg()
		{
			msgType = 0;
			data = 0;
		}
	};

public:	
	void handlerMessage(int msgType , void * data);
	void my_thread(ccTime dt);

private:
	std::list<struct Msg> _messageQuene;

};

#endif