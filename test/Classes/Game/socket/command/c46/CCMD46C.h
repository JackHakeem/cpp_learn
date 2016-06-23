/**
 * 
星魂兑换
 */

#ifndef _CCMD46C_H_
#define _CCMD46C_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD46C : public Packet
{
public:
	CCMD46C() 
	{
		a_xhtype = 0;
	}

	virtual ~CCMD46C() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_ZX_SCORE2XH;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	int32 a_xhtype; //星魂类型ID 具体看表
};


class CCMD46CFactory: public MessageFactory
{
public :

	virtual ~CCMD46CFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_ZX_SCORE2XH;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif