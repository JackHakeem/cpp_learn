/** 
 * @author shenzhiqiang
 * @version 1.1.4.0
 * @data 2012-3-8 ����02:18:43 
 * @description �ͻ�������һ��Ա�ף����Ʒ
	CMSG_WORLD_DELEGATE_GET_BLESS_ITEM				= 0x1DC,
�ͻ���->�����, ���ṹ
Uint16:		�һ���Ʒԭ��Id
 * 
 */ 
#ifndef _CCMD1DC_H_
#define _CCMD1DC_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
class CCMD1DC : public Packet
{
public:
	CCMD1DC() {}
	virtual ~CCMD1DC() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_DELEGATE_GET_BLESS_ITEM;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

	int16 a_goodsId ;
};

bool CCMD1DC::Write()
{
	writeShort(a_goodsId);
	return true;
}

class CCMD1DCFactory: public MessageFactory
{
public :

	virtual ~CCMD1DCFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_DELEGATE_GET_BLESS_ITEM;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif