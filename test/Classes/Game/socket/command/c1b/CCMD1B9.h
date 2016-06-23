#ifndef _CCMD1B9_H_
#define _CCMD1B9_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

/**
成员任命
CMSG_COMMU_GUILD_NOMINATE = 0x1B9 (441),			
服务端<-客户端, 包结构
string:     被任命者角色名，			 
byte：		职务ID						//3-会长 2-副会长 1-官员 0-普通成员
*/

class CCMD1B9 : public Packet
{
public:
	CCMD1B9() {}
	virtual ~CCMD1B9() {}


	virtual bool	Write()
	{
		writeString(a_memberName.c_str());
		writeByte(b_position);

		return true;
	}
public :
	virtual PacketID_t getPacketID() const { return CMSG_COMMU_GUILD_NOMINATE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

	string a_memberName;
	int8 b_position;
};



class CCMD1B9Factory: public MessageFactory
{
public :

	virtual ~CCMD1B9Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_GUILD_NOMINATE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif