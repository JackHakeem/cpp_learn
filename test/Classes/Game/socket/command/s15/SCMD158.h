#ifndef _SCMD158_H_
#define _SCMD158_H_
#include "socket/network/Packet.h"
#include "socket/message/MessageFactory.h"
#include "socket/message/SocketCMDConst.h"

class SCMD158 : public Packet
{
public:
	SCMD158(){}
	virtual ~SCMD158(){}

	virtual int32 Execute();

	virtual bool Read();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TASK_UPDATE;}

	struct SCMD158Node
	{
		int _id;
		int16 _nowCount;
	};

	int16 _id;
	//std::list<SCMD158Node> _tasksTips;
	SCMD158Node _taskTip;
};

class SCMD158Factory : public MessageFactory
{
public:
	SCMD158Factory(){}
	virtual ~SCMD158Factory(){}

	virtual Packet* CreateMessage() {return new SCMD158();}

	virtual PacketID_t GetPacketID() const {return WMSG_WORLD_TASK_UPDATE;}

	virtual uint32 GetMessageMaxSize() const {return 0;}

};

class SCMD158Handler 
{
public:
	static uint32 Execute(SCMD158 *pPacket) ;
};

#endif