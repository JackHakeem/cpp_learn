/**
* ��ҿͻ�����ȡ�ɾͽ���
* CMSG_GET_ACHIVEMENT_AWARD = 0x143
* �ͻ���->�����, ���ṹ
* uint16		����ID
 */ 

#ifndef _CCMD143_H_
#define _CCMD143_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD143 : public Packet
{
public:
	CCMD143()
	{
		a_honorid = 0;
	}
	virtual ~CCMD143() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_GET_ACHIVEMENT_AWARD;}

	virtual	int32		GetMessageSize( ) const { return 0;}

	int16 a_honorid;

};

bool CCMD143::Write()
{
	writeShort( a_honorid );

	return true;
}


class CCMD143Factory: public MessageFactory
{
public :
	
	virtual ~CCMD143Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_GET_ACHIVEMENT_AWARD;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif