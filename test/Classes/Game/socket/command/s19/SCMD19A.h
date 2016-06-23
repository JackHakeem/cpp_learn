#ifndef _SCMD19A_H__
#define _SCMD19A_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
	ϵͳ�㲥
	WMSG_COMMU_SYS_BROADCAST = 0x19A(410),			//ϵͳ�㲥
	�����->�ͻ���, ���ṹ
	Byte:		�㲥����		//  1 �C �ɾ�
									2 �C ʹ��
									3 �C ��Ʒ
									4 �C ��������ʤ
									6  - ��ɫ��������Ʒ����(������Ƭ)
									7  - ��ɫ��������Ʒ�ϳ�
									8  - ���̴�ɣ����¼�
									9  - ���̴󱩻�
									10 - ͨ�̴󱩻�
									11 - �׳�
									12 - ����Boss
									13 - ������ǰ10������ս
	Int:		���ID
	String��	�������
	String��	�㲥��Ϣ  // ��ʽ ��
			���ڳɾ� �� �ɾ�����
			����ʹ�� �� ʹ������
			������Ʒ ��(��Ƭ����Ʒ������������Ʒ����Ƿ�Ϊ0������)
					1��������ɫ��������Ƭ[�ʺ�ID����Ʒ���,������Ʒ���(Ϊ0)��ǿ���ȼ�(Ϊ0)];
					2: ������ɫ��������Ʒ[�ʺ�ID����Ʒ���,������Ʒ���(��Ϊ0)��ǿ���ȼ�(Ϊ0)];
					3, ��ɫ������װ���ϳ�[�ʺ�ID����Ʒ���,������Ʒ���(��Ϊ0)��ǿ���ȼ�(Ϊ0)];
			���ھ������� ��ʤ����
			��������: �������(���Ժ��ԣ���������)
			���ڽ���: �����˵�����
			����ͨ��: �������(���Ժ��ԣ���������)
			��������BOSS���������ҵ�����
			���ھ�����ǰ10������ս������ܵ��������
 */
class SCMD19A : public Packet
{
public:
	SCMD19A():a_type(0),b_id(0),c_name(""),d_content("") {}
	virtual ~SCMD19A() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_COMMU_SYS_BROADCAST;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:		 
	uint8 a_type;
	int32 b_id;
	std::string c_name;
	std::string d_content;

};


class SCMD19AFactory: public MessageFactory
{
public :

	virtual ~SCMD19AFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD19A();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_COMMU_SYS_BROADCAST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD19AHandler 
{
public:
	static uint32 Execute(SCMD19A* pPacket) ;
};
#endif