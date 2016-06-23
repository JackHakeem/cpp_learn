/**
	����BOSS������Ϣ
	WMSG_WORLDBOSS_PLAYERINFO = 0X2C8			
	�����->�ͻ���, ���ṹ
	Uint32			�ƶ�CD
	Uint32			ս��CD
	Uint8			�ۼƹ������(0~10)
	Uint32			�ۼ��˺�BOSS����
	��ۻ������������飨���ҡ�������ħʯ�ȣ�
	Uint32		�ۻ�������ƷID
	Uint32		�ۻ�������Ʒ����

*/

#ifndef _SCMD2C8_H_
#define _SCMD2C8_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD2C8 : public Packet
{
public:
	SCMD2C8() {}
	virtual ~SCMD2C8() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLDBOSS_PLAYERINFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	struct SCMD2C8Node 
	{
		uint32 a_id;		// �ۻ�������ƷID
		uint32 b_num;		// �ۻ�������Ʒ����
		SCMD2C8Node()
		{
			a_id = 0;
			b_num = 0;
		}
	};

	uint32 a_movingCD;		// �ƶ�CD
	uint32 b_battleCD;		// ս��CD
	uint8 c_boostNum;		// �ۼƹ������
	uint32 d_damage;			// �ۼ��˺�
	std::list<SCMD2C8Node> e_awardList; // ��ۻ������������飨���ҡ�������ħʯ�ȣ�
};


class SCMD2C8Factory: public MessageFactory
{
public :

	virtual ~SCMD2C8Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2C8();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLDBOSS_PLAYERINFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2C8Handler 
{
public:
	static uint32 Execute(SCMD2C8* pPacket) ;
};

#endif