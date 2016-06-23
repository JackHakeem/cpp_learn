/**
ս���������
WMSG_WORLD_GROUPFIGHT_RESULT = 0x27D 
�����->�ͻ���, ���ṹ
Uint16		����ID
Uint16		ս��ID
Uint8		����루0���ɹ�����0��ʧ�ܣ������������
*/

#ifndef _SCMD27D_H_
#define _SCMD27D_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD27D : public Packet
{
public:
	SCMD27D() {}
	virtual ~SCMD27D() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_GROUPFIGHT_RESULT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint16 a_fbId;
	uint16 b_teamId;
	uint8 c_ret;
};


class SCMD27DFactory: public MessageFactory
{
public :

	virtual ~SCMD27DFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD27D();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_GROUPFIGHT_RESULT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD27DHandler 
{
public:
	static uint32 Execute(SCMD27D* pPacket) ;
};

#endif