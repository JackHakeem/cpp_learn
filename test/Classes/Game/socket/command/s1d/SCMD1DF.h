/**
* Server -> client package structure
* Uint8 verify the results verified by the need to create a new account 3 version is too low, 4 prohibit Login
(If verified) will these data, otherwise is 0 or an empty string
* Uint32, User Id
* Uint8 distribution lines
* Uint32, line IP
* Uint16 line port
* Uint32, random verification Key figures
* String random verification SN string
 */

#ifndef _SCMD1DF_H_
#define _SCMD1DF_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD1DF : public Packet
{
public:
	SCMD1DF() {}
	virtual ~SCMD1DF() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_GUIDE_CDCONDITION;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8	a_cdType;
};


class SCMD1DFFactory: public MessageFactory
{
public :
	
	virtual ~SCMD1DFFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1DF();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_GUIDE_CDCONDITION;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1DFHandler 
{
public:
	static uint32 Execute(SCMD1DF* pPacket) ;
};

#endif 