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
	unsigned int mailStatus;	//״̬(δ��1���Ѷ�2)
	unsigned int sendTime;
	unsigned int attachStatus; //������ȡ״̬(δ��ȡ0������ȡ1���޸���״̬2)
};