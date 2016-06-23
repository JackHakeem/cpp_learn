#ifndef _SCMD1C7_H_
#define _SCMD1C7_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

/**
���������Ӧ
GMSG_COMMU_GUILD_ERR = 0x1C7 (455)��			 
�����->�ͻ���, ���ṹ
byte:		��Ӧ��(��Լ��)

��Ӧ�뺬�壺
111�����մﵽ��ߵȼ�
113���ɹ�
114��Ǯ����
115��������������
122�������ڹ����߳�
*/
class SCMD1C7 : public Packet
{
public:
	SCMD1C7() {}
	virtual ~SCMD1C7() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_GUILD_ERR;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint8 a;
};


class SCMD1C7Factory: public MessageFactory
{
public :

	virtual ~SCMD1C7Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1C7();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_GUILD_ERR;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1C7Handler 
{
public:
	static uint32 Execute(SCMD1C7* pPacket) ;
};

/**
 * ������Ӧ��
 * 
��105��ʼ��

// �����½�����
�½�����ɹ�
�����ظ�
���Ҳ���
û��ѫ��

// ���ڹ������
���᲻����

// ���ھ�������
�ɹ�
�Ѵ����ȼ�
��Ҳ���

//���ھ���
���׳ɹ�
���Ҳ���
�������վ�������

//���ڳ�Ա����
�ɹ�
��Ա������
���᳤������
�������󲻴���

//�����������
���������Ѽ����Ĺ���
���������ﵽ����

 
*/

#endif 