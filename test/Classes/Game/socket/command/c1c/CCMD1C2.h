#ifndef _CCMD1C2_H_
#define _CCMD1C2_H_

/**
* �鿴��Ա��Ϣ
* CMSG_COMMU_GUILD_MEMBER_INFO = 0x1C2 (450),	
* �����<-�ͻ���, ���ṹ
* string:     ��ѯ��ɫ��
* short��		ҳ��			// �����0����ȷ���ң�����ģ������ -1���ǲ鿴�ҵ�����
byte��		�����־		// 0 �C ֻ��ʾ������� / 1 �C ��ʾ�������
* */


#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD1C2 : public Packet
{
public:
	CCMD1C2() 
	{
		a_pName = "";
		b_code = 0;
		c_type = 0;
	}

	virtual ~CCMD1C2() {}

	virtual bool	Write();	 

	virtual PacketID_t getPacketID() const { return CMSG_COMMU_GUILD_MEMBER_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	string a_pName;
	int16 b_code;
	int8 c_type;
};

bool CCMD1C2::Write()
{
	writeString(a_pName.c_str());
	writeShort(b_code);
	writeByte(c_type);

	return true;
}

class CCMD1C2Factory: public MessageFactory
{
public :

	virtual ~CCMD1C2Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_GUILD_MEMBER_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif