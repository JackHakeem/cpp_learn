#ifndef _CCMD192_H_
#define _CCMD192_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
 * CMSG_COMMU_WORLD_CHAT = 0x190(400),			//�������죬����Ϣ��������㲥
 * �����->�ͻ���, ���ṹ
 * string:     �������� 
 * string:		�������ݣ�ս����չʾ��Ʒ�ȣ�
 */

class CCMD192 : public Packet
{
public:
	CCMD192() {}
	virtual ~CCMD192() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_COMMU_GUILD_CHAT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

	std::string a_content;
	std::string b_data;


};


class CCMD192Factory: public MessageFactory
{
public :

	virtual ~CCMD192Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_GUILD_CHAT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif