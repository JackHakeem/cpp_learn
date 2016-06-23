#include "SCMD1A3.h"
#include "view/mail/MailMediator.h"
#include "control/AppFacade.h"

bool	SCMD1A3::Read()
{
	a_mailId = readUint();			//邮件唯一ID
	b_senderName = readString();	//发送人角色名
	c_mailTitle = readString();		//邮件标题
	d_mailType = readUbyte();		//邮件类型
	e_mailStatus = readUbyte();		//收件箱状态(未读0，已读1)
	f_sendTime = readUint();		//发送时间
	g_attachStatus = readUbyte();	//附件领取状态(未领取0，已领取1，无附件状态2)
	h_mailContent = readString();	//邮件内容
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