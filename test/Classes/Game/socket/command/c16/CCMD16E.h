/**
//	ITEM_POS_NONE = 0,		// û��λ��
//	ITEM_POS_BAG = 1,		// ����
//	ITEM_POS_BANK = 2,		// �ֿ�
//	ITEM_POS_ROLE = 3,		// ��ɫ����
//	ITEM_POS_MAIL = 4,		// �ʼ�
*/
/**
*Э��ţ� 0x16E
* �����ȡ��Ʒ��ϸ��Ϣ
* c -> s��
* Int8��λ������
* Int8������λ��
* uint����ɫid
*/
#ifndef _CCMD16E_H_
#define _CCMD16E_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD16E : public Packet
{
public:
	CCMD16E() {}
	virtual ~CCMD16E() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_ITEM_INFO;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int8 a_locationType; //λ������
	int8 b_sitNum;		//����λ��
	uint c_roleId;		//��ɫid
};

class CCMD16EFactory: public MessageFactory
{
public :
	
	virtual ~CCMD16EFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_ITEM_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};
#endif 