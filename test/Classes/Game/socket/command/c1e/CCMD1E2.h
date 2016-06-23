/**
 *  �ͻ�������ί��
	CMSG_WORLD_DELEGATE_REQUEST = 0x1E2 (482)
	�ͻ���->�����, ���ṹ
	Uint8:		��������(��ָ����0����������1) 
	Uint8:		���˵ȼ�
	Uint8:		�Ա����ͣ�0�������Ա���1������Ա���
 */
#ifndef _CCMD1E2_H_
#define _CCMD1E2_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD1E2 : public Packet
{
public:
	CCMD1E2() 
	{
		a_type = 0;
		b_lev = 0;
		c_isGold = 0;
	}

	virtual ~CCMD1E2() {}

	int8 a_type;
	int8 b_lev;
	int8 c_isGold;

	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_DELEGATE_REQUEST;}

	virtual	int32		GetMessageSize( ) const { return 0;}
};

class CCMD1E2Factory: public MessageFactory
{
public :

	virtual ~CCMD1E2Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_DELEGATE_REQUEST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};
#endif 