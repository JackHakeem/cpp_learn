/** 
 * @author shenzhiqiang
 * @version 1.1.7.0
 * @description ����˷���-�ֿ�
WMSG_EGG_DEPOT = 0x40B
����� ->�ͻ���, ���ṹ:
Uint16		����
	Uint8	����(1װ����/2Ӷ����/3��Դ��)
	Uint8	Ʒ��(1С/2��/3��ɫ/4��ɫ/5��ɫ/6��ɫ)
	Uint8	״̬(1�ѿ�/2δ��)
	Uint32	����ID(����װ��ID,Ӷ��ID,��ƷID)
	Uint32	��������(װ������,Ӷ������,��Ʒ����)
	Uint32	�ѵ���

 * @data 2012-3-26 ����11:58:42 
 * 
 */ 
#ifndef _SCMD40B_H_
#define _SCMD40B_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD40BNode.h"

class SCMD40B : public Packet
{
public:
	SCMD40B()
	{
	}

	virtual ~SCMD40B() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_EGG_DEPOT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	std::vector<SCMD40BNode> a_eggs;
};


class SCMD40BFactory: public MessageFactory
{
public :
	
	virtual ~SCMD40BFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD40B();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_EGG_DEPOT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD40BHandler 
{
public:
	static uint32 Execute(SCMD40B* pPacket) ;
};

#endif