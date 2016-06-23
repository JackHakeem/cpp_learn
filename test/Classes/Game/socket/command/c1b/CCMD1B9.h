#ifndef _CCMD1B9_H_
#define _CCMD1B9_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

/**
��Ա����
CMSG_COMMU_GUILD_NOMINATE = 0x1B9 (441),			
�����<-�ͻ���, ���ṹ
string:     �������߽�ɫ����			 
byte��		ְ��ID						//3-�᳤ 2-���᳤ 1-��Ա 0-��ͨ��Ա
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