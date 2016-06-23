/**
 * ���ʹ������ս����	
	CMSG_SILVERMINE_TOKEN = 0x2EE 
	�ͻ���->�����, ���ṹ
	Uint8		����ID����0��Ϯ����1���š���2���ۡ���3���顿
	Uint32		Ŀ������ID
 */

#ifndef _CCMD2EE_H_
#define _CCMD2EE_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2EE : public Packet
{
public:
	CCMD2EE() 
	{
		a_type = 0;
		b_mineID = 0;
	}

	virtual ~CCMD2EE() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_SILVERMINE_TOKEN;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	int8 a_type;
	uint32 b_mineID;
};


class CCMD2EEFactory: public MessageFactory
{
public :

	virtual ~CCMD2EEFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_SILVERMINE_TOKEN;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif