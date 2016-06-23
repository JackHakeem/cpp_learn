/**
* the server radio upgrade
* WMSG_WORLD_LEVEL_UP = 0 x35D
* the server-> the client, package structure
* Uint32: account ID
 */
#ifndef _SCMD35D_H_
#define _SCMD35D_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD35D : public Packet
{
public:
	SCMD35D()
	{
		a_accountId = 0;
	}
	virtual ~SCMD35D() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_LEVEL_UP;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	int32 a_accountId;
};


class SCMD35DFactory: public MessageFactory
{
public :

	virtual ~SCMD35DFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD35D();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_LEVEL_UP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD35DHandler 
{
public:
	static uint32 Execute(SCMD35D* pPacket) ;
};

#endif