#pragma once

class MailHeadVo
{
public:
	MailHeadVo() : mailId(0),senderName(""),mailTitle(""),mailType(0),mailStatus(0),sendTime(0),attachStatus(0)
	{
	}
	unsigned int mailId;
	std::string senderName;
	std::string mailTitle;
	unsigned int mailType;
	unsigned int mailStatus;	//状态(未读1，已读2)
	unsigned int sendTime;
	unsigned int attachStatus; //附件领取状态(未领取0，已领取1，无附件状态2)
};