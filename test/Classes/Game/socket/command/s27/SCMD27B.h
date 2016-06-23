/**
��Աλ�õ������
WMSG_WORLD_GROUPADJ_RESULT = 0x27B 
�����->�ͻ���, ���ṹ
Uint16		����ID
Uint16		ս��ID
Uint8		����루0���ɹ�����0��ʧ�ܣ������������
*/

#ifndef _SCMD27B_H_
#define _SCMD27B_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD27B : public Packet
{
public:
	SCMD27B() {}
	virtual ~SCMD27B() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_GROUPADJ_RESULT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint16 a_fbId;
	uint16 b_teamId;
	uint8 c_ret;
};


class SCMD27BFactory: public MessageFactory
{
public :

	virtual ~SCMD27BFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD27B();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_GROUPADJ_RESULT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD27BHandler 
{
public:
	static uint32 Execute(SCMD27B* pPacket) ;
};

#endif