

#ifndef _CCMD1BD_H_
#define _CCMD1BD_H_
	/**
	 �����������
	 CMSG_COMMU_GUILD_APPLY_HANDLE = 0x1BD (445),	
	 �����<-�ͻ���, ���ṹ
	 string:     �����߽�ɫ����
	 byte��		��������					// 0-ͬ�� / 1-�ܾ�
	 */
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD1BD : public Packet
{
public:
	CCMD1BD() {}
	virtual ~CCMD1BD() {}


	virtual bool	Write()
	{
		writeString(a_pName.c_str());
		writeByte(b_result);
		return true;
	}
public :
	virtual PacketID_t getPacketID() const { return CMSG_COMMU_GUILD_APPLY_HANDLE;}

	virtual	int32		GetMessageSize( ) const { return 0;}
	
	string a_pName;
	int8 b_result;
};


class CCMD1BDFactory: public MessageFactory
{
public :

	virtual ~CCMD1BDFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_GUILD_APPLY_HANDLE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif