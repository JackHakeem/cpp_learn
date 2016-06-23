/**
����ս�ӽ��
WMSG_WORLD_GROUPCREATE_RESULT = 0x277 
�����->�ͻ���, ���ṹ
Uint16		����ID
Uint16		ս��ID
Uint8		����루0���ɹ�����0��ʧ�ܣ������������	
*/

#ifndef _SCMD277_H_
#define _SCMD277_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD277 : public Packet
{
public:
	SCMD277() {}
	virtual ~SCMD277() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_JOINGROUP_RESULT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint16 a_fbId;
	uint16 b_teamId;
	uint8 c_ret;
};


class SCMD277Factory: public MessageFactory
{
public :

	virtual ~SCMD277Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD277();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_JOINGROUP_RESULT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD277Handler 
{
public:
	static uint32 Execute(SCMD277* pPacket) ;
};

#endif