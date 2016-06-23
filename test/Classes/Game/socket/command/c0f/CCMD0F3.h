/**
 * 
 * CMSG_WORLD_TRADER_MAP_SKIP	= 0x0F3,			// 	
 */

#ifndef _CCMD0F3_H_
#define _CCMD0F3_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "../s11/SCMD111.h"


class CCMD0F3 : public Packet
{
public:
	CCMD0F3()
	{
	}

	virtual ~CCMD0F3() {}


	virtual bool	Write()
	{
		//writeShort(a_mapId);

		std::vector<SCMD111Node>::iterator iter = d_path.begin();
		int16 size = (int16)d_path.size();
		writeShort(size);
		for(; iter != d_path.end(); ++iter)
		{
			writeShort(iter->a_x);
			writeShort(iter->b_y);
		}

		size = (int16)e_path.size();
		writeShort(size);
		iter = e_path.begin();
		for(; iter != e_path.end(); ++iter)
		{
			writeShort(iter->a_x);
			writeShort(iter->b_y);
		}

		return true;
	}
public :
	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_TRADER_MAP_SKIP;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	//int16 a_mapId;
	std::vector<SCMD111Node> d_path;
	std::vector<SCMD111Node> e_path;
};


class CCMD0F3Factory: public MessageFactory
{
public :
	
	virtual ~CCMD0F3Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TRADER_MAP_SKIP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif 