#pragma once

class MailContentVo
{
public:
	MailContentVo() : mailId(0),senderName(""),mailTitle(""),mailType(0),mailStatus(0),sendTime(0),attachStatus(0),mailContent(""),attachId(0),goodsNum(0)
	{

	}
	unsigned int mailId;			//�ʼ�ΨһID
	std::string senderName;			//�����˽�ɫ��
	std::string mailTitle;			//�ʼ�����
	unsigned int mailType;			//�ʼ�����
	unsigned int mailStatus;		//�ռ���״̬(δ��0���Ѷ�1)
	unsigned int sendTime;			//����ʱ��
	unsigned int attachStatus;		//������ȡ״̬(δ��ȡ0������ȡ1���޸���״̬2)
	std::string mailContent;		//�ʼ�����
	unsigned int attachId;			//������Ʒԭ��id
	unsigned int goodsNum;			//������Ʒ����
protected:
private:
};