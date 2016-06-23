/**
	����BOSS�BOSS��Ϣ
	WMSG_WORLDBOSS_BOSSINFO = 0X2C9			
	�����->�ͻ���, ���ṹ
	int32			��ǰBOSSѪ����-1����ʾ��ǰ20��������ʾ���ţ�0����ʾ��ɱ���������ʾ��ǰѪ����
	int32			���Ѫ��
	��ǰ��˺��������飨ǰʮ����
	Uint8		���Σ�0~9��		
	string		�������
	int32		�˺���
	uint8		�˺��ȣ�0��100��
*/

#ifndef _SCMD2C9_H_
#define _SCMD2C9_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD2C9 : public Packet
{
public:
	SCMD2C9() {}
	virtual ~SCMD2C9() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLDBOSS_BOSSINFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	struct SCMD2C9Node 
	{
		uint8 a_rank;		// ���Σ�0~9��	
		std::string b_name;	// �������
		uint32 c_damage;	// �˺���
		//public var d_damagePercent:uint;	// �˺��ȣ�0��100��
		SCMD2C9Node()
		{
			a_rank = 0;
			b_name = "";
			c_damage = 0;
		}
	};

	uint32 a_currentHP;		// ��ǰBOSSѪ����-1����ʾ��ǰ20��������ʾ���ţ�0����ʾ��ɱ���������ʾ��ǰѪ����
	uint32 b_maxHP;			// ���Ѫ��
	uint32 c_totalDamage_low;	// ���˺���-��λ
	uint32 c_totalDamage_high;// ���˺���-��λ
	std::list<SCMD2C9Node> d_damageRankList;	// ��ǰ��˺��������飨ǰʮ����
};


class SCMD2C9Factory: public MessageFactory
{
public :

	virtual ~SCMD2C9Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2C9();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLDBOSS_BOSSINFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2C9Handler 
{
public:
	static uint32 Execute(SCMD2C9* pPacket) ;
};

#endif