/**
*ˢ��Ӷ��������Ϣ
CMSG_WORLD_MERCENARY_FOSTER_REFRESH = 0x31E (798)
�ͻ���->�����, ���ṹ
Int�� 	 	��ɫID
Byte��		ˢ�����ͣ�0,1,2,3��
Byte: �Ƿ��õ���
 * * 
*/
#ifndef _CCMD31E_H_
#define _CCMD31E_H_
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD31E : public Packet
{
public:
	CCMD31E() {}
	virtual ~CCMD31E() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_MERCENARY_FOSTER_REFRESH;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

	uint32 a_figureId;
	uint8 b_type;
	uint8 c_useItem;


};


class CCMD31EFactory: public MessageFactory
{
public :

	virtual ~CCMD31EFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_MERCENARY_FOSTER_REFRESH;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};






#endif