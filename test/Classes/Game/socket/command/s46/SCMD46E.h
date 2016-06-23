/**
更新每日免费占星数
 */

#ifndef _SCMD46E_H_
#define _SCMD46E_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD46E : public Packet
{
public:

	SCMD46E()
	{
		a_ZXerFreeCountToday = 0;
	}

	virtual ~SCMD46E() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_ZX_UPDATE_FREECOUNT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint32 a_ZXerFreeCountToday;//当前每日免费占星数
};


class SCMD46EFactory: public MessageFactory
{
public :
	
	virtual ~SCMD46EFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD46E();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_ZX_UPDATE_FREECOUNT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD46EHandler 
{
public:
	static uint32 Execute(SCMD46E* pPacket) ;
};

#endif