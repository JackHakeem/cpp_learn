

#ifndef _SCMD165_H_
#define _SCMD165_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD161_163_165_167Node.h"

class SCMD165 : public Packet
{
public:
	SCMD165() {}
	virtual ~SCMD165() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_BAG_INIT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	/*
	struct SCMD161_163_165_167Node
	{
	int8 a_sitGrid; / / items where
	uint32, b_id; / / the world's goods only Id (Items 0)
	int16 c_goodId; / / items prototype Id (Items 0)
	the int8 d_number; / / number of items (If there are no items to 0)
	the int8 e_superLv; / / enhanced level of
	int 16 f_stamina; / / the magic of the physical number of
	int 16 g_wrist; / / the magic of the wrist a few
	int16 h_intellect; / / Fel Intellect number
	;}
		*/
	std::list<SCMD161_163_165_167Node>		a_goodsList;
};


class SCMD165Factory: public MessageFactory
{
public :
	
	virtual ~SCMD165Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD165();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_BAG_INIT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD165Handler 
{
public:
	static uint32 Execute(SCMD165* pPacket) ;
};

#endif 