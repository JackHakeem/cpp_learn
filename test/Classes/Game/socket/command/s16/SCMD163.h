#ifndef _SCMD163_H_
#define _SCMD163_H_

/**
* Items of information to initialize or change notification
* Backpack, warehouse share
* Protocol number: 0x161 163 165 167;
* S -> c
*/	



#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD161_163_165_167Node.h"

class SCMD163 : public Packet
{
public:
	SCMD163() {}
	virtual ~SCMD163() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_BANK_ITEM_UPDATE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	/*
	struct SCMD163_163_165_167Node
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


class SCMD163Factory: public MessageFactory
{
public :
	
	virtual ~SCMD163Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD163();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_BANK_ITEM_UPDATE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD163Handler 
{
public:
	static uint32 Execute(SCMD163* pPacket) ;
};

#endif 