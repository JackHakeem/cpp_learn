/**
 * WMSG_WORLD_HERO_INFO = 0x285 
�����->�ͻ���, ���ṹ
Uint16		��������
Uint32		�´ν�������ʱ��
Ӣ�۰������飺�������������ȡ�������鳤��Ϊ0��
	Uint16	������ƷID
	Uint32	������Ʒ����
Ӣ�۰�ǰ25���������
	uint16	������0~24��
	uint32	���ID����������ҵĻ���Ϊ0���ͻ�����ʾ�������ռ�족��
	string	�������
	uint32	����ȼ�
 */

#ifndef _SCMD285_H_
#define _SCMD285_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD285Node.h"
#include "SCMD285Node1.h"

class SCMD285 : public Packet
{
public:
	SCMD285() {}
	virtual ~SCMD285() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_HERO_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int16	a_meRank;	uint32	b_time;
	std::vector<SCMD285Node1> c_rewards;
	std::vector<SCMD285Node> d_rankArr;
};


class SCMD285Factory: public MessageFactory
{
public :
	
	virtual ~SCMD285Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD285();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_HERO_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD285Handler 
{
public:
	static uint32 Execute(SCMD285* pPacket) ;
};

#endif 