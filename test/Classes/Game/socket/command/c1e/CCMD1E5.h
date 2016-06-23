/**
	�ͻ�������ί����Ʒ
	CMSG_WORLD_DELEGATE_SELL_ITEM = 0x1E5 (485)
	�ͻ���->�����, ���ṹ
	Short:		��ȡ��Ʒ������
		Uint16:		��ȡ����Ʒԭ��Id 
 */
#ifndef _CCMD1E5_H_
#define _CCMD1E5_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD1E5 : public Packet
{
public:
	CCMD1E5() 
	{
	}

	virtual ~CCMD1E5() {}

	std::list<int16> a_goods;
	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_DELEGATE_SELL_ITEM;}

	virtual	int32		GetMessageSize( ) const { return 0;}
};

class CCMD1E5Factory: public MessageFactory
{
public :

	virtual ~CCMD1E5Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_DELEGATE_SELL_ITEM;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};
#endif 