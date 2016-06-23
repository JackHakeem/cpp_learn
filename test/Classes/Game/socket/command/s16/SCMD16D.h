#ifndef _SCMD16D_H_
#define _SCMD16D_H_

/**
* Items of information to initialize or change notification
* Backpack, warehouse share
* Protocol number: 0x161 163 165 167;
* S -> c

*/	



#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD16D : public Packet
{
public:
	SCMD16D() {}
	virtual ~SCMD16D() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_ITEM_ADD_INFO;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_from;
	int16 b_goodsId;
	int8 c_num;
	int8 d_sitGrid;
};


class SCMD16DFactory: public MessageFactory
{
public :
	
	virtual ~SCMD16DFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD16D();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_ITEM_ADD_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD16DHandler 
{
public:
	static uint32 Execute(SCMD16D* pPacket) ;
};

#endif 