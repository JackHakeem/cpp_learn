/**
占星更新积分
 */

#ifndef _SCMD46D_H_
#define _SCMD46D_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD46D : public Packet
{
public:

	SCMD46D()
	{
		a_XHScore = 0;
	}

	virtual ~SCMD46D() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_ZX_UPDATE_SCORE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint32 a_XHScore;//当前积分
};


class SCMD46DFactory: public MessageFactory
{
public :
	
	virtual ~SCMD46DFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD46D();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_ZX_UPDATE_SCORE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD46DHandler 
{
public:
	static uint32 Execute(SCMD46D* pPacket) ;
};

#endif