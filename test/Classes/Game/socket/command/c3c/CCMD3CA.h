#ifndef _CCMD3CA_H_
#define _CCMD3CA_H_


/**客户端请求幻龙塔排位信息
public static const CMSG_WORLD_REQ_RANKLIST_BY_PAGE:uint	= 0X3CA;
*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD3CA : public Packet
{
public:
	CCMD3CA() 
	{
	}

	virtual ~CCMD3CA() {}

	virtual bool	Write()
	{
		writeShort(a_sit);
		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_REQ_RANKLIST_BY_PAGE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	int16 a_sit;
};


class CCMD3CAFactory: public MessageFactory
{
public :

	virtual ~CCMD3CAFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_REQ_RANKLIST_BY_PAGE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif