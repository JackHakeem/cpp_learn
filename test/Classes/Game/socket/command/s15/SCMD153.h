#ifndef _SCMD153_H_
#define _SCMD153_H_

#include "socket/network/Packet.h"
#include "socket/message/MessageFactory.h"
#include "socket/message/SocketCMDConst.h"

/**
* Push to the client can be accessed entrusted the task information
WMSG_WORLD_ENTRUST_TASK_VISIBLE = 0x153 (339),
The service side -> client package structure
Byte: has completed the tasks entrusted
Short: the number of tasks
Short: task ID
Byte: type of task / / At present, only on behalf of Daguai task [crusade]
Int: the monster combination of ID
Short: Map ID

Byte: a monster number of
Byte: the difficulty of / / 1 to 6 represents the degree of difficulty (easy) EDCBAS (difficult)
Int: Awards Item ID
Int: reward coins

Int: reward gold
Byte: whether it is plugged in / / 0 - No / 1 -
*/
class SCMD153 : public Packet
{
public:
	SCMD153(){}
	virtual ~SCMD153(){}

	virtual int32 Execute();

	virtual bool Read();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_ENTRUST_TASK_VISIBLE;}


	struct SCMD153Node
	{
		int16 _id;
		int8 _type;
		int _mgId;
		int16 _mapId;

		int8 _num;
		int8 _lev;
		int _goodId;
		int _silver;

		int _gold;
		int8 _acc;
	};

	int8 _finishNum;
	int8 _diffLev;
	std::list<SCMD153Node> _task;
};

class SCMD153Factory : public MessageFactory
{
public:
	SCMD153Factory(){}
	virtual ~SCMD153Factory(){}

	virtual Packet* CreateMessage() {return new SCMD153();}

	virtual PacketID_t GetPacketID() const {return WMSG_WORLD_ENTRUST_TASK_VISIBLE;}

	virtual uint32 GetMessageMaxSize() const{return 0;}

};
#endif