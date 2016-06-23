/**
 *
 The client requests for upgrade talent skills
 WMSG_WORLD_UPGRADE_TALENT = 0 x3AC (940)
 The server-> the client, package structure
 Uint8 success
 Uint16 skills ID
 Uint8 new level
 */

#ifndef _SCMD3AC_H_
#define _SCMD3AC_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD3AC : public Packet
{
public:
	SCMD3AC()
	{
		a_isSuccess = 0;
		b_tltId = 0;
		c_newLv = 0;
	}

	virtual ~SCMD3AC() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_UPGRADE_TALENT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	int8 a_isSuccess ;
	int16 b_tltId ;
	int8 c_newLv ;

};


class SCMD3ACFactory: public MessageFactory
{
public :

	virtual ~SCMD3ACFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD3AC();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_UPGRADE_TALENT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD3ACHandler 
{
public:
	static uint32 Execute(SCMD3AC* pPacket) ;
};

#endif 