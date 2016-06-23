#ifndef _CCMD3B4_H_
#define _CCMD3B4_H_

/**
	�ͻ��˿�ʼ����
	CMSG_WORLD_APPLY_CLIMB_TOWER	= 0X3B4,			
	�ͻ���->�����, ���ṹ
	Uint32		ѡ�����Ĳ���(1,31,61..)
	Uint8		�Ƿ�vip5�ý�ҽ���(1���ǣ������񣻲���vip���򲻹���Ҳ����ذ�) 
 */

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD3B4 : public Packet
{
public:
	CCMD3B4() 
	{
		a_floor = 0;
		b_isPay = 0;
	}

	virtual ~CCMD3B4() {}

	virtual bool	Write()
	{
		writeInt(a_floor);
		writeByte(b_isPay);
		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_APPLY_CLIMB_TOWER;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	int a_floor;
	int8 b_isPay;

};


class CCMD3B4Factory: public MessageFactory
{
public :

	virtual ~CCMD3B4Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_APPLY_CLIMB_TOWER;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif