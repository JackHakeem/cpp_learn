
#ifndef _CCMD1B1_H_
#define _CCMD1B1_H_

	/**
	 * �鿴�����б���ҳ��
	 * CMSG_COMMU_GUILD_GET_LIST = 0x1B1 (433),	
	 * �����<-�ͻ���, ���ṹ
	 * Short:		ҳ��
	 */

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD1B1 : public Packet
{
public:
	CCMD1B1() {}
	virtual ~CCMD1B1() {}


	virtual bool	Write()
	{
		writeShort(a_page);
		return true;
	};
public :
	virtual PacketID_t getPacketID() const  { return CMSG_COMMU_GUILD_GET_LIST;}

	virtual	int32		GetMessageSize( ) const { return 0;}
	
	int16 a_page;
};

class CCMD1B1Factory: public MessageFactory
{
public :

	virtual ~CCMD1B1Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_GUILD_GET_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};
#endif 