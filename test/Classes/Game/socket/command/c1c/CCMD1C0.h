#ifndef _CCMD1C0_H_
#define _CCMD1C0_H_

/**
* �鿴��Ա�б���ҳ��
* CMSG_COMMU_GUILD_MEMBER_LIST = 0x1C0 (448),			//�������죬����Ϣ��������㲥
* �����<-�ͻ���, ���ṹ
* Byte��		�������ͣ�						//0-Ĭ�ϣ�����ʾ���ߣ� 1-��ʾ����
* Short:		ҳ��
* @author Administrator
* 
*/	

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD1C0 : public Packet
{
public:
	CCMD1C0() 
	{
	}

	virtual ~CCMD1C0() {}

	virtual bool	Write();	 

	virtual PacketID_t getPacketID() const { return CMSG_COMMU_GUILD_MEMBER_LIST;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	int8 a_displayType;
	int16 b_memberPage;
};

bool CCMD1C0::Write()
{
	writeByte(a_displayType);
	writeShort(b_memberPage);

	return true;
}

class CCMD1C0Factory: public MessageFactory
{
public :

	virtual ~CCMD1C0Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_GUILD_MEMBER_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif