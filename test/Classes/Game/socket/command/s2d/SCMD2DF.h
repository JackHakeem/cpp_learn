/**
 *����˷��ش��н��
WMSG_WORLD_HERITAGE = 0x2Df
�����->�ͻ���, ���ṹ
Uint8	�Ƿ񴫳гɹ���0��ʧ�ܣ�1���ɹ�
Uint8		Դ��Ʒǿ���ȼ�
Uint8        Դ��Ʒ����λ�����ͣ�����/���ϣ�
Uint8 		Դ��Ʒ����λ��
Uint32 		Դ��Ʒ������ٸ��ID���ڱ�����Ϊ0��

Uint8		Ŀ����Ʒǿ���ȼ�
Uint8        Ŀ����Ʒ��Ʒ����λ�����ͣ�����/���ϣ�
Uint8 		Ŀ����Ʒ��Ʒ����λ��
Uint32 		Ŀ����Ʒ��Ʒ������ٸ��ID���ڱ�����Ϊ0�� 
Uint16	Ŀ����Ʒ����ħ���������		�����ʧ����Ϊ0��
Uint16	Ŀ����Ʒ����ħ����������		�����ʧ����Ϊ0��
Uint16	Ŀ����Ʒ����ħ����������		�����ʧ����Ϊ0��
 */
#ifndef _SCMD2DF_H_
#define _SCMD2DF_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD2DF : public Packet
{
public:
	SCMD2DF() {}
	virtual ~SCMD2DF() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_HERITAGE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_type;
	int8 b_streng;
	int8 c_location;
	int8 d_sit;
	int e_roleId;
	int8 f_streng;
	int8 g_location;
	int8 h_sit;
	int i_roleId;
	int16 j_stamina;
	int16 k_wrist;
	int16 l_intellect;
};


class SCMD2DFFactory: public MessageFactory
{
public :
	
	virtual ~SCMD2DFFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2DF();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_HERITAGE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2DFHandler 
{
public:
	static uint32 Execute(SCMD2DF* pPacket) ;
};

#endif