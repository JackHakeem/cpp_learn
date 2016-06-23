#pragma once

class MailContentVo
{
public:
	MailContentVo() : mailId(0),senderName(""),mailTitle(""),mailType(0),mailStatus(0),sendTime(0),attachStatus(0),mailContent(""),attachId(0),goodsNum(0)
	{

	}
	unsigned int mailId;			//邮件唯一ID
	std::string senderName;			//发送人角色名
	std::string mailTitle;			//邮件标题
	unsigned int mailType;			//邮件类型
	unsigned int mailStatus;		//收件箱状态(未读0，已读1)
	unsigned int sendTime;			//发送时间
	unsigned int attachStatus;		//附件领取状态(未领取0，已领取1，无附件状态2)
	std::string mailContent;		//邮件内容
	unsigned int attachId;			//附件物品原型id
	unsigned int goodsNum;			//附件物品数量
protected:
private:
};