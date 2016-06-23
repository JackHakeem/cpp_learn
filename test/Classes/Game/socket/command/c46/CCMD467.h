/**
 * 
�ǻ�ʰȡ 
 */

#ifndef _CCMD467_H_
#define _CCMD467_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD467 : public Packet
{
public:
	CCMD467() 
	{
		a_bankPos = 0;
	}

	virtual ~CCMD467() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_ZX_COLLECT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	uint8 a_bankPos;//��������˼255:һ��ʰȡ   0~11:ʰȡ����λ��
};


class CCMD467Factory: public MessageFactory
{
public :

	virtual ~CCMD467Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_ZX_COLLECT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif