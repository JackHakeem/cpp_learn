/** 
 * @author shenzhiqiang
 * @version 1.1.7.0
 * @description ����˷���-����ʷ��¼
WMSG_EGG_HISTORY = 0x401
����� -> �ͻ���, ���ṹ:
Uint8		��Ը�Ҹ���
Uint16		���˼�¼��
	Uint8	����(1װ����/2Ӷ����/3��Դ��)
	Uint8	Ʒ��(1С/2��/3��ɫ/4��ɫ/5��ɫ/6��ɫ)
	Uint8	״̬(1�ѿ�/2δ��)
	Uint32	����ID(����װ��ID,Ӷ��ID,��ƷID)
	Uint32	��������(װ������,Ӷ������,��Ʒ����)
	Uint32	����
Uint16		������Ҽ�¼��
	String	�������
	Uint8	����(1װ����/2Ӷ����/3��Դ��)
	Uint8	Ʒ��(1С/2��/3��ɫ/4��ɫ/5��ɫ/6��ɫ)
	Uint8	״̬(1�ѿ�/2δ��)
	Uint32	����ID(����װ��ID,Ӷ��ID,��ƷID)
	Uint32	��������(װ������,Ӷ������,��Ʒ����)
	Uint32	����

 * @data 2012-3-26 ����11:57:53 
 * 
 */ 
#ifndef _SCMD401_H_
#define _SCMD401_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "./SCMD401Node1.h"
#include "./SCMD401Node2.h"

class SCMD401 : public Packet
{
public:
	SCMD401()
	{
	}

	virtual ~SCMD401() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_EGG_HISTORY;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_num;
	std::vector<SCMD401Node1> b_myReward;
	std::vector<SCMD401Node2> c_otherReward;
};


class SCMD401Factory: public MessageFactory
{
public :
	
	virtual ~SCMD401Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD401();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_EGG_HISTORY;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD401Handler 
{
public:
	static uint32 Execute(SCMD401* pPacket) ;
};

#endif