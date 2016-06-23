#include "SCMD1A3.h"
#include "view/mail/MailMediator.h"
#include "control/AppFacade.h"

bool	SCMD1A3::Read()
{
	a_mailId = readUint();			//�ʼ�ΨһID
	b_senderName = readString();	//�����˽�ɫ��
	c_mailTitle = readString();		//�ʼ�����
	d_mailType = readUbyte();		//�ʼ�����
	e_mailStatus = readUbyte();		//�ռ���״̬(δ��0���Ѷ�1)
	f_sendTime = readUint();		//����ʱ��
	g_attachStatus = readUbyte();	//������ȡ״̬(δ��ȡ0������ȡ1���޸���״̬2)
	h_mailContent = readString();	//�ʼ�����
	i_attachId = readUshort();
	j_goodsNum = readUint();

	return true;
}

int32 	SCMD1A3::Execute()
{
	if (!Read())
	{
		return 1;
	}
	return SCMD1A3Handler::Execute(this) ;
}


uint32 SCMD1A3Handler::Execute(SCMD1A3* pPacket)
{
	if (!pPacket) return 1;

	MailMediator * pMailMediator = (MailMediator *)g_pFacade->retrieveMediator(AppFacade_Mail_Mediator);
	if (pMailMediator)
	{
		pMailMediator->sockMailContent(pPacket);
	}

	return 0;
}