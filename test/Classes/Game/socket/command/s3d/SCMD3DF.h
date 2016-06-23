#ifndef _SCMD3DF_H_
#define _SCMD3DF_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

//a_errorcode int8 //0 success£¬ 1 gold not enough£¬

class SCMD3DF : public Packet
{
public:
	SCMD3DF()
	{
		a_errorcode = 0;
	}
	virtual ~SCMD3DF() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TOWER_RECLIMB_RESP;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_errorcode;
};


class SCMD3DFFactory: public MessageFactory
{
public :

	virtual ~SCMD3DFFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD3DF();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_TOWER_RECLIMB_RESP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD3DFHandler 
{
public:
	static uint32 Execute(SCMD3DF* pPacket) ;
};

#endif 