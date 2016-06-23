#ifndef _CCMD1A2_H_
#define _CCMD1A2_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
	 *�ʼ���ϸ��������
	 * @author Administrator
	 * 
	 */


class CCMD1A2 : public Packet
{
public:
	CCMD1A2() : a_mailId(0)
	{}
	virtual ~CCMD1A2() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_COMMU_MAIL_CONTENT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

	uint32 a_mailId;		//�ʼ�ΨһID
};


class CCMD1A2Factory: public MessageFactory
{
public :

	virtual ~CCMD1A2Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_MAIL_CONTENT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif