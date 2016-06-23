#ifndef _CCMD1DE_H_
#define _CCMD1DE_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/*
 ���������������CD����
CMSG_WORLD_GUIDE_CDCONDITION = 0x1DE
	�ͻ���->�����, ���ṹ
	byte	 	CD����
*/

class CCMD1DE : public Packet
{
public:
	CCMD1DE() {}
	virtual ~CCMD1DE() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_GUIDE_CDCONDITION;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

	int8 a_cdType ;
};

bool CCMD1DE::Write()
{
	writeByte(a_cdType);
	return true;
}

class CCMD1DEFactory: public MessageFactory
{
public :

	virtual ~CCMD1DEFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_GUIDE_CDCONDITION;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif