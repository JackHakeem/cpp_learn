#ifndef _CCMD3CD_H_
#define _CCMD3CD_H_

/**
	�ͻ�����������(�����ɹ���������ҳ��Ϣ)
	CMSG_WORLD_REPLACE_RANK	= 0X3CD			
	�ͻ���->�����, ���ṹ
	Uint32 		����¥��
	Uint8		�Ƿ��ý��ֱ������(1,�ǣ���,�񣻲�����Ҳ����ذ�) 
 */
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD3CD : public Packet
{
public:
	CCMD3CD() 
	{
	}

	virtual ~CCMD3CD() {}

	virtual bool	Write()
	{
		writeInt(a_namedFloor);
		writeByte(b_isPay);
		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_REPLACE_RANK;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	int a_namedFloor;
	int8 b_isPay;
};


class CCMD3CDFactory: public MessageFactory
{
public :

	virtual ~CCMD3CDFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_REPLACE_RANK;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif