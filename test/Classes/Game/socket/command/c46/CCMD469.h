/**
 * 
�ǻ�������ƶ��ǻ����
 */

#ifndef _CCMD469_H_
#define _CCMD469_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD469 : public Packet
{
public:
	CCMD469() 
	{
		a_fromPosType = 0;
		b_fromPos= 0;
		c_toPosType= 0;
		d_toPos= 0;
		e_roldId = 0;
	}

	virtual ~CCMD469() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_ZX_XH_MOVE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	/*
	enum ��������
	{
		XH_POS_16 = 1,����
		XH_POS_8 = 3, װ��
	};
	*/
	int8 a_fromPosType; //�Ӱ������ͣ�enum �������ͣ�ע��ö��ֵ��
	int8 b_fromPos;		//���ĸ�λ��
	int8 c_toPosType;	//�ƶ����������ͣ�enum �������ͣ�ע��ö��ֵ��
	int8 d_toPos;		//�ƶ���λ��
	uint32 e_roldId;	//Ӷ��ID��������漰��װ�������ƶ���Ҫд��������0��
};


class CCMD469Factory: public MessageFactory
{
public :

	virtual ~CCMD469Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_ZX_XH_MOVE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif