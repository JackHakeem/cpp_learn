/**
 * ����ս��֪ͨ	
WMSG_SILVERMINE_BATTLE = 0x2E9 
�����->�ͻ���, ���ṹ
	Uint32		�������ID
	string		�����������
	Uint32		�ط����ID
	String		�ط��������
	Int8		ս�������������ʤ����������ʧ�ܣ�
	Uint32		���˷�����ʤ��
	Uint8		�Ƿ�ش�Ӫ��0����1���ǣ�
	Uint64      ս��ID
 */
#ifndef _SCMD2E9_H_
#define _SCMD2E9_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD2E9 : public Packet
{
public:
	SCMD2E9() {}
	virtual ~SCMD2E9() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_SILVERMINE_BATTLE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint32 a_attackId;
	std::string b_attackName;
	uint32 c_defenceId;
	std::string d_defenceName;
	int8 e_result;
	int8 f_winRow;
	int8 g_backHome;
	int32 h_report1;
	int32 i_report2;
};


class SCMD2E9Factory: public MessageFactory
{
public :

	virtual ~SCMD2E9Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2E9();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_SILVERMINE_BATTLE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2E9Handler 
{
public:
	static uint32 Execute(SCMD2E9* pPacket) ;
};

#endif